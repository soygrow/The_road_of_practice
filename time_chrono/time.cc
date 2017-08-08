/*
 * Copyright 2017 All Rights Reserved.
 * Author : soygrow
 * Date   : 2017-06-16
 *
 * time.cc
 * ---------------------------------------------------------------------------
 * Test chrono time function.
 * ---------------------------------------------------------------------------
 */

#include <unistd.h>
#include <iostream>
#include <ratio>
#include <chrono>
#include <string>

#include <boost/shared_ptr.hpp>

#include "gflags/gflags.h"
#include "glog/logging.h"
#include "/home/project/trunk/stream_service/orbit/logger_helper.h"

class Person {
public:
  Person(int id) {};
  ~Person() {
    //LOG(FATAL) << "+++++++++++++++++++++++++++";
  }
  int id_;
};

void TestSecondTime() {
  std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
  sleep(3);
  std::chrono::high_resolution_clock::time_point next_time = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::ratio<1, 1>> durations(next_time - time);

  int past_time = durations.count();

  LOG(INFO) << past_time << " seconds .....";

  const std::string name("zhanghao jintian xinqingbuhao");
  //boost::scoped_ptr<std::string> transportName(new std::string(name));

  boost::shared_ptr<Person> p(new Person(0));
  {
    boost::shared_ptr<Person> temp(p);
    {
      boost::shared_ptr<Person> temp(p);
    }
  }

  ELOG_INFO("%s - NICE State Changing from+++++++", NULL);
}

int main(int argc, char** argv) {  
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);

  TestSecondTime();

  return 0;
}
