// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2026 Noethric. NoeMixerr optional audio recording backend.
// PortAudio retains its own MIT-style license; see the upstream PortAudio package.
#include <portaudio.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace {
namespace fs = std::filesystem;
constexpr double kPi = 3.14159265358979323846;
void require(bool success, const char* reason) {
    if (!success) throw std::runtime_error(reason);
}
void write16(std::ostream& s, uint16_t x) {
    s.put(char(x & 0xff)); s.put(char((x >> 8) & 0xff));
}
void write32(std::ostream& s, uint32_t x) {
    write16(s, uint16_t(x)); write16(s, uint16_t(x >> 16));
}
class WaveFile {
    fs::path destination_;
    fs::path temporary_;
    std::fstream output_;
    uint64_t samples_ = 0;
    bool finished_ = false;
    int rate_, channels_;
public:
    WaveFile(const fs::path& path, int rate, int channels)
      : destination_(path), temporary_(path.string() + ".partial"),
        rate_(rate), channels_(channels) {
        require(!fs::exists(destination_), "Output exists. Select a new WAV filename.");
        require(!fs::exists(temporary_), "A partial recording already exists");
        output_.open(temporary_, std::ios::out | std::ios::binary | std::ios::trunc);
        require(bool(output_), "Cannot create recording");
        std::array<char,44> header{};
        output_.write(header.data(), header.size());
        require(bool(output_), "Cannot initialize WAV file");
    }
    WaveFile(const WaveFile&) = delete;
    WaveFile& operator=(const WaveFile&) = delete;
    ~WaveFile() {
        if (output_.is_open()) output_.close();
        if (!finished_) {
            std::error_code error;
            fs::remove(temporary_, error);
        }
    }
    void writeSamples(const float* source, size_t samples) {
        std::array<char,8192> bytes{};
        for (size_t offset=0; offset < samples;) {
            const size_t count = std::min(samples-offset, bytes.size()/2);
            for (size_t i=0; i<count; ++i) {
                const float x = std::isfinite(source[offset+i]) ? source[offset+i] : 0.0f;
                const int16_t pcm = int16_t(std::lround(std::clamp(x,-1.0f,1.0f)*32767.0f));
                bytes[2*i] = char(uint16_t(pcm) & 255);
                bytes[2*i+1] = char((uint16_t(pcm) >> 8) & 255);
            }
            output_.write(bytes.data(), std::streamsize(count*2));
            require(bool(output_), "Disk write failed");
            samples_ += count;
            offset += count;
        }
    }
    void finish() {
        require(samples_ <= (UINT32_MAX-36ULL)/2ULL, "WAV exceeds RIFF 4 GiB file limit");
        require(samples_ % unsigned(channels_) == 0, "Incomplete audio frame");
        output_.seekp(0, std::ios::beg);
        output_.write("RIFF",4); write32(output_, uint32_t(36+samples_*2));
        output_.write("WAVEfmt ",8);
        write32(output_,16); write16(output_,1);write16(output_,uint16_t(channels_));
        write32(output_,uint32_t(rate_));
        write32(output_,uint32_t(rate_*channels_*2));
        write16(output_,uint16_t(channels_*2)); write16(output_,16);
        output_.write("data",4); write32(output_,uint32_t(samples_*2));
        output_.flush();
        require(bool(output_), "WAV header finalization failed");
        output_.close();
        require(!fs::exists(destination_), "Destination was created by another process");
        fs::rename(temporary_, destination_);
        finished_ = true;
    }
    uint64_t frames() const { return samples_ / unsigned(channels_); }
};
class Ring {
    static constexpr size_t kCapacity = 1U << 19;
    static constexpr size_t kMask = kCapacity-1;
    std::vector<float> data_{kCapacity};
    std::atomic<uint64_t> produced_{0}, consumed_{0};
public:
    // Single audio-callback producer. No allocation, locks, logging or I/O.
    bool push(const float* input, size_t count) noexcept {
        const uint64_t write = produced_.load(std::memory_order_relaxed);
        const uint64_t read = consumed_.load(std::memory_order_acquire);
        if (count > kCapacity - size_t(write-read)) return false;
        size_t start = size_t(write) & kMask;
        size_t first = std::min(count, kCapacity - start);
        if (input) {
            std::memcpy(data_.data()+start, input, first*sizeof(float));
            if (first < count) std::memcpy(data_.data(), input+first, (count-first)*sizeof(float));
        } else {
            std::fill_n(data_.data()+start, first, 0.0f);
            if (first < count) std::fill_n(data_.data(), count-first, 0.0f);
        }
        produced_.store(write+count, std::memory_order_release);
        return true;
    }
    size_t pop(float* destination, size_t maxSamples) noexcept {
        const uint64_t read = consumed_.load(std::memory_order_relaxed);
        const uint64_t write = produced_.load(std::memory_order_acquire);
        const size_t count = std::min(maxSamples, size_t(write-read));
        size_t start = size_t(read) & kMask;
        size_t first = std::min(count,kCapacity-start);
        std::memcpy(destination,data_.data()+start,first*sizeof(float));
        if (first<count) std::memcpy(destination+first,data_.data(),(count-first)*sizeof(float));
        consumed_.store(read+count,std::memory_order_release);
        return count;
    }
    bool empty() const noexcept {
        return produced_.load(std::memory_order_acquire) ==
               consumed_.load(std::memory_order_acquire);
    }
};
struct Capture {
    Ring ring;
    uint64_t limitFrames = 0;
    uint64_t capturedFrames = 0; // only audio callback accesses this
    int channels = 2;
    std::atomic<bool> overflow{false};
};
int callback(const void* input, void*, unsigned long frames,
             const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags,
             void* user) noexcept {
    auto& capture = *static_cast<Capture*>(user);
    const uint64_t left = capture.limitFrames-capture.capturedFrames;
    const size_t accepted = size_t(std::min(left,uint64_t(frames)));
    if (!capture.ring.push(static_cast<const float*>(input), accepted*size_t(capture.channels))) {
        capture.overflow.store(true,std::memory_order_release);
        return paAbort;
    }
    capture.capturedFrames += accepted;
    return accepted < frames || capture.capturedFrames >= capture.limitFrames ? paComplete : paContinue;
}
class AudioRuntime {
public:
    AudioRuntime() {
        const PaError err = Pa_Initialize();
        if (err != paNoError) throw std::runtime_error(Pa_GetErrorText(err));
    }
    ~AudioRuntime() { Pa_Terminate(); }
};
void listDevices() {
    AudioRuntime context;
    const int count=Pa_GetDeviceCount();
    if (count<0) throw std::runtime_error(Pa_GetErrorText(count));
    for(int i=0;i<count;++i) {
        const auto* device=Pa_GetDeviceInfo(i);
        if (!device || device->maxInputChannels<=0) continue;
        std::cout<<i<<" | "<<device->name<<" | in="<<device->maxInputChannels
                 <<" | sampleRate="<<device->defaultSampleRate<<"\n";
    }
}
void makeTestFile(const fs::path& path) {
    WaveFile output(path,48000,2);
    std::array<float,2048> values{};
    constexpr size_t totalFrames=24000;
    for(size_t frame=0;frame<totalFrames;) {
        const size_t n=std::min(totalFrames-frame,values.size()/2);
        for(size_t i=0;i<n;++i) {
            const float val=float(std::sin(2*kPi*440.0*double(frame+i)/48000.0)*0.5);
            values[2*i]=val;values[2*i+1]=val;
        }
        output.writeSamples(values.data(),n*2);
        frame += n;
    }
    output.finish();
    require(output.frames()==24000,"Self-test frame count mismatch");
    std::cout<<"Created synthetic NoeMixerr WAV: "<<path<<"\n";
}
void record(const fs::path& path, unsigned seconds, int rate, int channels) {
    require(seconds>=1&&seconds<=3600,"seconds must be 1..3600");
    require(rate>=8000&&rate<=96000,"rate must be 8000..96000");
    require(channels==1||channels==2,"channels must be 1 or 2");
    require(uint64_t(seconds)*unsigned(rate)*unsigned(channels)*2 < UINT32_MAX-36ULL,
            "WAV size would exceed RIFF format");
    AudioRuntime context;
    Capture capture;
    capture.limitFrames=uint64_t(seconds)*unsigned(rate);
    capture.channels=channels;
    PaStream* raw=nullptr;
    PaError rc=Pa_OpenDefaultStream(&raw,channels,0,paFloat32,double(rate),256,callback,&capture);
    if(rc!=paNoError) throw std::runtime_error(Pa_GetErrorText(rc));
    struct StreamGuard {
        PaStream* handle;
        ~StreamGuard(){if(handle){Pa_StopStream(handle);Pa_CloseStream(handle);}}
    } stream{raw};
    WaveFile output(path,rate,channels);
    std::atomic<bool> done{false};
    std::exception_ptr writerFailure;
    std::thread writer([&]{
        try {
            std::array<float,4096> block{};
            while (!done.load(std::memory_order_acquire) || !capture.ring.empty()) {
                const size_t count=capture.ring.pop(block.data(),block.size());
                if(count) output.writeSamples(block.data(),count);
                else std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        } catch (...) {
            writerFailure=std::current_exception();
            done.store(true,std::memory_order_release);
        }
    });
    try {
        rc=Pa_StartStream(raw);
        if(rc!=paNoError) throw std::runtime_error(Pa_GetErrorText(rc));
        while(Pa_IsStreamActive(raw)==1 && !capture.overflow.load(std::memory_order_acquire)
              && !done.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        rc=Pa_IsStreamActive(raw);
        if(rc<0) throw std::runtime_error(Pa_GetErrorText(rc));
        Pa_StopStream(raw);
    } catch (...) {
        done.store(true,std::memory_order_release);
        writer.join();
        throw;
    }
    done.store(true,std::memory_order_release);
    writer.join();
    if(writerFailure) std::rethrow_exception(writerFailure);
    require(!capture.overflow.load(std::memory_order_acquire),"Audio buffer overrun; recording discarded");
    require(output.frames()==capture.limitFrames,"Recorded frame count mismatch");
    output.finish();
    std::cout<<"Recorded "<<output.frames()<<" frames to "<<path<<"\n";
}
void usage() {
    std::cout<<"NoeMixerr capture (PortAudio, 0.4.0)\n"
      <<"  noemixerr-recorder --devices\n"
      <<"  noemixerr-recorder --self-test <file.wav>\n"
      <<"  noemixerr-recorder --output <file.wav> [--seconds 10] [--rate 48000] [--channels 2]\n";
}
}
int main(int argc,char** argv){
    try {
        if(argc==2 && std::string(argv[1])=="--devices"){listDevices();return 0;}
        if(argc==3 && std::string(argv[1])=="--self-test"){makeTestFile(argv[2]);return 0;}
        if(argc==2 && std::string(argv[1])=="--help"){usage();return 0;}
        std::string file;
        unsigned seconds=10;int rate=48000,channels=2;
        for(int i=1;i<argc;++i) {
            const std::string flag=argv[i];
            require(i+1<argc,"Missing argument value");
            const std::string arg=argv[++i];
            if(flag=="--output") file=arg;
            else if(flag=="--seconds") seconds=unsigned(std::stoul(arg));
            else if(flag=="--rate") rate=std::stoi(arg);
            else if(flag=="--channels") channels=std::stoi(arg);
            else throw std::runtime_error("Unknown option: "+flag);
        }
        if(file.empty()){usage();return 2;}
        record(file,seconds,rate,channels);
        return 0;
    }catch(const std::exception& e) {
        std::cerr<<"NoeMixerr capture: "<<e.what()<<"\n";
        return 1;
    }
}
