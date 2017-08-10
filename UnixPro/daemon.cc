/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * daemon.cc
 * ---------------------------------------------------------------------------
 * The file introduce daemon process. The reason of Daemon is that it can
 * prevented the signals from the tty.
 * 创建守护进程的原因是防止终端产生的一些信号让进程推出。
 * 步骤：
 * [1].将文件模式的屏蔽字设置为0;子进程会继承父进程的文件权限掩码，设为0,取消继承
 *     文件权限掩码，增大守护进程的灵活性
 * [2].第一次fork;保证创建的进程不是进程组组长，为了setsid服务
 * [3].setsid新建一个会话，并担任该进程组组长; 有三个作用：1.让进程摆脱原进程的控制
 *     2.让进程摆脱原进程组的控制 3.让进程摆脱原控制终端的控制
 * [4].将当前工作目录改为根目录 chdir
 * [5].关闭不需要的文件描述符
 * [6].忽略SIGGHLD信号;守护进程需要忽略SIGGHLD信号，因为守护进程创建的子进程在
 *     退出的时候会给父进程发送该信号，当父进程忽略该信号后，将它抛给init进程，
 *     init进程会回收该进程，从而不会出现僵尸进程，如果父进程不等待子进程结束，
 *     子进程将称为僵尸进程，如果父进程等待，将增加父进程的负担。这一步不是必须的。
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

  // Ensure furture opens won't allocate controlling ttys
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

void test (int vec) {
  std::cout << vec << std::endl;

  return;
}
int main(int argc, char** argv) {
  //Daemon("daemon");
  std::vector<int> vec;
  vec[0] = 10;

  test(vec[1]);
  
  sleep(100);

  return 0;
}
