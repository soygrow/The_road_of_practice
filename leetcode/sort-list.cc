/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * mini_depth.cc
 * ---------------------------------------------------------------------------
 * Sort a linked list in O(n log n) time using constant space complexity.
 * ---------------------------------------------------------------------------
 */

#include <iostream>

#include "glog/logging.h"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


ListNode* Merge(ListNode* forward, ListNode* backend) {
  if (forward == NULL) {
    return backend;
  } else if (backend == NULL) {
    return forward;
  }
  
  ListNode* head = NULL;
  if (forward->val < backend->val) {
    head = forward;
    forward = forward->next;
  } else {
    head = backend;
    backend = backend->next;
  }
  
  ListNode* p = head;
  while (forward != NULL && backend != NULL) {
    if (forward->val < backend->val) {
      p->next = forward;
      forward = forward->next;
    } else {
      p->next = backend;
      backend = backend->next;
    }

    p = p->next;
  }

  if (forward != NULL) {
    p->next = forward;
  }
  if (backend != NULL) {
    p->next = backend;
  }

  return head;
}


ListNode *sortList(ListNode *head) {
  // Just one node
  if (head == NULL || head->next == NULL) {
    return head;
  }

  LOG(INFO) << " =================== ";

  ListNode* p = head;
  ListNode* q = head->next;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode* left = sortList(slow->next);
  slow->next = NULL;
  ListNode* right = sortList(head);

  {
    ListNode* p = left;
    ListNode* q = right;
    while (p != NULL) {
      std::cout << p->val << " ";
      p = p->next;
    }

    while (q != NULL) {
      std::cout << q->val << " ";
      p = q->next;
    }
  }

  sleep(2);

  return Merge(left, right);
}

int main(int argc, char** argv) {
  ListNode* head = new ListNode(5);
  head->next = new ListNode(4);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(2);
  head->next->next->next->next = new ListNode(2);

  ListNode* new_head = sortList(head);

  while (new_head != NULL) {
    std::cout << new_head->val << " ";
    new_head = new_head->next;
  }

  std::cout << std::endl;

  return 0;
}

