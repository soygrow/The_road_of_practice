/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * copy_list_with_random_pointer.cc
 * ---------------------------------------------------------------------------
 * A linked list is given such that each node contains an additional random 
 * pointer which could point to any node in the list or null.
 * Return a deep copy of the list.
 * ---------------------------------------------------------------------------
 */

#include <iostream>

#include "glog/logging.h"

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

RandomListNode *copyRandomList(RandomListNode *head) {
  if (head == NULL) {
    return NULL;
  }

  RandomListNode* p = head;
  while (p != NULL) {
    RandomListNode* tmp = new RandomListNode(p->label);
    
    // Insert the back of the same node
    tmp->next = p->next;
    p->next = tmp;

    p = tmp->next;
  }

  p = head;
  RandomListNode* new_head = p->next;
  RandomListNode* q = p->next;
  while (p != NULL && q!= NULL) {
    if (p->random != NULL) {
      q->random = p->random->next;
    } else {
      q->random = NULL;
    }

    if (p->next == NULL || q->next == NULL) {
      break;
    }
    
    RandomListNode* p_tmp = p->next->next;
    RandomListNode* q_tmp = q->next->next;

    p->next = p->next->next;
    q->next = q->next->next;

    p = p_tmp;
    q = q_tmp;
  }

  return new_head;
}

int main(int argc, char** argv) {
  RandomListNode* head = new RandomListNode(1);
  head->next = new RandomListNode(2);
  head->next->next = new RandomListNode(3);
  head->next->next->next = new RandomListNode(4);
  head->next->next->next->next = new RandomListNode(5);

  head->random = head->next->next;
  head->next->next->next->next->random = head->next;
  head->next->next->next->random = head->next;

  RandomListNode* new_head = copyRandomList(head);
  
  return 0;
}

