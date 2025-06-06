# Homework Sorting Project
## 組員

41243204 張品薰
41243205 黃詩方

---
## 第一題
![Max/Min Heap](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework2/src/Image/MinHeap.png)

### 解題說明
本作業實作一個最小優先佇列（Min Priority Queue），並以 **最小堆積（Min Heap）** 的資料結構來實現。整體程式共分為三個檔案：

### 1. MinPQ.h - 抽象類別定義
這是一個模板抽象類別 MinPQ<T>，定義了最小優先佇列的基本操作介面，包括：
- **IsEmpty()**：檢查佇列是否為空
- **Top()**：取得最小元素（具有最高優先權的元素）
- **Push(const T&)**：插入新元素
- **Pop()**：移除最小元素
- **虛擬解構函式** ：供繼承類別適當釋放資源

```cpp
#ifndef MINPQ_H
#define MINPQ_H

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                      
    virtual bool IsEmpty() const = 0;        
    virtual const T& Top() const = 0;        
    virtual void Push(const T&) = 0;         
    virtual void Pop() = 0;                  
};

#endif
```

### 2. MinHeap.h - 最小堆積實作
此檔案繼承 MinPQ<T> 並使用 std::vector<T> 來實作最小堆積邏輯，保證 Top() 回傳的總是最小元素：
- **Swim (上浮)**：當插入新元素後，自底向上調整位置以維持最小堆性質
- **Sink (下沉)**：移除最小元素後，自頂向下調整堆
  
主要函式包括：
- **Push(const T&)**：插入元素並上浮
- **Pop()**：移除堆頂元素並下沉
- **Top()**：回傳堆頂元素
- **IsEmpty()**：檢查堆是否為空
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
### 3. 測試主程式 – main()
此段程式用來測試 MinHeap<int> 類別的功能：
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
### 執行結果
插入 4 個整數後，透過迴圈依序取出最小值進行列印。預期輸出為排序後的結果：
```cpp
1 3 5 8
```
### 結論
本作業成功實作了一個以最小堆積為基礎的最小優先佇列，符合抽象介面的需求。整體程式設計具有良好的擴充性與模組化特性：
- 利用模板與純虛擬函式設計，使此優先佇列可套用於各種類型。
- MinHeap 使用向量與經典的上浮/下沉操作來維持堆性質，操作效率良好（插入與移除的時間複雜度為 O(log n)）。
- 測試程式驗證了基本功能正確性，成功地按照從小到大的順序輸出元素。

本作業不僅強化了對資料結構中「堆積」的理解，也實踐了抽象類別與繼承的應用，有助於日後實作更複雜的資料結構與演算法。



---
## 第二題
![Binary Search Tree](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework2/src/Image/BinarySearchTree.png)

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

### 隨機樹生成器
```cpp
std::random_device rd;
std::mt19937 gen(rd());
```

### BinarySearchTree.cpp
```cpp
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <iomanip>
#include "BST.h"

void analyzeHeight() {
    std::cout << "Part (a): Binary Search Tree Height Analysis\n";
    std::cout << "==========================================\n\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> sizes = { 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };

    std::cout << std::setw(8) << "n"
        << std::setw(10) << "Height"
        << std::setw(12) << "log2(n)"
        << std::setw(15) << "Height/log2(n)" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (int n : sizes) {
        BST tree;
        std::uniform_int_distribution<> dis(1, n * 10); // Generate random numbers

        // Insert n random values
        for (int i = 0; i < n; i++) {
            tree.insert(dis(gen));
        }

        int height = tree.height();
        double log2n = log2(n);
        double ratio = height / log2n;

        std::cout << std::setw(8) << n
            << std::setw(10) << height
            << std::setw(12) << std::fixed << std::setprecision(2) << log2n
            << std::setw(15) << std::setprecision(3) << ratio << std::endl;
    }

    std::cout << "\nObservation: The ratio height/log2(n) should be approximately constant around 2,\n";
    std::cout << "confirming that the average height of a randomly built BST is O(log n).\n";
}

int main() {
    analyzeHeight();
    return 0;
}
```
### Part(A) 執行結果
```cpp
Part (a): Binary Search Tree Height Analysis
==========================================

       n    Height     log2(n) Height/log2(n)
---------------------------------------------
     100        14        6.64          2.107
     500        23        8.97          2.565
    1000        19        9.97          1.907
    2000        24       10.97          2.189
    3000        26       11.55          2.251
    4000        27       11.97          2.256
    5000        29       12.29          2.360
    6000        27       12.55          2.151
    7000        28       12.77          2.192
    8000        32       12.97          2.468
    9000        31       13.14          2.360
   10000        28       13.29          2.107

Observation: The ratio height/log2(n) should be approximately constant around 2,
confirming that the average height of a randomly built BST is O(log n).
```
### 說明：

