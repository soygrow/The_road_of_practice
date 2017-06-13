#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/regex.hpp>

int fun(int x, int y) { return x+y;}

// Test bind
void TestBind() {
  std::cout << "############# TestBind #############" << std::endl;
  int m = 1;
  int n = 2;

  std::cout << boost::bind(fun, _1, _2) (m, n) << std::endl;
  return;
}

void TestRegexMatch() {
  std::cout << "############# TestRegexMatch #############" << std::endl;
  std::string s = "Boris Schaling";
  boost::regex r("\\w+\\s\\w+");
  std::cout << boost::regex_match(s, r) << std::endl; // result : 1
}

void TestRegexSearch() {
  std::cout << "############# TestRegexSearch #############" << std::endl;
  std::string s = "a=rtpmap:101VP9a=rtpmap:116H264";
  std::string::const_iterator start = s.begin();
  std::string::const_iterator end = s.end();
  boost::regex r("a=rtpmap:([1-9][0-9]*)");
  boost::smatch what;
  boost::match_flag_type flags = boost::match_default; 
  while (boost::regex_search(start, end, what, r, flags)) {
    for (auto i = 0; i < what.size(); i ++) {
      std::cout << what[i] << std::endl; // result 101 116
    }

    start = what[0].second;
  }
}

void TestRegexReplace() {
  std::cout << "############# TestRegexReplace #############" << std::endl;
  {
    std::string s = "Miss han";
    boost::regex r("\\s"); // match \n blank \t and so on
    std::string fmt("_");
    boost::smatch what;
    if (boost::regex_search(s, what, r)) {
      // boost::regex r("(\\s)"); // replace up regex
      //std::cout << "#" << what[1] << "#" << std::endl;
    }
    std::cout << boost::regex_replace(s, r, fmt) << std::endl; // result : Miss_han
  }
  
  ////////////////////////////
  {
    std::string s = "Miss han";
    boost::regex expr("(\\w+)\\s(\\w+)");
    std::string fmt2("\\2 \\1");
    std::cout << boost::regex_replace(s, expr, fmt2) << std::endl; // result : han Miss
  }

  ////////////////////////////
  {
    std::string s = "Miss han"; 
    boost::regex expr("(\\w+)\\s(\\w+)"); 
    std::string fmt("\\2 \\1"); 
    std::cout << boost::regex_replace(s, expr, fmt, boost::regex_constants::format_literal) << std::endl; // result : /2 /1
  }
}

int main(int argc, char** argv) {
  TestBind();
  TestRegexMatch();
  TestRegexSearch();
  TestRegexReplace();
  
  return 0;
}
