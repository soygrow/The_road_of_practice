/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * thread_create.cc
 * ---------------------------------------------------------------------------
 * The file introduce the thread create and thread id.
 * ---------------------------------------------------------------------------
 */

#include <iostream>

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

pthread_t ntid;

void printids(const char* s) {
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %lu tid %lu (0x%lx) \n", s, (unsigned long)pid,
        (unsigned long)tid, (unsigned long)tid);
}

void* thr_fn(void* arg) {
  printids("new thread: ");
  return ((void*) 0);
}

int main(int argc, char** argv) {
  int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0) {
    printf("err : %d, can't create thread.", err);
  }

  printids("main thread: ");
  sleep(1);

  return 0;
}