- 使用隨機產生的整數，對不同資料筆數 `n`（100 到 10000）建立 Binary Search Tree（BST）。
- 每棵樹皆透過 `insert()` 插入節點形成，資料順序為隨機。
- 使用 `height()` 計算 BST 的高度，並比較理論高度 `log₂(n)`。
- 計算 `Height / log₂(n)` 比值，以觀察平均樹高是否符合 O(log n)。

### 結論：

- 隨著節點數的增加，BST 高度與 log₂(n) 呈現接近線性關係。
- 高度與 log₂(n) 的比值大多維持在約 2 左右。
- 結論支持：**隨機建立的 BST 在平均情況下高度為 O(log n)**，結構相對平衡。

---
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
### Part(B) 執行結果
```cpp
Part (b): Delete Function with Time Complexity Analysis
======================================================

Inserting values: 50 30 70 20 40 60 80 10 25 35 45
Initial tree height: 4

Deleting key 30 (node with two children)...
Tree height after deletion: 4

Deleting key 10 (leaf node)...
Tree height after deletion: 4

Deleting key 25 (node with one child)...
Tree height after deletion: 4
```

### 說明：
- 建立初始 BST，插入節點如下：  
  `{50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45}`  
  → 此為一棵高度為 4 的完整 BST。
- 接著分別刪除以下三種不同情況的節點，以驗證 `delete()` 函數邏輯：
  1. 刪除「有兩個子節點」的節點（30）
  2. 刪除「葉節點」（10）
  3. 刪除「只有一個子節點」的節點（25）
- 每次刪除後觀察 BST 的高度變化。
  
### 結論
- BST 的 `delete()` 函數能正確處理三種情況的節點刪除：
  1. **刪除有兩個子節點的節點**（如 30）：會尋找右子樹中的最小值替代，維持 BST 的順序性。
  2. **刪除葉節點**（如 10）：直接刪除即可，無需重接子樹。
  3. **刪除僅有一個子節點的節點**（如 25）：會讓該節點的子節點頂替其位置。
- 執行後 BST 的高度皆維持不變（仍為 4），表示刪除操作對樹的整體結構影響極小。
- 此實驗驗證了 BST 刪除操作的正確性與穩定性，並符合理論上 **平均 O(log n)** 的時間複雜度。
  
---
## 第三題
![Exercise](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework2/src/Image/Exercise.png)

### 外部排序（External Sorting）Phase 2 分析

#### (a) 計算第二階段的輸入時間（Input Time）
- **每筆資料的磁碟讀取時間：**
    - Seek time = `1` 秒
    - Latency time = `4` 秒
    - 傳輸時間（Transmission time） = `t = 10^-3` 秒/record
    - 總時間（每筆）：`1 + 4 + 0.001 = 5.001` 秒

- **計算合併所需的輪數：**
    - 每輪最多合併 `k` 個 runs
    - 所需合併輪數 ≈ `log_k(m)`
    - 每輪要讀全部 `n` 筆資料

- **輸入總時間公式：**

$$
T_{\text{input}} = \log_k(64) \cdot 200000 \cdot (1 + 4 + 0.001) = \log_k(64) \cdot 200000 \cdot 5.001
$$

- **(a) 最終答案：**

$$
T_{\text{input}} = 200000 \cdot 5.001 \cdot \log_k(64)
$$

#### (b) 作圖與分析：輸入時間 T vs k
- **選定幾個 k 值來計算：**

| k   | logₖ(64) | 輸入時間 T_input（秒）            |
|-----|----------|------------------------------------|
| 2   | 6        | 6 × 200000 × 5.001 = **6,001,200** |
| 4   | 3        | 3 × 200000 × 5.001 = **3,000,600** |
| 8   | 2        | 2 × 200000 × 5.001 = **2,000,400** |
| 16  | 1.5      | 1.5 × 200000 × 5.001 = **1,500,300** |
| 32  | 1.2      | 1.2 × 200000 × 5.001 = **1,200,240** |
| 64  | 1        | 1 × 200000 × 5.001 = **1,000,200** |

- **趨勢觀察：**
    - 隨著 `k ↑`，`log_k(64) ↓`，輸入時間會 **下降**
    - 但 `k` 不可無限大，受限於記憶體空間

- **記憶體限制：**
    - 每個 run 需一個 input buffer
    - 預留 1 個 output buffer ⇒ 最多支援 `k = S - 1 = 1999`
    - 但實際只有 `m = 64` 個 runs ⇒ `k ≤ min(64, 1999) = 64`

#### 是否存在某個 k 使得 T_input = T_CPU？

假設 CPU 處理時間 `t_CPU = 1,500,000` 秒  
觀察上表，`k = 16` 時：

- 輸入時間 T_input = **1,500,300 秒** ≈ CPU 處理時間  
✔️ 可以找到符合的 k

#### 結論
- 第二階段輸入時間：T_input = 200000 × 5.001 × logₖ(64)
- `k` 越大，輪數越少 ⇒ 輸入時間越短
- `k` 的最大值由記憶體空間與 run 數決定
- 存在某些 `k` 使得輸入時間 ≈ CPU 處理時間
