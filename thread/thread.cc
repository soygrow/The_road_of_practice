#include <iostream>
#include <vector>

#include <boost/thread.hpp>

boost::mutex mutex;

namespace Test1 {
  void wait(int seconds) {
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
  }

  void thread() {
    std::cout << boost::this_thread::get_id() << std::endl;
    std::cout << boost::thread::hardware_concurrency() << std::endl;
  
    try{
      for (int i = 0; i < 5; i ++) {
        //wait(1);
        // only one thread can visit this mutex
        boost::lock_guard<boost::mutex> lock(mutex);
        std::cout << i << std::endl;
      }
    } catch (boost::thread_interrupted&) {
      std::cout << "thread interrupted ..." << std::endl;
    }
  }

  void TestThread() {
    boost::thread t(thread);
    //t.interrupt(); //when the program sleep, the interrupt function can interrupt.
    t.join();
  }

} // namespace Test1

namespace Test2 {
  void wait(int seconds) {
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
  }

  boost::shared_mutex mutex;
  std::vector<int> random_numbers;

  void fill() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    for(int i = 0; i < 3; i++) {
      // Need write lock - other threads can not visit this mutex
      boost::unique_lock<boost::shared_mutex> lock(mutex);
      random_numbers.push_back(std::rand());
      lock.unlock();
      wait(1);
    }
  }

  void print() {
    for (int i = 0; i < 3; i++) {
      wait(1);
      // Need read lock - other threads can have read priority
      boost::shared_lock<boost::shared_mutex> lock(mutex);
      std::cout << random_numbers.back() << std::endl;
    }
  }

  int sum = 0;
  void count() {
    for (int i = 0; i < 3; i ++) {
      wait(1);
      // Need read lock - other threads can have read priority
      boost::shared_lock<boost::shared_mutex> lock(mutex);
      sum += random_numbers.back();
    }
  }

  void TestThread() {
    boost::thread t1(fill);
    boost::thread t2(print);
    boost::thread t3(count);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Sum : " << sum << std::endl;
  }
} // namecpace Test2


/////////////////////////////////


int main(int argc, char** argv) {
  Test1::TestThread();

  Test2::TestThread();

  return 0;
}
