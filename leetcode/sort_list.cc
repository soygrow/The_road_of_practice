/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * sort_list.cc
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

namespace merge {
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

    ListNode* p = head;
    ListNode* q = head->next;
    while (q != NULL && q->next != NULL) {
      p = p->next;
      q = q->next->next;
    }

    ListNode* left = sortList(p->next);
    p->next = NULL;
    ListNode* right = sortList(head);

    return Merge(left, right);
  }

} // namespace merge

namespace insert {
  ListNode* FindSmallNode(ListNode** head) {
    ListNode* cur = *head;
    if (cur == NULL || cur->next == NULL) {
      return cur;
    }

    ListNode* small_node = cur;
    ListNode* small_prev_node = NULL;
    ListNode* cur_prev = cur;
    cur = cur->next;

    while (cur != NULL) {
      if (small_node->val > cur->val) {
        small_prev_node = cur_prev;
        small_node = cur;
      }

      cur_prev = cur;
      cur = cur->next;
    }

    // delete the smallest node
    if (small_prev_node != NULL) {
      small_prev_node->next = small_node->next;
    } else {
      *head = small_node->next;
    }
    
    return small_node;
  }

  ListNode *insertionSortList(ListNode *head) {
    if (head == NULL || head->next == NULL) {
      return head;
    }

    ListNode* new_head = NULL;
    ListNode* node = NULL;
    while (head->next != NULL) {
      ListNode* tmp_node = FindSmallNode(&head);

      if (new_head == NULL) {
        new_head = tmp_node;
        node = tmp_node;
      } else {
        node->next = tmp_node;
        node = node->next;
      }
    }

    if (head != NULL) {
      node->next = head;
    }

    return new_head;
  }

} // namespace insert

int main(int argc, char** argv) {
  ListNode* head = new ListNode(0);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(2);
  head->next->next->next->next = new ListNode(1);

  //ListNode* new_head = merge::sortList(head);
  ListNode* new_head = insert::insertionSortList(head);

  while (new_head != NULL) {
    std::cout << new_head->val << " ";
    new_head = new_head->next;
  }

  std::cout << std::endl;

  return 0;
}

