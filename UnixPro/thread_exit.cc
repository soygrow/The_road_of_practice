/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * thread_exit.cc
 * ---------------------------------------------------------------------------
 * The file introduce exit the thread.
 * ---------------------------------------------------------------------------
 */


#include <iostream>
#include <pthread.h>

#include "glog/logging.h"

namespace test1 {

  void* thr_fn1(void* arg) {
    LOG(INFO) << "thread 1 returning.";
    return ((void*)1);
  }

  void* thr_fn2(void* arg) {
    LOG(INFO) << "thread 2 exiting.";
    pthread_exit((void*)2);
  }

  void thread_exit_test() {
    int err;
    pthread_t tid1,tid2;
    void* tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0) {
      LOG(INFO) << "err : " << err << " ,can't create thread 1.";
    }
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0) {
      LOG(INFO) << "err : " << err << " ,can't create thread 2.";
    }

    err = pthread_join(tid1, &tret);
    if (err != 0) {
      LOG(INFO) << "err : " << err << " ,can't join thread 1.";
    }
    LOG(INFO) << "thread1 exit code : " << (long)tret;

    err = pthread_join(tid2, &tret);
    if (err != 0) {
      LOG(INFO) << "err : " << err << " ,can't join thread 2.";
    }  
    LOG(INFO) << "thread2 exit code : " << (long)tret;
  }

} // namespace test1

namespace test2 {

  struct Foo {
    int a;
    int b;
    int c;
    int d;
  };

  void printfoo(const char* s, const Foo* fp) {
    LOG(INFO) << s;
    LOG(INFO) << "  structure at 0x" << (unsigned long)fp;
    LOG(INFO) << "  foo.a = " << fp->a;
    LOG(INFO) << "  foo.b = " << fp->b;
    LOG(INFO) << "  foo.c = " << fp->c;
    LOG(INFO) << "  foo.d = " << fp->d;
  }

  void* thr_fn1(void* arg) {
    Foo foo = {1, 2, 3, 4};
    printfoo("thread 1 : ", &foo);
    pthread_exit((void*)&foo);
  }

  void* thr_fn2(void* arg) {
    LOG(INFO) << "thread 2: ID is " << (unsigned long)pthread_self();
    pthread_exit((void*)0);
  }

  void thread_exit_test() {
    int err;
    pthread_t tid1, tid2;
    Foo* fp;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0) {
      LOG(INFO) << "err = " << err << " can't create thread 1.";
    }
    err = pthread_join(tid1, (void**)(&fp));
    if (err != 0) {
      LOG(INFO) << "err = " << err << " can't join thread 1.";
    }

    sleep(1);
    LOG(INFO) << "parent starting second thread";
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0) {
      LOG(INFO) << "err = " << err << "can't create thread 2.";
    }

    sleep(1);
    printfoo("parent : ", fp);
  }
  
} // namespace test2

int main(int argc, char** argv) {
  test1::thread_exit_test();
  test2::thread_exit_test();
  
  return 0;
}
