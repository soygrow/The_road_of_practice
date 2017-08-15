/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * sum_root_to_leaf_numbers.cc
 * ---------------------------------------------------------------------------
 * Given a binary tree containing digits from0-9only, each root-to-leaf path 
 * could represent a number.
 * An example is the root-to-leaf path1->2->3which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 * For example,
 *    1
 *   / \
 *  2   3
 * The root-to-leaf path1->2represents the number 12.
 * The root-to-leaf path1->3represents the number 13.
 * Return the sum = 12 + 13 =25.
 * ---------------------------------------------------------------------------
 */

#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int preorderSum(TreeNode* node, int sum) {
  if (node == NULL) {
    return 0;
  }

  sum = sum*10 + node->val;

  if (node->left == NULL && node->right == NULL) {
    return sum;
  }
  
  int left = preorderSum(node->left, sum);
  int right = preorderSum(node->right, sum);

  return (left + right);
}

int sumNumbers(TreeNode *root) {
  int sum = 0;
  if (root == NULL) {
    return sum;
  }

  return preorderSum(root, sum);
}

int main(int argc, char** argv) {

}
