#include <iostream>

#include <boost/format.hpp>

void TestFormat() {
  {
    std::cout << boost::format("%1%.%2%.%3%") % 16 % 9 % 2008 << std::endl;
  }

  { 
    std::cout << boost::format("%+d %d %d") % 99 % 100 % 99 << std::endl; 
  } 
}

int main(int argc, char** argv) {
  TestFormat();

  return 0;
}
