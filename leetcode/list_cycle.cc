/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * list_cycle.cc
 * ---------------------------------------------------------------------------
 * Given a linked list, return the node where the cycle begins. If there is 
 * no cycle, returnnull.
 * Follow up:
 * Can you solve it without using extra space?
 * ---------------------------------------------------------------------------
 */

#include <iostream>

#include "glog/logging.h"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

namespace listcycle1 {

  ListNode *detectCycle(ListNode *head) {
    if(head == NULL){
      return 0;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast != NULL && fast->next != NULL){
      slow = slow->next;
      fast = fast->next->next;
      if(slow == fast){
        break;
      }
    }
    if(fast == NULL || fast->next == NULL){
      return NULL;
    }

    slow = head;
    while(slow != fast){
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
  }

} // namespace listcycle1


int main(int argc, char** argv) {
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = head->next->next;

  ListNode* node = listcycle1::detectCycle(head);
  LOG(INFO) << "node->val === " << node->val;
  
  return 0;
}

