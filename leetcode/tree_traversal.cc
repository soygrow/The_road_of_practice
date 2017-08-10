/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * tree_traversal.cc
 * ---------------------------------------------------------------------------
 * Given a binary tree, return the postorder traversal of its nodes' values.
 * For example:
 * Given binary tree{1,#,2,3},
 *  1
 *   \
 *    2
 *   /
 *  3
 * return[3,2,1].
 * Note: Recursive solution is trivial, could you do it iteratively?
 * ---------------------------------------------------------------------------
 */


#include <iostream>
#include <vector>
#include <set>
#include <stack>

#include "glog/logging.h"

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace postorder {
  using namespace std;
  
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == NULL) {
      return res;
    }

    set<TreeNode*> trav_flag;
    stack<TreeNode*> tree_stack;
    tree_stack.push(root);
    while (tree_stack.size() > 0) {
      TreeNode* node = tree_stack.top();
      auto ite = trav_flag.find(node);
      if (ite == trav_flag.end()) {
        // First time
        trav_flag.insert(node);

        if (node->left == NULL && node->right == NULL) {
          tree_stack.pop();
          res.push_back(node->val);
        } else {
          if (node->right != NULL) {
            tree_stack.push(node->right);
          }
          if (node->left != NULL) {
            tree_stack.push(node->left);
          }
        }
      } else {
        tree_stack.pop();
        res.push_back(node->val);
      }
    }

    return res;
  }

  // Recursive traversal
  void RecursiveTraversal(TreeNode* node, vector<int>& vec) {
    if (node == NULL) {
      return;
    }

    if (node->left != NULL) {
      RecursiveTraversal(node->left, vec);
    }
    if (node->right != NULL) {
      RecursiveTraversal(node->right, vec);
    }

    vec.push_back(node->val);
  }
  
  vector<int> postorderRecursiveTraversal(TreeNode* root) {
    vector<int> res;
    if (root == NULL) {
      return res;
    }

    RecursiveTraversal(root, res);
    return res;
  }
  
} // postorder

/**
 * Given a binary tree, return the preorder traversal of its nodes' values.
 * For example:
 * Given binary tree{1,#,2,3},
 *  1
 *   \
 *    2
 *   /
 *  3
 * return[1,2,3].
 * Note: Recursive solution is trivial, could you do it iteratively?
 */

namespace preorder {

  using namespace std;

  vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == NULL) {
      return res;
    }

    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
      TreeNode* node = s.top();
      s.pop();

      res.push_back(node->val);
      if (node->right != NULL) {
        s.push(node->right);
      }
      if (node->left != NULL) {
        s.push(node->left);
      }
    }

    return res;
  }

  // Recursive traversal
  void RecursiveTraversal(TreeNode* node, vector<int>& vec) {
    if (node == NULL) {
      return;
    }

    vec.push_back(node->val);
    if (node->left != NULL) {
      RecursiveTraversal(node->left, vec);
    }
    
    if (node->right != NULL) {
      RecursiveTraversal(node->right, vec);
    }
  }
  
  vector<int> PreorderRecursiveTraversal(TreeNode* root) {
    vector<int> res;
    if (root == NULL) {
      return res;
    }

    RecursiveTraversal(root, res);

    return res;
  }
  
} // namespace preorder

int main(int argc, char** argv) {
  TreeNode* root = new TreeNode(3);
  root->right = new TreeNode(2);
  root->left = new TreeNode(1);

  //std::vector<int> res = postorder::postorderTraversal(root);
  //std::vector<int> res = postorder::postorderRecursiveTraversal(root);
  //std::vector<int> res = preorder::preorderTraversal(root);
  std::vector<int> res = preorder::PreorderRecursiveTraversal(root);
  for (size_t i = 0; i < res.size(); i ++) {
    LOG(INFO) << i << " : " << res[i];
  }
  
  return 0;
}
