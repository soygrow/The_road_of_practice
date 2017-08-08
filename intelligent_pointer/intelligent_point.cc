/*
 * Copyright 2017 All Rights Reserved.
 * Author : soygrow
 * Date   : 2017-06-14
 *
 * intelligent_point.cc
 * ---------------------------------------------------------------------------
 * Test intelligent point.
 * ---------------------------------------------------------------------------
 */

#include <unistd.h>
#include <string.h>
#include <iostream>

#include <boost/shared_ptr.hpp>

void IntelligentPiontWithArray() {
  char* str = new char[1024*1024*1024];
  char s[] = "zhanghaokjsadfhlkashdlkjfalsdkfskladfkalsdkldflkasdlkfashdfjklajsflkd";
  strcpy(str, s);

  //boost::shared_ptr<char> p(str);
  //sleep(1);
  delete str;
  return;
}

int main(int argc, char** argv) {
  while (true) {
    IntelligentPiontWithArray();
    //sleep(1);
  }

  return 0;
}
