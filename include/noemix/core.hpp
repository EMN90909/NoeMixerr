#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace noemix {
struct Note {
 int pitch=60;
 double beat=0;
 double length=1;
 float velocity=0.8f;
};
struct AudioClip {
 std::string path;
 double beat=0;
 int sample_rate=0;
 int channels=0;
 std::vector<float> pcm;
};
struct Track {
 std::string name="Track";
 double gain=0.8;
 double pan=0;
 bool mute=false,solo=false;
 int waveform=0; // 0=sine, 1=sawtooth
 std::vector<Note> notes;
 std::vector<AudioClip> clips;
};
struct Project {
 std::string name="Untitled";
 double bpm=120;
 std::vector<Track> tracks;
};
void validate(const Project&);
AudioClip read_wav(const std::string& path);
void save_project(const Project&,const std::string& path);
Project open_project(const std::string& path);
double duration(const Project&);
std::vector<float> render(const Project&,int sample_rate=44100);
void write_wav(const Project&,const std::string&,int rate=44100);
Project demo_project();
} // namespace noemix
