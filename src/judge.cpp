#include <iostream>
#include "judge.h"


myjudge::myjudge():win(false),white(false){}
myjudge::~myjudge(){}

bool myjudge::iswin(){return win;}

bool myjudge::isequal(bool b,piece::color c){return b==(bool)(c-1);}

bool myjudge::judge_win(void){
  if(hd.isfive(&jcb, jcs.get_last_piece())){
    win=true;
    return true;
  }
  return false;
}

bool myjudge::deal_put(player *pl){
  point *p=pl->send_point(&jcb, jcs.get_last_piece());
  int tmp_x=p->getx(),tmp_y=p->gety();
  if(!jcb.isbound(tmp_x,tmp_y)||jcb.istaken(tmp_x, tmp_y)){
    std::cout<<"落子失败!"<<std::endl;
    return false;
  }else{
    if(jcs.get_last_piece()==NULL||jcs.get_last_piece()->getc()==piece::white){
      jcb.sets(tmp_x, tmp_y, chessboard::black);
      jcs.push(new piece(p,piece::black));
    }else{
      jcb.sets(tmp_x, tmp_y, chessboard::white);
      jcs.push(new piece(p,piece::white));
    }
  }
  return true;
}

bool myjudge::deal_withdraw(player *pl){
  if(pl->allow_withdraw(&jcb, jcs.get_last_piece())){
    piece *pi=jcs.get_last_piece();
    jcb.sets(pi->getx(), pi->gety(), chessboard::empty);
    jcs.pop();
    pi=jcs.get_last_piece();
    jcb.sets(pi->getx(), pi->gety(), chessboard::empty);
    jcs.pop();
    return true;
  }
  return false;
}

void myjudge::intern(player *pl1, player *pl2){
  jcb.show(jcs.get_last_piece());
  if(!white){
    response *r=pl1->send_response(&jcb, jcs.get_last_piece());
    response::type rt=r->get_response_type();
    if(rt==response::put){
      while(!deal_put(pl1)){}
      if(!judge_win())white=!white;
    }
    else if(rt==response::withdraw){
      if(!jcs.isempty()&&!deal_withdraw(pl2)){
	while(!deal_put(pl1)){}
	if(!judge_win())white=!white;
      }
    }
    else if(rt==response::giveup){
      white=!white;
      win=true;
    }else{
      std::cout<<"你无权指出禁手!"<<std::endl;
    }
  }else{
    response *r=pl2->send_response(&jcb, jcs.get_last_piece());
    response::type rt=r->get_response_type();
    if(rt==response::put){
      while(!deal_put(pl2)){}
      if(!judge_win())white=!white;
    }
    else if(rt==response::withdraw){
      if(!deal_withdraw(pl1)){
	while(!deal_put(pl2)){}
	if(!judge_win())white=!white;
      }
    }
    else if(rt==response::giveup){
      white=!white;
      win=true;
    }else{
      if(hd.check_prohibit(&jcb, jcs.get_last_piece())){
	win=true;
      }else{
	std::cout<<"你错误地指出了禁手!"<<std::endl;
      }
    }
  }
}

bool myjudge::record_chess(void){
  std::string cname,filename;
  std::cout<<"请输入对局文件名: ";
  std::cin>>cname;
  filename="../data/"+cname+".dat";
  std::ofstream outfile(filename.c_str());
  if(!outfile){
    std::cout<<"记录棋局失败！"<<std::endl;
    return false;
  }
  chessstack tmp_cs;
  piece *tmp_pi;
  while(!jcs.isempty()){
    tmp_pi=jcs.get_last_piece();
    tmp_cs.push(tmp_pi);
    jcs.pop();
  }
  while(!tmp_cs.isempty()){
    tmp_pi=tmp_cs.get_last_piece();
    outfile<<tmp_pi->getx()<<" "<<tmp_pi->gety()<<" "<<tmp_pi->getc()<<std::endl;
    jcs.push(tmp_pi);
    tmp_cs.pop();
  }
  outfile.close();
  std::cout<<"记录棋局成功！"<<std::endl;
  return true;
}

bool myjudge::show_record(void){
  std::string filename,line;
  std::cout<<"请输入对局文件名: ";
  std::cin>>filename;
  std::string ofilename="../data/"+filename+".dat";
  std::ifstream infile(ofilename);
  if(!infile){
    std::cout<<"打开记录失败!"<<std::endl;
    return false;
  }
  int tmpx,tmpy,tmps;
  chessboard tmp_cb;
  bool exit=false;
  while(!exit&&getline(infile,line)){
    int i=0;
    std::stringstream ss(line);
    ss>>tmpx;
    ss>>tmpy;
    ss>>tmps;
    tmp_cb.sets(tmpx, tmpy, (chessboard::state)tmps);
    tmp_cb.show(new point(tmpx,tmpy));
    std::cout<<"是否继续?(1:是；2：否)"<<std::endl;
    if(!(std::cin>>i)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }else{
      exit=(i==1)?false:true;
    }
  }
  infile.close();
  return true;
}

void myjudge::end(void){
  jcb.show(jcs.get_last_piece());
  if(!white){
    std::cout<<"恭喜黑方获胜！"<<std::endl;
  }else{
    std::cout<<"恭喜白方获胜！"<<std::endl;
  }
  bool exit=false;
  while(!exit){
    std::cout<<"接下来想干什么？(1:复盘；2:记录棋局；3:查看棋局;4:退出)"<<std::endl;
    int i;
    while(!(std::cin>>i)){
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
    switch(i){
    case 1:
      jcs.replay();
      break;
    case 2:record_chess();
      break;
    case 3:show_record();
      break;
    case 4:exit=true;
    }
  }
  
}
