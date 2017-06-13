#include <iostream>
#include <string>

#include <boost/tokenizer.hpp>

void TestTokenizer() {
  std::cout << "#### TestTokenizer ####" << std::endl;

  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  std::string s = "Boost C++ libraries";
  {
    tokenizer tok(s);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); it ++) {
      std::cout << *it << std::endl; // result : Boost C + + libraries
    }
  }

  ////////////////////////////
  {
    boost::char_separator<char> sep(" ");
    tokenizer tok(s, sep);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); it++) {
      std::cout << *it << std::endl; // result : Boost C++ libraries
    }
  }

  ////////////////////////////
  {
    // The second parameter indicate which charactor show
    boost::char_separator<char> sep(" ", "+");
    tokenizer tok(s, sep);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); it++) {
      std::cout << *it << std::endl; // result : Boost C + + libraries
    }
  }

  ////////////////////////////
  {
    // The second parameter indicate which charactor show
    boost::char_separator<char> sep(" ", "+", boost::keep_empty_tokens); 
    tokenizer tok(s, sep); 
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) { 
      std::cout << *it << std::endl; // result : Boost C+  + libraries
    }
  }
}

void TestTokenizer2() {
  {
    typedef boost::tokenizer<boost::escaped_list_separator<char> > tokenizer;
    std::string s = "Boost,\"C++ libraries\"";
    tokenizer tok(s);
    for (auto it = tok.begin(); it != tok.end(); ++it) {
      std::cout << *it << std::endl; // result : Boost C++ libraries
    }
  }

  {
    typedef boost::tokenizer<boost::offset_separator> tokenizer; 
    std::string s = "Boost C++ libraries";
    int offsets[] = {5, 5, 9};
    boost::offset_separator sep(offsets, offsets + 3);
    tokenizer tok(s, sep);
    for (auto it = tok.begin(); it != tok.end(); it ++) {
      std::cout << *it << std::endl;
    }
  }
}

int main(int argc, char** argv) {
  TestTokenizer();
  TestTokenizer2();

  return 0;
}
