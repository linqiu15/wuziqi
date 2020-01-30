#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "response.h"
#include "chessboard.h"
#include "piece.h"
#include "handle.h"

class player{
public:
  virtual response* send_response(chessboard*,point*)=0; //做出回应
  virtual point* send_point(chessboard*,point*)=0; //决策落子
  virtual bool allow_withdraw(chessboard*,point*)=0; //是否允许悔棋
};

//五元组评分法
class myplayer :public player{
public:
  myplayer():scoretable{7,35,800,15000,800000,15,400,1800,100000,0,0},vec{{1,-1},{1,0},{1,1},{0,1}}{};//借鉴网上的评分表
  virtual response* send_response(chessboard*,point*);
  virtual point* send_point(chessboard*,point*);
  virtual bool allow_withdraw(chessboard*,point*);
private:
  const long scoretable[11];//BLANK,S,SS,SSS,SSSS,D,DD,DDD,DDDD,NULL,BOTH
  const int vec[4][2]; //四个方向矢量
  long get_score(int,int); //给五元组打分
  long mark_vec(chessboard*,int,int,chessboard::state,int,int); //给定位置，给定方向五元组分数
  long mark(chessboard*,int,int,chessboard::state);//给定位置，所有方向的所有五元组分数和
  handle hd;
};

class yourplayer :public player{
  virtual response* send_response(chessboard*,point*);
  virtual point* send_point(chessboard*,point*);
  virtual bool allow_withdraw(chessboard*,point*);
};


#endif
