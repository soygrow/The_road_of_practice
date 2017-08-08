/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * mini_depth.cc
 * ---------------------------------------------------------------------------
 * Given a binary tree, find its minimum depth.The minimum depth is the number
 * of nodes along the shortest path from the root node down to the nearest 
 * leaf node.
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int val;
	
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

std::queue<TreeNode*> q_up;
std::queue<TreeNode*> q_down;

int run(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
        
    int depth = 0;
    q_up.push(root);
    while (q_up.size() > 0 || q_down.size() > 0) {
        if (q_up.size() > 0) {
            depth ++;
        }
        while (q_up.size() > 0) {
            TreeNode* node = q_up.front();
            if (node && node->left == NULL && node->right == NULL) {
                return depth;
            } else {
                if (node && node->left != NULL) {
                    q_down.push(node->left);
                }
                if (node && node->right != NULL) {
                    q_down.push(node->right);
                }
            }
            q_up.pop();
        }
        if (q_down.size() > 0) {
            depth ++;
        }
        while (q_down.size() > 0) {
            TreeNode* node = q_down.front();
            if (node && node->left == NULL && node->right == NULL) {
                return depth;
            } else {
                if (node && node->left != NULL) {
                    q_up.push(node->left);
                }
                    
                if (node && node->right != NULL) {
                    q_up.push(node->right);
                }
            }
            q_down.pop();
        }
    }
        
    return depth;
}

int main()
{
    cout << "Hello World" << endl;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
	
    std::cout << run(root) << std::endl;
	
    return 0;
}
