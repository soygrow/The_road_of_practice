/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * asoi_socket.cc
 * ---------------------------------------------------------------------------
 * Test asio functions to test async socket.
 * ---------------------------------------------------------------------------
 */

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <string>

#include "gflags/gflags.h"
#include "glog/logging.h"

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket sock(io_service);
boost::array<char, 4096> buffer;

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
  if (!ec) {
    LOG(INFO) << std::string(buffer.data(), bytes_transferred);
    sock.async_read_some(boost::asio::buffer(buffer), read_handler);
  } else {
    LOG(INFO) << "Read error!";
    LOG(INFO) << ec.value(); 
    LOG(INFO) << ec.category().name(); 
  }
}

void connect_handler(const boost::system::error_code &ec) {
  if (!ec) {
    boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: baidu.com\r\n\r\n"));
    sock.async_read_some(boost::asio::buffer(buffer), read_handler);
  } else {
    LOG(INFO) << "Connect error!";
  }
}

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) {
  if (!ec) {
    sock.async_connect(*it, connect_handler);
  } else {
    LOG(INFO) << "Domain name resolve error!";
  }
}

void TestSocket() {
  boost::asio::ip::tcp::resolver::query query("www.baidu.com", "80");
  resolver.async_resolve(query, resolve_handler);

  io_service.run();
}

int main(int argc, char** argv) {
  google::InstallFailureSignalHandler();
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);
  
  TestSocket();

  return 0;
}
