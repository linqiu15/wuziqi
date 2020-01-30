#ifndef PIECE_H
#define PIECE_H

class point{
public:
  point(int x,int y):m_x(x),m_y(y){}
  ~point(){}
  int getx(void){return m_x;} //获取x坐标
  int gety(void){return m_y;} //获取y坐标
protected:
  int m_x;
  int m_y;
};


class piece :public point{
public:
  enum color{black=1,white=2};
  piece(int x,int y,color c):point(x,y),m_c(c){};
  piece(point *p,color c):point(p->getx(),p->gety()),m_c(c){};
  ~piece(){};
  color getc(void){return m_c;} //获取棋子颜色
protected:
  color m_c;
};


#endif

