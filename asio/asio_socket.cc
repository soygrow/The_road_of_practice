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
#include <boost/thread.hpp>

#include <iostream>
#include <string>
#include <cstddef>

#include "gflags/gflags.h"
#include "glog/logging.h"

namespace client {
  
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
      LOG(INFO) << ec.message();
    }
  }

  void connect_handler(const boost::system::error_code &ec) {
    if (!ec) {
      boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
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
    boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80");
    resolver.async_resolve(query, resolve_handler);

    io_service.run();
  }

} // namespace client

//////////////////////////////////////////////////////

namespace Server {
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80);
  boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
  boost::asio::ip::tcp::socket sock(io_service);
  std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";

  void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if (!ec) {
      LOG(INFO) << "Transfer bytes is : " << bytes_transferred;
    }
  }

  void accept_handler(const boost::system::error_code &ec) {
    if (!ec) {
      boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);
    } else {
      LOG(INFO) << "error : " << ec.message();
    }
  }

  void TestServer() {
    while (true) {
      acceptor.listen();
      acceptor.async_accept(sock, accept_handler);
      io_service.run();
      LOG(INFO) << "end...";
    }
  }
}

//////////////////////////////////////////////////////

namespace AsioExtend {

  template <typename Service>
  class basic_timer : public boost::asio::basic_io_object<Service> {
   public:
    explicit basic_timer(boost::asio::io_service &io_service)
      : boost::asio::basic_io_object<Service>(io_service) {

    }

    void wait(std::size_t seconds) {
      return this->service.wait(this->implementation, seconds);
    }

    template <typename Handler>
    void async_wait(std::size_t seconds, Handler handler) {
      this->service.async_wait(this->implementation, seconds, handler);
    }
  };
  
}

int main(int argc, char** argv) {
  google::InstallFailureSignalHandler();
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);
  
  //client::TestSocket();
  Server::TestServer();

  return 0;
}
