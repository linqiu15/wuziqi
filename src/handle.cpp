#include "handle.h"

handle::handle():vec{{1,0},{1,1},{0,1},{-1,1}}{}
handle::~handle(){}

int handle::distance_xboarder(int x){return (x<8)?x:(14-x);}
int handle::distance_yboarder(int y){return (y<8)?y:(14-y);}

int handle::single_find_same(chessboard *cb,piece *pi,int xvec,int yvec){
  int num=0,x0=pi->getx()+xvec,y0=pi->gety()+yvec;
  chessboard::state tmps=(chessboard::state)pi->getc();
  while(cb->isbound(x0, y0)&&tmps==cb->gets(x0, y0)){
    x0+=xvec;
    y0+=yvec;
    num++;
  }
  return num;
}

int handle::double_find_same(chessboard *cb,piece *pi,int xdir,int ydir){
  return single_find_same(cb, pi, xdir, ydir)+single_find_same(cb, pi, -xdir, -ydir);
}

handle::type handle::get_type(chessboard *cb, point *p, int xdir, int ydir){
  chessboard::state csb=chessboard::black,csw=chessboard::white,cse=chessboard::empty;
  int xi=p->getx(),yi=p->gety();
  if(cb->gets(xi, yi)!=csb)return handle::none;
  piece *tmpp=new piece(p,piece::black);
  int num_front=single_find_same(cb, tmpp, xdir, ydir),num_back=single_find_same(cb, tmpp, -xdir, -ydir);
  int num=num_front+num_back+1;

  if(num==5)return l5;
  if(num>5)return ll;

  int xfront=xi+(num_front+1)*xdir,yfront=yi+(num_front+1)*ydir;
  int xback=xi-(num_back+1)*xdir,yback=yi-(num_back+1)*ydir;

  //活
  if(cb->isbound(xfront, yfront)&&cb->isbound(xback, yback)&&cb->gets(xfront, yfront)==cse&&cb->gets(xback, yback)==cse){
    if(num==1){
      if(distance_xboarder(xfront)>2&&distance_yboarder(yfront)>2){
	if(cb->gets(xfront+xdir, yfront+ydir)==csb&&cb->gets(xfront+2*xdir, yfront+2*ydir)==csb&&cb->gets(xfront+3*xdir, yfront+3*ydir)==cse)
	  num+=2;
      }else if(distance_xboarder(xback)>2&&distance_yboarder(yback)>2){
	if(cb->gets(xback-xdir,yback-ydir)==csb&&cb->gets(xback-2*xdir, yback-2*ydir)==csb&&cb->gets(xback-3*xdir,yback-3*ydir)==cse)
	  num+=2;
      }
    }else if(num==2){
      if(distance_xboarder(xfront)>1&&distance_yboarder(yfront)>1){
	if(cb->gets(xfront+xdir,yfront+ydir)==csb&&cb->gets(xfront+2*xdir, yfront+2*ydir)==cse)
	  num+=1;
      }else if(distance_xboarder(xback)>1&&distance_yboarder(yback)>1){
	if(cb->gets(xback-xdir, yback-ydir)==csb&&cb->gets(xback-2*xdir, yback-2*ydir)==cse)
	  num+=1;
      }
    }    
    if(num==3)return handle::l3;
    if(num==4)return handle::l4;
    //半活
  }else if(!cb->isbound(xfront, yfront)||cb->gets(xfront, yfront)==csw){
    if(cb->isbound(xback, yback)&&cb->gets(xback, yback)==cse&&num==4)return handle::l4;
  }else if(!cb->isbound(xback, yback)||cb->gets(xback,yback)==csw){
    if(cb->isbound(xfront, yfront)&&cb->gets(xfront,yfront)==csw&&num==4)return handle::l4;
  }
  return handle::none;
}

bool handle::check_prohibit(chessboard *cb, point *p){
  handle::type t;
  int n3=0,n4=0,nl=0;
  for(int i=0;i<4;i++){
    t=get_type(cb, p, vec[i][0], vec[i][1]);
    if(t==handle::l5)
      return false;
    else if(t==handle::ll)
      nl++;
    else if(t==handle::l3)
      n3++;
    else if(t==handle::l4)
      n4++;
  }
  return n3>1||n4>1||nl>0;
}

bool handle::isfive(chessboard *cb, point *p){
  int x=p->getx(),y=p->gety();
  chessboard::state s;
  if((s=cb->gets(x, y))==chessboard::empty)return false;
  int i;
  piece *tmp_pi=new piece(p,(piece::color)s);
  for(i=0;i<4&&double_find_same(cb, tmp_pi, vec[i][0], vec[i][1])!=4;i++){}
  return i<4;
}
