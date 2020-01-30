#include "chessstack.h"

chessstack::chessstack():num(0){}

chessstack::~chessstack(){}

piece* chessstack::get_last_piece(void){
  if(s.empty())return NULL;
  return s.top();
}

bool chessstack::pop(void){
  if(s.empty()){return false;}
  else{
    s.pop();
    num--;
  }
  return true;
}

bool chessstack::push(piece *p){
  piece::color tmp_c=p->getc();
  if(!s.empty()&&s.top()->getc()==tmp_c){
    return false;
  }else if(s.empty()&&tmp_c==piece::white){
    return false;
  }else{
    s.push(p);
    num++;
  }
  return true;
}

bool chessstack::isempty(void){
  return s.empty();
}

int chessstack::getn(void){return num;}

void chessstack::replay(){
  std::stack<piece*> tmp_s;
  chessboard tmp_cb;
  piece* tmp_pi;
  //reverse
  while(!s.empty()){
    tmp_s.push(s.top());
    s.pop();
  }
  int i=1;
  //replay
  while(!tmp_s.empty()){
    tmp_pi=tmp_s.top();
    tmp_cb.sets(tmp_pi->getx(), tmp_pi->gety(), (chessboard::state)tmp_pi->getc());
    if(i==1){
      tmp_cb.show(tmp_pi);
      std::cout<<"是否继续播放？(1:是；2:否) ";
      if(!(std::cin>>i)){
	std::cin.clear();
	std::cin.ignore(10000, '\n');
      }
    }
    s.push(tmp_pi);
    tmp_s.pop();
  }
}
