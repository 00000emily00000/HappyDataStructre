#include "BST.h"
#include <algorithm>

// TreeNode constructor
TreeNode::TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}

// BST constructor
BST::BST() : root(nullptr) {}

// BST destructor
BST::~BST() {
    deleteTree(root);
}

// Helper function to insert a node
TreeNode* BST::insert(TreeNode* node, int key) {
    if (node == nullptr) {
        return new TreeNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    // If key already exists, do nothing

    return node;
}

// Helper function to calculate height
int BST::getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

// Helper function to find minimum value node
TreeNode* BST::findMin(TreeNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Helper function to delete a node
TreeNode* BST::deleteNode(TreeNode* node, int key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }
    else {
        // Node to be deleted found

        // Case 1: No child or only right child
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        // Case 2: Only left child
        else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: Two children
        TreeNode* temp = findMin(node->right);
        node->key = temp->key;
        node->right = deleteNode(node->right, temp->key);
    }

    return node;
}

// Helper function to delete entire tree
void BST::deleteTree(TreeNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Public function to insert a key
void BST::insert(int key) {
    root = insert(root, key);
}

// Public function to get tree height
int BST::height() {
    return getHeight(root);
}

// Public function to delete a key
void BST::deleteKey(int key) {
    root = deleteNode(root, key);
}

// Public function to clear the tree
void BST::clear() {
    deleteTree(root);
    root = nullptr;
}