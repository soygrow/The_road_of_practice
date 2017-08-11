/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * tree_traversal.cc
 * ---------------------------------------------------------------------------
 * Given a singly linked list L: L 0->L 1->...¦->L n-1->L n,
 * reorder it to: L 0->L n ->L 1->L n-1->L 2->L n-2->...¦
 * You must do this in-place without altering the nodes' values.
 * For example,
 * Given{1,2,3,4}, reorder it to{1,4,2,3}.
 * ---------------------------------------------------------------------------
 */

#include <iostream>

#include "glog/logging.h"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void OrderList(ListNode** front, ListNode* back) {
  if (back->next == NULL) {
    return;
  }

  OrderList(front, back->next);

  // Move last node to its location
  ListNode* new_front = *front;
  ListNode* node = back->next;
  back->next = NULL;
  node->next = new_front->next;
  new_front->next = node;
  *front = (*front)->next->next;
}

void reorderList(ListNode *head) {
  if (head == NULL || head->next == NULL) {
    return;
  }

  // Compute the length of the list
  ListNode* slow = head;
  ListNode* fast = head;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  OrderList(&head, slow);
}

int main() {
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  //head->next->next->next->next = new ListNode(5);

  reorderList(head);

  while (head != NULL) {
    LOG(INFO) << "val ====== " << head->val;
    head = head->next;
  }

  return 0;
}
