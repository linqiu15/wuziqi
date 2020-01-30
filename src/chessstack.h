#ifndef CHESSSTACK_H
#define CHESSSTACK_H
#include <iostream>
#include <stack>
#include "piece.h"
#include "chessboard.h"

class chessstack{
public:
  chessstack();
  ~chessstack();
  piece* get_last_piece(void); //最近一次棋子
  bool pop(void); //弹出棋子
  bool push(piece* p); //压入棋子
  bool isempty(void); //栈是否为空
  int getn(void); //获取栈的棋子数量
  void replay(); //复盘
private:
  int num;
  std::stack<piece*> s;
};

#endif
