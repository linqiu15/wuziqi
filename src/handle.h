#ifndef HANDLE_H
#define HANDLE_H
#include "chessboard.h"
#include "piece.h"

class handle{
public:
  enum type{none,l3,l4,l5,ll}; //无，活三，（半）活四，五连，长连
  handle();
  ~handle();
  type get_type(chessboard*,point*,int,int); //给定位置，给定方向类型
  bool check_prohibit(chessboard*,point*); //检查给定位置是否（将）形成禁手
  bool isfive(chessboard*,point*); //是否形成连五
private:
  const int vec[4][2]; //四个方向矢量
  int single_find_same(chessboard*,piece*,int,int); //给定位置、给定单方向最大同颜色棋子数（不包括自身）
  int double_find_same(chessboard*,piece*,int,int); //给定位置、给定双方向最大同颜色棋子数（不包括自身）
  int distance_xboarder(int); //x方向距边界位置
  int distance_yboarder(int); //y方向距边界位置
};


#endif
