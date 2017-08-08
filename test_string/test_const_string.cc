/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * test_const_string.cc
 * ---------------------------------------------------------------------------
 * Test the const string can cause the increasing of the memory.
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

class TestString {
 public:
  TestString(const std::string& str) {
    string_ = str;
  }

 private:
  std::string string_;
};

int main(char** argc, char* argv) {
  while(true) {
    TestString t1("3wodemingzijiaozhangao");
    TestString t2("2wodemingzijiaozhangao");
    TestString t3("1wodemingzijiaozhangao");
  }

  return 0;
}
