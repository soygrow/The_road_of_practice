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

void* thr_fn1(void* arg) {
  LOG(INFO) << "thread 1 returning.";
  return ((void*)1);
}

void* thr_fn2(void* arg) {
  LOG(INFO) << "thread 2 exiting.";
  return ((void*)2);
}

int main(int argc, char** argv) {
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

  return 0;
}
