#ifndef JUDGE_H
#define JUDGE_H
#include <fstream>
#include <string>
#include "chessboard.h"
#include "chessstack.h"
#include "response.h"
#include "player.h"
#include "handle.h"

class judge{
public:
  virtual bool iswin(void)=0; //是否结束
  virtual void intern(player*,player*)=0; //下一步
  virtual void end(void)=0; //结束游戏
};

class myjudge :public judge{
public:
  myjudge();
  ~myjudge();
  virtual bool iswin(void);
  virtual void intern(player*,player*);
  virtual void end(void);
private:
  bool win; //是否赢局
  bool white; //是否白方
  chessstack jcs;
  chessboard jcb;
  handle hd;
  bool isequal(bool,piece::color); //颜色和玩家是否对应
  bool judge_win(void); //判断是否赢局
  bool deal_put(player*); //处理落子
  bool deal_withdraw(player*); //处理悔棋
  bool record_chess(void);//记录棋局
  bool show_record(void);//查看棋局
};


#endif
