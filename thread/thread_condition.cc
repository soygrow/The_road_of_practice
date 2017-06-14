#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <boost/thread.hpp>

boost::mutex mutex;
boost::condition_variable_any cond;
std::vector<int> random_numbers;

void wait(int seconds) {
  boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void fill() {
  wait (2);
  std::srand(static_cast<unsigned int> (std::time(0)));
  for (int i = 0; i < 3; i ++) {
    std::cout << "wait unlock ...." << std::endl;
    boost::unique_lock<boost::mutex> lock(mutex);
    random_numbers.push_back(std::rand());
    std::cout << "wait 2s ..." << std::endl;
    wait(2);
    cond.notify_all();
    // when the thread block, the wait function can destroy the mutex
    // The execution of the current thread (which shall currently be
    // locking lck) is blocked until notified.
    cond.wait(mutex);
  }
}

void print() {
  std::size_t next_size = 1;
  for (int i = 0; i < 3; i ++) {
    boost::unique_lock<boost::mutex> lock(mutex);
    std::cout << "get lock ..." << std::endl;
    while (random_numbers.size() != next_size) {
      std::cout << "size less next_size ..." << std::endl;
      wait (10);
      cond.wait(mutex);
    }

    std::cout << random_numbers.back() << std::endl;
    ++ next_size;
    cond.notify_all();
  }
}

void TestThread() {
  
  boost::thread t2(print);
  boost::thread t1(fill);

  t1.join();
  t2.join();
}

int main(int argc, char** argv) {
  TestThread();

  return 0;
}
