#include "noemix/core.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
namespace noemix {
namespace {
constexpr double pi=3.14159265358979323846;
void check(bool ok,const char* msg){if(!ok)throw std::runtime_error(msg);}
uint16_t u16(std::istream& f){unsigned char b[2]{};f.read((char*)b,2);check(bool(f),"Truncated WAV");return uint16_t(b[0])|(uint16_t(b[1])<<8);}
uint32_t u32(std::istream& f){uint32_t a=u16(f),b=u16(f);return a|(b<<16);}
void w16(std::ostream& f,uint16_t v){f.put(char(v&255));f.put(char(v>>8));}
void w32(std::ostream& f,uint32_t v){w16(f,uint16_t(v));w16(f,uint16_t(v>>16));}
}
void validate(const Project& p) {
 check(std::isfinite(p.bpm)&&p.bpm>=20&&p.bpm<=400,"Invalid tempo (20..400 BPM)");
 check(p.tracks.size()<=128,"Too many tracks");
 for(const auto& t:p.tracks){
  check(std::isfinite(t.gain)&&t.gain>=0&&t.gain<=4&&std::isfinite(t.pan)&&t.pan>=-1&&t.pan<=1,"Invalid mixer setting");
  check((t.waveform==0||t.waveform==1)&&t.notes.size()<=10000&&t.clips.size()<=512,"Invalid track");
  for(const auto& n:t.notes)check(n.pitch>=0&&n.pitch<=127&&std::isfinite(n.beat)&&n.beat>=0&&n.beat<=1e6&&std::isfinite(n.length)&&n.length>0&&n.length<=1e5&&std::isfinite(n.velocity)&&n.velocity>=0&&n.velocity<=1,"Invalid note");
  for(const auto& c:t.clips)check(std::isfinite(c.beat)&&c.beat>=0&&c.beat<=1e6&&(c.channels==1||c.channels==2)&&c.sample_rate>=8000&&c.sample_rate<=192000&&!c.pcm.empty()&&c.pcm.size()%size_t(c.channels)==0,"Invalid PCM clip");
 }
}
AudioClip read_wav(const std::string& path){
 std::ifstream f(path,std::ios::binary);check(bool(f),"Cannot open WAV");
 char tag[4];f.read(tag,4);check(bool(f)&&std::memcmp(tag,"RIFF",4)==0,"Expected RIFF");
 (void)u32(f);f.read(tag,4);check(bool(f)&&std::memcmp(tag,"WAVE",4)==0,"Expected WAVE");
 uint16_t fmt=0,ch=0,bits=0;uint32_t rate=0;std::vector<unsigned char> bytes;
 while(f.read(tag,4)){
  uint32_t n=u32(f);check(n<=256u*1024*1024,"WAV chunk too large");
  if(std::memcmp(tag,"fmt ",4)==0){
   check(n>=16,"Bad WAV format");fmt=u16(f);ch=u16(f);rate=u32(f);
   (void)u32(f);(void)u16(f);bits=u16(f);
   f.seekg(std::streamoff(n-16),std::ios::cur);
  }else if(std::memcmp(tag,"data",4)==0){
   bytes.resize(n);f.read((char*)bytes.data(),n);
   check(bool(f),"Truncated WAV data");
  }else f.seekg(std::streamoff(n),std::ios::cur);
  if(n&1)f.seekg(1,std::ios::cur);
  check(bool(f),"Invalid WAV chunk");
 }
 check(fmt==1&&bits==16,"Only 16-bit PCM WAV is supported");
 check((ch==1||ch==2)&&rate>=8000&&rate<=192000,"Unsupported WAV format");
 check(!bytes.empty()&&bytes.size()%(ch*2)==0,"Invalid WAV payload");
 AudioClip out;out.path=path;out.channels=ch;out.sample_rate=int(rate);
 out.pcm.reserve(bytes.size()/2);
 for(size_t i=0;i<bytes.size();i+=2){
  uint16_t raw=uint16_t(bytes[i])|(uint16_t(bytes[i+1])<<8);
  int value=(raw&0x8000)?int(raw)-65536:int(raw);
  out.pcm.push_back(float(value)/32768.f);
 }
 return out;
}
void save_project(const Project& p,const std::string& file){
 validate(p);
 std::ofstream f(file,std::ios::binary|std::ios::trunc);check(bool(f),"Cannot save project");
 f<<"NOEMIX 1\n"<<std::quoted(p.name)<<" "<<std::setprecision(17)<<p.bpm<<" "<<p.tracks.size()<<"\n";
 for(const auto& t:p.tracks){
  f<<std::quoted(t.name)<<" "<<t.gain<<" "<<t.pan<<" "<<t.mute<<" "<<t.solo<<" "<<t.waveform<<" "<<t.notes.size()<<" "<<t.clips.size()<<"\n";
  for(const auto& n:t.notes)f<<n.pitch<<" "<<n.beat<<" "<<n.length<<" "<<n.velocity<<"\n";
  for(const auto& c:t.clips)f<<std::quoted(c.path)<<" "<<c.beat<<"\n";
 }
 check(bool(f),"Project write failed");
}
Project open_project(const std::string& file){
 std::ifstream f(file,std::ios::binary);check(bool(f),"Cannot open project");
 std::string magic;int ver=0;f>>magic>>ver;check(bool(f)&&magic=="NOEMIX"&&ver==1,"Unsupported project format");
 Project p;size_t nt=0;f>>std::quoted(p.name)>>p.bpm>>nt;
 check(bool(f)&&std::isfinite(p.bpm)&&p.bpm>=20&&p.bpm<=400&&nt<=128,"Invalid project header");
 for(size_t i=0;i<nt;++i){
  Track t;size_t nn=0,nc=0;f>>std::quoted(t.name)>>t.gain>>t.pan>>t.mute>>t.solo>>t.waveform>>nn>>nc;
  check(bool(f)&&nn<=10000&&nc<=512,"Invalid track header");
  for(size_t k=0;k<nn;++k){Note n;f>>n.pitch>>n.beat>>n.length>>n.velocity;check(bool(f),"Bad note");t.notes.push_back(n);}
  for(size_t k=0;k<nc;++k){std::string path;double beat=0;f>>std::quoted(path)>>beat;check(bool(f)&&path.size()<4096,"Bad clip");auto c=read_wav(path);c.beat=beat;t.clips.push_back(std::move(c));}
  p.tracks.push_back(std::move(t));
 }
 validate(p);return p;
}
double duration(const Project& p){
 validate(p);double end=1.0;
 for(const auto& t:p.tracks){
  for(const auto& n:t.notes)end=std::max(end,(n.beat+n.length)*60/p.bpm+0.15);
  for(const auto& c:t.clips)end=std::max(end,c.beat*60/p.bpm+double(c.pcm.size()/size_t(c.channels))/c.sample_rate);
 }
 check(end<=3600,"Maximum render length is 1 hour");
 return end+0.25;
}
std::vector<float> render(const Project& p,int rate){
 check(rate>=8000&&rate<=192000,"Unsupported sample rate");
 const double seconds=duration(p);
 const size_t frames=size_t(std::ceil(seconds*rate));
 check(frames<=30000000,"Render exceeds memory budget");
 std::vector<float> output(frames*2,0);
 const bool solo=std::any_of(p.tracks.begin(),p.tracks.end(),[](const Track& t){return t.solo;});
 for(const auto& t:p.tracks){
  if(t.mute||(solo&&!t.solo))continue;
  double left=t.gain*std::sqrt((1-t.pan)*0.5);
  double right=t.gain*std::sqrt((1+t.pan)*0.5);
  for(const auto& n:t.notes){
   const double start=n.beat*60/p.bpm;
   const double end=(n.beat+n.length)*60/p.bpm;
   const size_t first=std::min(frames,size_t(start*rate));
   const size_t last=std::min(frames,size_t(std::ceil((end+0.1)*rate)));
   const double freq=440*std::pow(2.,(n.pitch-69)/12.);
   for(size_t i=first;i<last;++i){
    const double sec=double(i)/rate,age=std::max(0.,sec-start);
    const double envelope=(sec>end)?std::max(0.,1-(sec-end)/0.1):std::min(1.,age/0.006);
    const double phase=2*pi*freq*age;
    const double oscillator=t.waveform==0?std::sin(phase):(2.*(phase/(2*pi)-std::floor(phase/(2*pi)+0.5)));
    const float sample=float(oscillator*envelope*n.velocity*0.23);
    output[i*2]+=float(sample*left);output[i*2+1]+=float(sample*right);
   }
  }
  for(const auto& c:t.clips){
   const size_t first=std::min(frames,size_t(c.beat*60/p.bpm*rate));
   const size_t nframes=c.pcm.size()/size_t(c.channels);
   for(size_t i=first;i<frames;++i){
    const double source=double(i-first)*c.sample_rate/rate;
    const size_t j=size_t(source);
    if(j>=nframes)break;
    const size_t next=std::min(j+1,nframes-1);
    const float frac=float(source-j);
    const float a=c.pcm[j*c.channels]*(1-frac)+c.pcm[next*c.channels]*frac;
    const int rc=c.channels==2?1:0;
    const float b=c.pcm[j*c.channels+rc]*(1-frac)+c.pcm[next*c.channels+rc]*frac;
    output[i*2]+=float(a*left);output[i*2+1]+=float(b*right);
   }
  }
 }
 for(float& x:output)x=std::clamp(x,-1.f,1.f);
 return output;
}
void write_wav(const Project& p,const std::string& path,int rate){
 const auto data=render(p,rate);
 check(data.size()<=size_t(std::numeric_limits<uint32_t>::max()-36)/2,"WAV too large");
 std::ofstream f(path,std::ios::binary|std::ios::trunc);check(bool(f),"Cannot create WAV output");
 f.write("RIFF",4);w32(f,uint32_t(data.size()*2+36));f.write("WAVEfmt ",8);
 w32(f,16);w16(f,1);w16(f,2);w32(f,rate);w32(f,rate*4);w16(f,4);w16(f,16);
 f.write("data",4);w32(f,uint32_t(data.size()*2));
 for(float x:data)w16(f,uint16_t(int16_t(std::lround(x*32767))));
 check(bool(f),"WAV write failed");
}
Project demo_project(){
 Project p;p.name="NoeMixerr Session";p.bpm=126;
 Track kick;kick.name="Bass";kick.waveform=1;kick.gain=0.7;
 Track lead;lead.name="Lead";lead.gain=0.6;lead.pan=0.12;
 Track chords;chords.name="Chords";chords.gain=0.4;chords.pan=-0.14;
 const int roots[]={48,45,41,43};
 for(int bar=0;bar<4;++bar){
  for(int j=0;j<4;++j)kick.notes.push_back({roots[bar],double(bar*4+j),0.75f,0.6f});
  for(int j=0;j<8;++j)lead.notes.push_back({roots[bar]+12+(j%3)*2,bar*4+j*0.5,0.4f,0.62f});
  for(int n:{0,3,7})chords.notes.push_back({roots[bar]+12+n,double(bar*4),3.7f,0.42f});
 }
 p.tracks={kick,lead,chords};return p;
}
} // namespace noemix
