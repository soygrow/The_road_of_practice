/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * thread_TLS.cc
 * ---------------------------------------------------------------------------
 * The file introduce the thread local store. Some variable can only visit
 * in this thread.
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/thread.hpp>

// The srand of this function execute just once in all threads. when it has
// many threads, we may get the same random number.
void init_number_generator() {
  static bool done = false;
  if (!done) {
    done = true;
    std::srand(static_cast<unsigned int> (std::time(0)));
    std::cout << "variable done init ..." << std::endl;
  }
}

// The srand can execute once in one thread, so in every thread
// we can get different random number.
void init_number_generator_tls() {
  // TLS variable, just in different thread has different tls variable.
  static boost::thread_specific_ptr<bool> tls;
  if (!tls.get()) {
    tls.reset(new bool(false));
  }

  if (!*tls) {
    *tls = true;
    std::srand(static_cast<unsigned int> (std::time(0)));
  }
}

boost::mutex mutex;

void random_number_generator() {
  init_number_generator();
  int i = std::rand();
  boost::lock_guard<boost::mutex> lock(mutex);
  std::cout << i << std::endl;
}

void TestThreadTls() {
  boost::thread t[3];
  for (int i = 0; i < 3; i ++) {
    t[i] = boost::thread(random_number_generator);
  }

  for (int i = 0; i < 3; i ++) {
    t[i].join();
  }
}

int main(int argc, char** argv) {
  TestThreadTls();

  return 0;
}

