#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <iomanip>
#include "piece.h"

class chessboard{
public:
  enum size{LEN=15,MAXNUM=225}; //棋盘尺寸
  enum state{empty=0,black=1,white=2}; //棋盘位置状态
  chessboard();
  ~chessboard();
  bool istaken(int,int); //该位置是否落子
  bool isempty(void); //棋盘是否为空
  bool isfull(void); //棋盘是否满了
  bool isbound(int,int); //落子位置是否在棋盘内
  int getn(void); //目前棋盘棋子数量
  state gets(int,int); //获取该位置状态
  bool sets(int,int,state); //改变该位置状态
  void show(point*); //展示棋盘
private:
  int num;
  state array[LEN][LEN];
  void line_draw(int,int); //绘制边界
  void chess_draw(int,int,state,point*); //绘制边界或棋子
};


#endif
