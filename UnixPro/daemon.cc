/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * daemon.cc
 * ---------------------------------------------------------------------------
 * The file introduce daemon process.
 * ---------------------------------------------------------------------------
 */


#include <iostream>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#include "glog/logging.h"

void Daemon(const char* cmd) {
  int i,fd0,fd1,fd2;
  pid_t pid;
  struct rlimit rl;
  struct sigaction sa;

  // Clear the file creation mask
  umask(0);

  //Get maximum number of file descriptors
  if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
    LOG(INFO) << cmd << " can't get file limit" ;
    return;
  }

  // Become a session leader to lose controlling tty.
  if ((pid = fork()) < 0) {
    LOG(INFO) << cmd << " : can't fork.";
    return;
  } else if (pid != 0) {
    exit(0); // parent
  }

  // Make process to session leader.
  setsid();

  // Ensure frture opens won't allocate controlling ttys
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGHUP, &sa, NULL) < 0) {
    LOG(INFO) << cmd << " : can't ignore SIGHUP.";
    return;
  }

  if ((pid = fork()) < 0) {
    LOG(INFO) << cmd << " : can't fort.";
    return;
  } else if (pid != 0) {
    exit(0); // parent
  }

  // Change the current working directory to the root so we won't
  // prevent file systems from being unmounted.
  if (chdir("/") < 0) {
    LOG(INFO) << cmd << " : can't change directory to /.";
    return;
  }

  // Close all open file descriptors
  if (rl.rlim_max == RLIM_INFINITY) {
    rl.rlim_max = 1024;
  }
  for (i = 0; i < rl.rlim_max; i ++) {
    close(i);
  }

  // Attach file descriptors 0, 1, and 2 to /dev/null.
  fd0 = open("/dev/null", O_RDWR);
  fd1 = dup(0);
  fd2 = dup(0);

  // Initialize the log file.
  openlog(cmd, LOG_CONS, LOG_DAEMON);
  if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
    syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
    exit(1);
  }
  
}


int main(int argc, char** argv) {
  Daemon("daemon");

  sleep(100);

  return 0;
}
