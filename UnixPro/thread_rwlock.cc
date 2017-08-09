/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * thread_rwlock.cc
 * ---------------------------------------------------------------------------
 * The file introduce the thread read and write lock.
 * ---------------------------------------------------------------------------
 */

#include <stdlob.h>
#include <pthread.h>

#include "glog/logging.h"

struct Job {
  Job* j_next;
  Job* j_prev;
  pthread j_id;
};

struct Queue {
  Job* q_head;
  Job* q_tail;
  pthread_rwlock_t q_lock;
};

int QueueInit(Queue* qp) {
  int err;

  qp->q_head = NULL;
  qp->q_tail = NULL;
  err = pthread_rwlock_init(&qp->q_lock, NULL);

  if (err != 0) {
    LOG(INFO) << "thread rwlock init err == " << err;
    return err;
  }

  return 0;
}

// Insert a job at the head of the queue
void JobInsert(Queue* qp, Job* jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = qp->q_head;
  jp->j_prev = NULL;

  if (qp->q_head != NULL) {
    qp->q_head->j_prev = jp;
  } else {
    qp->q_tail = jp;
  }

  qp->q_head = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

// Append a job on the tail of the queue
void JobAppend(Queue* qp, Job* jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  jb->j_prev = qp->q_tail;
  jb->j_next = NULL;

  if (qp->q_tail != NULL) {
    qp->q_tail->j_next = jp;
  } else {
    qp->q_head = jp;
  }

  qp->q_tail = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

// Remove the given job from a queue
void JobRemove(Queue* qp, Job* jp) {
  pthread_rwlock_wrlock(&qp->q_lock);
  if (jp == qp->q_head) {
    qp->q_head = jp->j_next;
    if (qp->q_tail == jp) {
      qp->q_tail = NULL;
    } else {
      jp->j_next->j_prev = jp->j_prev;
    }
  } else if (jp == qp->q_tail){
    qp->q_tail = jp->q_prev;
    jp->j_prev->j_next = jp->j_next;
  } else {
    jp->j_prev->j_next = jp->j_next;
    jp->j_next->j_prev = jp->j_prev;
  }

  pthread_rwlock_wrlock(&qp->q_lock);
}

// Find a job for the given thread Id
Job* JobFind(Queue* qp, pthread_t id) {
  Job* jp = NULL;

  if (pthread_rwlock_rdlock(&qp->q_lock) != 0) {
    return NULL;
  }

  for (jp = qp->q_head; jp != NULL; jp = jp->j_next) {
    if (pthread_equal(jp->j_id, id)) {
      break;
    }
  }

  pthread_rwlock_unlock(&qp->q_lock);

  return jp;
}
