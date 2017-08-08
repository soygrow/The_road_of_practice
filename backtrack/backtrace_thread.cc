/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * backtrack.cc
 * ---------------------------------------------------------------------------
 * The code is traced the stack when the program crash, print different stack
 * of different threads.
 * ---------------------------------------------------------------------------
 */

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include <signal.h>
#include <stdio.h>

#include <boost/thread.hpp>

// Call this function to get a backtrace.
void backtrace(int sig) {
  unw_cursor_t cursor;
  unw_context_t context;

  // Initialize cursor to current frame for local unwinding.
  unw_getcontext(&context);
  unw_init_local(&cursor, &context);

  // Unwind frames one by one, going up the frame stack.
  int count = 1;
  while (unw_step(&cursor) > 0) {
    unw_word_t offset, pc;
    unw_get_reg(&cursor, UNW_REG_IP, &pc);
    if (pc == 0) {
      break;
    }
    //LOG(ERROR) << "0x" << pc << ":";
    printf("## 0x%lx:", pc);
    
    char sym[256];
    if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
      printf("## (%s+0x%lx)\n", sym, offset);
      //LOG(ERROR) << " function name : " << sym;
    } else {
      //LOG(ERROR) << " -- error: unable to obtain symbol name for this frame";
      printf(" -- error: unable to obtain symbol name for this frame\n");
    }
  }
}

void func2() {
  char* str = "abcd";
  //str[0] = 'H';
}

void func1() {
  func2();
}

void thread1() {
  func1();
}

void func4() {
  char* str = "abcd";
  str[0] = 'H';
}

void func3() {
  func4();
}

void thread2() {
  func3();
}

int main(int argc, char** argv) {
  signal(SIGSEGV, backtrace);

  boost::thread t1(thread2);
  boost::thread t2(thread1);

  t1.join();
  t2.join();
  
  return 0;
}

