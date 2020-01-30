#include "player.h"

// My player-robot
response* myplayer::send_response(chessboard *cb, point *p){
  if(p!=NULL&&cb->gets(p->getx(), p->gety())==chessboard::black&&hd.check_prohibit(cb, p))
    return new prohibit();
  return new put();
}

long myplayer::get_score(int m,int n){
  if(m>0&&n>0)
    return scoretable[10];
  else if(m==0&&n==0)
    return scoretable[0];
  else if(m==0)
    return scoretable[n+4];
  return scoretable[m];
}

long myplayer::mark_vec(chessboard *cb,int px,int py,chessboard::state s,int xdir,int ydir){
  if(!(cb->isbound(px, py)&&cb->isbound(px+4*xdir, py+4*ydir)))
    return scoretable[9];
  int m=0,n=0;
  for(int i=0;i<5;i++){
    chessboard::state tmps=cb->gets(px, py);
    px+=xdir;
    py+=ydir;
    if(tmps==chessboard::empty)continue;
    else if(tmps==s)m++;
    else n++;
  }
  return get_score(m, n);
}

long myplayer::mark(chessboard *cb,int px,int py,chessboard::state s){
  long rl=0;
  for(int i=0;i<4;i++){
    for(int j=0;j<5;j++){
      rl+=mark_vec(cb, px-j*vec[i][0],py-j*vec[i][1], s, vec[i][0], vec[i][1]);
    }
  }
  return rl;
}

point* myplayer::send_point(chessboard *cb,point *p){
  if(cb->isempty())return new point(7,7);
  chessboard::state s=(cb->gets(p->getx(), p->gety())==chessboard::black)?chessboard::white:chessboard::black;
  long tmpv=0,current_max=0;
  int rx=0,ry=0;
  for(int i=0;i<15;i++){
    for(int j=0;j<15;j++){
      if(!cb->istaken(i, j)&&(tmpv=mark(cb, i, j, s))>current_max){
	if(s==chessboard::black&&hd.check_prohibit(cb, new point(i,j)))continue;
	else rx=i,ry=j,current_max=tmpv;
      }
    }
  }
  return new point(rx,ry);
}

bool myplayer::allow_withdraw(chessboard *cb, point *p){return true;}


// Your player-human
response* yourplayer::send_response(chessboard *cb, point *p){
  int i=0;
  response *r;
  while(i<=0||i>4){
    std::cout<<"请输入您下一步的回应(1:下棋；2：悔棋；3：认输；4：指出禁手)：";
    if(!(std::cin>>i)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  switch(i){
  case 1:
    r=new put();
    break;
  case 2:
    r=new withdraw();
    break;
  case 3:
    r=new giveup();
    break;
  case 4:
    r=new prohibit();
    break;
  }
  return r;
}
  
point* yourplayer::send_point(chessboard *cb, point *p){
  int px=0;
  char py='@';
  while(px<1||px>15||py<'A'||py>'O'){
    std::cout<<"请输入落子位置(如: A5): ";
    std::cin>>py;
    if(!(std::cin>>px)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  return new point(px-1,int(py-'A'));
}

bool yourplayer::allow_withdraw(chessboard *cb, point *p){
  int i=0;
  while(i<1||i>2){
    std::cout<<"是否允许悔棋？(1:不允许；2：允许): ";
    if(!(std::cin>>i)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  return (bool)(i-1);
}
