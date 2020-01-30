#ifndef RESPONSE_H
#define RESPONSE_H

class response{
public:
  enum type{put,withdraw,giveup,prohibit};
  virtual response::type get_response_type()=0; //获取回应类型
};

//落子回应
class put :public response{
public:
  virtual response::type get_response_type(){return response::put;}
};

//悔棋回应
class withdraw :public response{
public:
  virtual response::type get_response_type(){return response::withdraw;}
};

//认输回应
class giveup :public response{
public:
  virtual response::type get_response_type(){return response::giveup;}
};

//指出禁手回应
class prohibit :public response{
public:
  virtual response::type get_response_type(){return response::prohibit;}
};

#endif
