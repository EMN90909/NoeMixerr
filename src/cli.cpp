#include "noemix/core.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
int main(int argc,char** argv){
 try{
  if(argc==3&&std::string(argv[1])=="demo"){
   noemix::save_project(noemix::demo_project(),argv[2]);
   std::cout<<"Demo project saved: "<<argv[2]<<"\n";return 0;
  }
  if(argc==4&&std::string(argv[1])=="render"){
   const auto p=noemix::open_project(argv[2]);
   noemix::write_wav(p,argv[3]);
   std::cout<<"Rendered WAV: "<<argv[3]<<"\n";return 0;
  }
  if(argc==3&&std::string(argv[1])=="inspect"){
   const auto p=noemix::open_project(argv[2]);
   std::cout<<p.name<<" | "<<p.bpm<<" BPM | "<<p.tracks.size()<<" tracks\n";
   return 0;
  }
  if(argc==3&&std::string(argv[1])=="render-demo"){
   noemix::write_wav(noemix::demo_project(),argv[2]);
   std::cout<<"Demo mix exported: "<<argv[2]<<"\n";return 0;
  }
  std::cerr<<"NoeMixerr CLI\n"
      "  noemixerr-cli demo <session.noemix>\n"
      "  noemixerr-cli render <session.noemix> <mix.wav>\n"
      "  noemixerr-cli inspect <session.noemix>\n"
      "  noemixerr-cli render-demo <mix.wav>\n";
  return 2;
 }catch(const std::exception& e){std::cerr<<"NoeMixerr: "<<e.what()<<"\n";return 1;}
}
