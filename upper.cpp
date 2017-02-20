// Copyright 1999-2017 Alibaba Inc. All Rights Reserved.
// Author:
//   xiaochu.yh@alipay.com
//
// 将 i love algrithom 转化成 I Love Algrithom

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int to_upper(const char *s, char *buf, int buf_size)
{
  int ret = 0; // 0 succ, 1 buf_not_enough, 2 other failure
  int i = 0;
  bool alert = true;

  while (1) {

    if (i >= buf_size) {
      ret = 1;
      break;
    }

    if (s[i] == '\0') {
      buf[i] = '\0';
      break;
    }

    if (isspace(s[i])) {
      buf[i] = s[i];
      alert = true;
    } else if (alert) {
      buf[i] = toupper(s[i]);
      alert = false;
    } else {
      buf[i] = s[i];
    }

    i++;

  }

  return ret;
}

void assert(int expect, int actual)
{
  if (expect != actual) {
    printf("[ERROR] number not equal\n");
    printf("expected: %d\n", expect);
    printf("actual: %d\n", actual);
  } else {
    printf("[SUCC] number equal\n");
    printf("value: %d\n", expect);
  }
}

void assert(const char *s1, const char *s2)
{
  if (strcmp(s1, s2) != 0) {
    printf("[ERROR] string not equal\n");
    printf("expected: %s\n", s1);
    printf("actual: %s\n", s2);
  } else {
    printf("[SUCC] string equal\n");
    printf("value: %s\n", s1);
  }
}

void test()
{
  const char *str[] = {
    "i love algrithom",
    "IIIi i",
    "i",
    "",
    "iiiii",
    "i love ",
    " i love ",
    " i love"
  };

  const char *expect[] = {
    "I Love Algrithom",
    "IIIi I",
    "I",
    "",
    "Iiiii",
    "I Love ",
    " I Love ",
    " I Love"
  };


  const int buf_size = 1024;
  char buf[buf_size];
  int count = sizeof(str) / sizeof(char *);
  printf("we have %d test\n", count);
  for (int i = 0; i < count; ++i) {
    printf("[CASE] [%s]\n", str[i]);
    int ret = to_upper(str[i], buf, buf_size);
    assert(expect[i], buf);
    printf("\n");
  }

  //test buf not enought
  int ret = 0;
  ret = to_upper(str[0], buf, 3);
  assert(ret, 1);
  ret = to_upper(str[0], buf, 2);
  assert(ret, 1);
  ret = to_upper(str[0], buf, 1);
  assert(ret, 1);
  ret = to_upper(str[0], buf, 0);
  assert(ret, 1);



}

int main(int argc, const char *argv[])
{
  test();
  return 0;
}
