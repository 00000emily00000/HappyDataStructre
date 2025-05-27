# Homework Sorting Project
## 組員

41243204 張品薰
41243205 黃詩方

---

### MinPQ.h
```cpp
#ifndef MINPQ_H
#define MINPQ_H

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                      // 虛擬解構函式
    virtual bool IsEmpty() const = 0;        // 是否為空
    virtual const T& Top() const = 0;        // 取最小值（min priority）
    virtual void Push(const T&) = 0;         // 插入
    virtual void Pop() = 0;                  // 移除最小值
};

#endif
```

### MinHeap.h
```cpp
#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
#include "MinPQ.h"

template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

    void Swim(int i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void Sink(int i) {
        int n = heap.size();
        while (2 * i + 1 < n) {
            int j = 2 * i + 1;
            if (j + 1 < n && heap[j + 1] < heap[j]) j++;
            if (heap[i] <= heap[j]) break;
            std::swap(heap[i], heap[j]);
            i = j;
        }
    }

public:
    MinHeap() {}

    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw std::underflow_error("Empty MinHeap");
        return heap[0];
    }

    void Push(const T& value) override {
        heap.push_back(value);
        Swim(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw std::underflow_error("Empty MinHeap");
        std::swap(heap[0], heap.back());
        heap.pop_back();
        if (!IsEmpty()) Sink(0);
    }
};

#endif
```
### main.cpp
```cpp
#include <iostream>
#include "MinHeap.h"

int main() {
    MinHeap<int> pq;

    pq.Push(5);
    pq.Push(3);
    pq.Push(8);
    pq.Push(1);

    while (!pq.IsEmpty()) {
        std::cout << pq.Top() << " ";
        pq.Pop();
    }
    std::cout << std::endl;

    return 0;
}
```
###  BST.h
```cpp
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
```

### BST.cpp
```cpp
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
```
### BinarySearchTree.cpp
```cpp
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
```
### DeleteBinarySearchTree
```cpp
#include <iostream>
#include <vector>
#include "BST.h"

void demonstrateDelete() {
    std::cout << "Part (b): Delete Function with Time Complexity Analysis\n";
    std::cout << "======================================================\n\n";

    BST tree;

    // Insert some sample values
    std::vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };

    std::cout << "Inserting values: ";
    for (int val : values) {
        std::cout << val << " ";
        tree.insert(val);
    }
    std::cout << "\nInitial tree height: " << tree.height() << std::endl;

    // Demonstrate deletion
    std::cout << "\nDeleting key 30 (node with two children)...\n";
    tree.deleteKey(30);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;

    std::cout << "\nDeleting key 10 (leaf node)...\n";
    tree.deleteKey(10);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;

    std::cout << "\nDeleting key 25 (node with one child)...\n";
    tree.deleteKey(25);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;
}

int main() {
    demonstrateDelete();
    return 0;
}
```
