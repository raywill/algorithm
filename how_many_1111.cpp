// Copyright 1999-2017 Alibaba Inc. All Rights Reserved.
// Author:
//   xiaochu.yh@alipay.com
//
//   0011001111011111, 最多连续有多少个 1
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

class Seq
{
public:
  virtual int cur() = 0;
  virtual void next() = 0;
};

/* 对于不同形式的序列，只需要实现 Seq 类即可 */
class IntSeq : public Seq
{
public:
  IntSeq(int64_t val) {
    val_ = val;
    remain_ = sizeof(int64_t) * 8;
    printf("remain=%d\n", remain_);
  }
  int cur() {
    if (remain_ > 0) {
      return val_ & 1;
    } else {
      return -1;
    }
  }
  void next() {
    printf("%lx, %d, %d\n", val_, cur(), remain_);
    val_ >>= 1;
    if (remain_ > 0) {
      remain_--;
    } else {
      printf("\n");
    }
  }
private:
  int remain_;
  int64_t val_;
};


#define END (-1)
class Parser
{
public:

  Parser(Seq &seq) : seq_(seq), token_(-1), one_cnt_(0)
  {
  }

  int parse(int &count)
  {
    int ret = 0;
    bool finish = false;
    get_token();
    while (!finish) {
      switch (token_) {
        case 0:
          match(0);
          break;
        case 1:
          count = std::max(count, one_cnt_);
          match(1);
          break;
        case END:
          finish = true;
          printf("see END\n");
          break;

        default:
          break;

      }
    }
    return ret;
  }

private:
  int cur()
  {
    return seq_.cur();
  }

  void next()
  {
    seq_.next();
  }

  void get_token()
  {
    if (cur() == 0) {
      while (cur() == 0) {
        next();
      }
      token_ = 0;
    } else if (cur() == 1) {
      token_ = 1;
      one_cnt_ = 0;
      while (cur() == 1) {
        next();
        one_cnt_++;
      }
    } else if (cur() == -1) {
      token_ = END;
    } else {
      //invalid
      //assert(1);
    }
  }

  void match(int sym)
  {
    if (token_ != sym) {
      //assert(1);
    } else {
      get_token();
    }
  }

private:
  Seq &seq_;
  int token_;
  int one_cnt_;
};

int main(int argc, const char *argv[])
{
  int count = 0;
  int64_t val = 0xFFF7FFFF7;
  IntSeq seq(val);
  Parser p(seq);
  p.parse(count);
  printf("%x:%d\n", val, count);
  return 0;
}
