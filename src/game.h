#ifndef GAME_H
#define GAME_H
#include "judge.h"
#include "player.h"

class chessgame{
public:
  chessgame();
};

chessgame::chessgame(){
  int b=0,w=0;
  player *bplayer,*wplayer;
  myjudge mj;
  while(b<=0||b>2){
    std::cout<<"选择黑方为：（1：电脑；2：玩家）"<<std::endl;
    if(!(std::cin>>b)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  while(w<=0||w>2){
    std::cout<<"选择白方为：（1：电脑；2：玩家）"<<std::endl;
    if(!(std::cin>>w)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  if(b==1)bplayer=new myplayer();
  else bplayer=new yourplayer();
  if(w==1)wplayer=new myplayer();
  else wplayer=new yourplayer();

  while(!mj.iswin())mj.intern(bplayer, wplayer);
  mj.end();
}

#endif
