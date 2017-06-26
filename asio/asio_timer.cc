/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * asoi.cc
 * ---------------------------------------------------------------------------
 * Test asio functions
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp> 

#include "gflags/gflags.h"
#include "glog/logging.h"

void handler1(const boost::system::error_code &ec) {
  std::cout << "5s ......" << std::endl;
}

void handler2(const boost::system::error_code &ec) {
  std::cout << "10s ......" << std::endl;
}

boost::asio::io_service io_service1;
boost::asio::io_service io_service2;
void run1() {
  LOG(INFO) << "asio run 1 ....";
  io_service1.run();
}
void run2() {
  LOG(INFO) << "asio run 2 ....";
  io_service2.run();
}

void TestMutiService() {
  boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(5));
  timer1.async_wait(handler1);
  boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(5));
  timer2.async_wait(handler2);

  LOG(INFO) << "++++++++++++++++++";
  boost::thread thread1(run1);
  boost::thread thread2(run2);

  LOG(INFO) << "++++++++++++++++++";
  thread1.join();
  thread2.join();
  LOG(INFO) << "++++++++++++++++++ end";
}

int main(int argc, char** argv) {
  google::InstallFailureSignalHandler();
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);

  TestMutiService();
  
  return 0;
}
