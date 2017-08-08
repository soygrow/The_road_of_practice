/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * evaluate-reverse-polish-notation.cc
 * ---------------------------------------------------------------------------
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * Valid operators are+,-,*,/. Each operand may be an integer or another 
 * expression.
 * Some examples:
 *  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 *  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "glog/logging.h"

std::stack<int> s;

void Operator(int flag) {
  int val1 = s.top();
  s.pop();
  int val2 = s.top();
  s.pop();

  int res = 0;
  switch (flag) {
  case 1 : {
    res = val2 + val1;
    break;
  }
  case 2 : {
    res = val2 - val1;
    break;
  }
  case 3 : {
    res = val2 * val1;
    break;
  }
  case 4 : {
    if (val1 != 0) {
      res = val2 / val1;
      break;
    }
  }
  }

  s.push(res);
}
    
int evalRPN(std::vector<std::string> &tokens) {
  for (size_t i = 0; i < tokens.size(); i ++) {
    std::string tmp = tokens[i];
    LOG(INFO) << i << " : " << tmp;
    if (tmp == "+") {
      Operator(1);
    } else if (tmp == "-") {
      Operator(2);
    } else if (tmp == "*") {
      Operator(3);
    } else if (tmp == "/") {
      Operator(4);
    } else {
      int val = stoi(tmp);
      s.push(val);
    }           
  }
        
  return s.top();
}


int main(int argc, char** argv) {
  std::string str[3] = {"3","-4","+"};
  std::vector<std::string> token;
  for (int i = 0; i < 3; i ++) {
    token.push_back(str[i]);
  }

  std::cout << evalRPN(token) << std::endl;

  return 0;
}
