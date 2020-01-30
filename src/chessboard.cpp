#include "chessboard.h"

template<typename T> void align_print(T a){
  std::cout<<std::setw(4)<<std::setiosflags(std::ios::left)<<a;
}

chessboard::chessboard(){
  num=0;
  int tmp_len=LEN;
  for(int i=0;i<tmp_len;i++){
    for(int j=0;j<tmp_len;j++){
      array[i][j]=empty;
    }
  }
}

chessboard::~chessboard(){}

bool chessboard::istaken(int x, int y){
  if(!isbound(x,y))return false;
  return array[x][y]!=empty;
}

bool chessboard::isempty(){
  return num==0;
}

bool chessboard::isfull(){
  return num==MAXNUM;
}

bool chessboard::isbound(int x, int y){
  return 0<=x&&x<LEN&&0<=y&&y<LEN;
}

int chessboard::getn(void){
  return num;
}

chessboard::state chessboard::gets(int x, int y){
  return array[x][y];
} 

bool chessboard::sets(int x, int y,state s){
  if(!isbound(x, y))return false;
  if(istaken(x, y)){
    if(s==empty)num--;
  }else{
    if(s!=empty)num++;
  }
  array[x][y]=s;
  return true;
}

void chessboard::line_draw(int x,int y){
  const char shape[9][4]={"└","┴","┘","├","┼","┤","┌","┬","┐"};
  if(x==0){
    if(y==0){align_print(shape[0]);}
    else if(y==14){align_print(shape[2]);}
    else{align_print(shape[1]);}
  }else if(x==14){
    if(y==0){align_print(shape[6]);}
    else if(y==14){align_print(shape[8]);}
    else{align_print(shape[7]);}
  }else{
    if(y==0){align_print(shape[3]);}
    else if(y==14){align_print(shape[5]);}
    else{align_print(shape[4]);}
  }
}

void chessboard::chess_draw(int x,int y,chessboard::state s,point *p){
  const char shape[4][4]={"●","○","▲","△"};
  if(p==NULL||s==chessboard::empty){
    line_draw(x, y);
  }else if(s==chessboard::black){
    if(x==p->getx()&&y==p->gety()){align_print(shape[2]);}
    else{align_print(shape[0]);}
  }else{
    if(x==p->getx()&&y==p->gety()){align_print(shape[3]);}
    else{align_print(shape[1]);}
  }
}

void chessboard::show(point *p){
  std::cout<<std::endl;
  for(int i=(chessboard::LEN-1);i>=0;i--){
    align_print(i+1);
    for(int j=0;j<chessboard::LEN;j++)chess_draw(i, j, array[i][j], p);
    std::cout<<std::endl;
  }
  std::cout<<"    A B C D E F G H I J K L M N O"<<std::endl;
  std::cout<<std::endl;
}
