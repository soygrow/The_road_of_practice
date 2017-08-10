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

void OrderList(ListNode* slow, ListNode* fast) {
  if (fast == NULL) {
    return;
  }

  ListNode* node = fast->next;
  if (node != NULL && node->next != NULL) {
    OrderList(slow->next, node->next);
  }
}

void reorderList(ListNode *head) {
  if (head == NULL || head->next == NULL) {
    return;
  }

  reorderList();
}

int main() {

}
