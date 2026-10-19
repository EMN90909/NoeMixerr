#include "noemix/core.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#define CHECK(x) do{if(!(x))throw std::runtime_error("FAILED: " #x);}while(false)
int main(){
 auto p=noemix::demo_project();
 CHECK(p.tracks.size()==3);
 auto out=noemix::render(p,8000);
 CHECK(out.size()>10000);
 double energy=0;
 for(float x:out){CHECK(std::isfinite(x));energy+=double(x)*x;}
 CHECK(energy>1);
 auto muted=p;
 for(auto& t:muted.tracks)t.mute=true;
 auto quiet=noemix::render(muted,8000);
 CHECK(std::all_of(quiet.begin(),quiet.end(),[](float x){return x==0.f;}));
 auto solo=p;solo.tracks.front().solo=true;solo.tracks.front().mute=true;
 quiet=noemix::render(solo,8000);
 CHECK(std::all_of(quiet.begin(),quiet.end(),[](float x){return x==0.f;}));
 noemix::write_wav(p,"test.wav",8000);
 auto clip=noemix::read_wav("test.wav");
 CHECK(clip.channels==2&&clip.sample_rate==8000&&clip.pcm.size()==out.size());
 auto original=p;
 original.tracks[0].clips.push_back(clip);
 noemix::save_project(original,"test.noemix");
 auto reopened=noemix::open_project("test.noemix");
 CHECK(reopened.tracks[0].clips.size()==1);
 CHECK(reopened.tracks[1].notes.size()==32);
 CHECK(reopened.tracks[0].clips[0].pcm.size()==out.size());
 auto rendered=noemix::render(reopened,8000);
 CHECK(rendered.size()>0);
 bool invalid=false;
 try{auto bad=p;bad.bpm=0;noemix::render(bad);}catch(const std::exception&){invalid=true;}
 CHECK(invalid);
 std::ofstream corrupt("bad.noemix");corrupt<<"NOEMIX 1\n\"oops\" 120 900000\n";corrupt.close();
 invalid=false;try{(void)noemix::open_project("bad.noemix");}catch(const std::exception&){invalid=true;}
 CHECK(invalid);
 std::remove("test.wav");std::remove("test.noemix");std::remove("bad.noemix");
 std::cout<<"NoeMixerr C++ core tests passed\n";
}
