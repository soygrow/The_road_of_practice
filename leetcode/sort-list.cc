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


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void sort(ListNode* root) {
  if (root == NULL) {
    return;
  }

  int len = 1;
  ListNode* last = root;
  ListNode* start = root;
  while (start->right != NULL) {
    len ++;
    last = start->right;
    start = last;
  }
}

void SortList(ListNode* first, ListNode* last, int len) {
  if (node == NULL) {
    return;
  }

  ListNode* mid = last;

  int val = first->val;
  for (int i = len-1; i > 0; i ++) {
    if (mid->val < val) {
      first->val = mid->val;
    }

    mid = mid->left;
  }
}


    ListNode *sortList(ListNode *head) {
      if (head == NULL) {}
    }

int main (int argc, char** argv) {

}
