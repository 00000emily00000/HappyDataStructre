#ifndef BST_H
#define BST_H

// Binary Search Tree Node
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k);
};

class BST {
private:
    TreeNode* root;

    // Helper functions
    TreeNode* insert(TreeNode* node, int key);
    int getHeight(TreeNode* node);
    TreeNode* findMin(TreeNode* node);
    TreeNode* deleteNode(TreeNode* node, int key);
    void deleteTree(TreeNode* node);

public:
    BST();
    ~BST();

    void insert(int key);
    int height();
    void deleteKey(int key);
    void clear();
};

#endif // BST_H#pragma once
