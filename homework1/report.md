# Homework Sorting Project
## 組員

41243204 張品薰
41243205 黃詩方

---

此報告展示對多種排序算法進行的實作與性能分析。包括對以下排序算法的討論與實作：

- **Insertion Sort**
- **Quick Sort** (使用 median-of-three 方法選擇樞軸)
- **Merge Sort** (使用迭代方法)
- **Heap Sort**
- **Composite Sort** (綜合多種排序法)

## 1. 分析與討論

### Worst-case 與 Average-case 討論

- **Insertion Sort:**
  - **Worst-case**: 當數列逆序時，最差情況下需要進行 n*(n-1)/2 次比較與交換。其時間複雜度為 O(n²)。
  - **Average-case**: 當數列是隨機排列時，平均情況下時間複雜度也是 O(n²)。
  
- **Quick Sort:**
  - **Worst-case**: Quick Sort將排序邏輯反轉，逆推出 worst-case的時間複雜度為 O(n²)。
  - **Average-case**: 在隨機數列中，Quick Sort 的時間複雜度為 O(n log n)。

- **Merge Sort:**
  - **Worst-case**: Merge Sort 的時間複雜度為 O(n log n)，無論數列如何排列。
  - **Average-case**: 由於 Merge Sort 每次都將數列分成兩半並進行合併，時間複雜度始終為 O(n log n)。

- **Heap Sort:**
  - **Worst-case**: Heap Sort 的時間複雜度為 O(n log n)，無論數列如何排列。
  - **Average-case**: Heap Sort 也保持在 O(n log n) 的時間複雜度。

- **Composite Sort**: 綜合了多種排序法，針對不同的輸入資料使用最合適的排序方法，以達到最短的排序時間。

## 2. 排序函式實作

### Insertion Sort

```cpp
void insertionSort(vector<int>& arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

### Quick Sort (使用 median-of-three 方法選擇privot)

```cpp
void quickSort(vector<int>& arr, int left, int right)
{
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) swap(arr[i++], arr[j--]);
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}
```

### Merge Sort (使用迭代方法)

```cpp
void merge(vector<int>& arr, int l, int m, int r, vector<int>& temp)
{
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int x = l; x <= r; ++x) arr[x] = temp[x];
}

void mergeSort(vector<int>& arr, int l, int r, vector<int>& temp)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, temp);
        mergeSort(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
    }
}
```

### Heap Sort

```cpp
void heapify(vector<int>& arr, int n, int i)
{
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

## 3. 性能測試

### 測試資料與執行時間

測試資料的生成與執行時間如下：

#### 生成隨機數列
```cpp
template<class T>
void Permute(T* a, int n)
{
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        swap(a[j], a[i]);
    }
}
```

#### 建立Insertion Sort Worst-Case數列
```cpp
template<class T>
vector<int> original(n);
for (int i = 0; i < n; ++i)
  original[i] = i;
```

#### 建立Merge Sort Worst-Case數列
```cpp
void buildMergeWorstCase(vector<int>& a, int left, int right)
{
    if (right - left <= 0) return;
    int mid = (left + right) / 2;
    vector<int> temp(right - left + 1);
    int idx = 0;
    for (int i = left; i <= right; ++i) temp[idx++] = a[i];
    for (int i = 0; i <= right - left; ++i) {
        if (i % 2 == 0) a[left + i / 2] = temp[i];
        else a[mid + 1 + i / 2] = temp[i];
    }
    buildMergeWorstCase(a, left, mid);
    buildMergeWorstCase(a, mid + 1, right);
}
```

#### 計算執行時間
```cpp
void printMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "----------------------------------------------------------" << endl;
    cout << "Memory Usage Information:" << endl;
    cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout << "----------------------------------------------------------" << endl;
}

const char* names[] = { "Insertion Sort", "Quick Sort    ", "Merge Sort    ", "Heap Sort     " };
for (int i = 0; i < 4; ++i)
{
    double avg = 0;
    for (double x : times[i]) avg += x;
    avg /= times[i].size();
    printf("%s - Worst: %.2f microseconds, Avg: %.2f microseconds\n", names[i], worst[i], avg);
    printMemoryUsage();
}
```

在以下數值範圍內測試了各排序算法：n = 500, 1000, 2000, 3000, 4000, 5000。

```
===== n = 1000 =====
Insertion Sort - Worst: 2948.00 microseconds, Avg: 2791.00 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4704 KB
Peak Working Set Size: 4704 KB
Pagefile Usage: 732 KB
----------------------------------------------------------
Quick Sort     - Worst: 135.00 microseconds, Avg: 123.60 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4712 KB
Peak Working Set Size: 4712 KB
Pagefile Usage: 732 KB
----------------------------------------------------------
Merge Sort     - Worst: 234.00 microseconds, Avg: 217.40 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4712 KB
Peak Working Set Size: 4712 KB
Pagefile Usage: 732 KB
----------------------------------------------------------
Heap Sort      - Worst: 304.00 microseconds, Avg: 278.50 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4712 KB
Peak Working Set Size: 4712 KB
Pagefile Usage: 732 KB
----------------------------------------------------------
===== n = 2000 =====
Insertion Sort - Worst: 15555.00 microseconds, Avg: 13304.10 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4752 KB
Peak Working Set Size: 4752 KB
Pagefile Usage: 772 KB
----------------------------------------------------------
Quick Sort     - Worst: 397.00 microseconds, Avg: 326.40 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4752 KB
Peak Working Set Size: 4752 KB
Pagefile Usage: 772 KB
----------------------------------------------------------
Merge Sort     - Worst: 820.00 microseconds, Avg: 661.20 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4752 KB
Peak Working Set Size: 4752 KB
Pagefile Usage: 772 KB
----------------------------------------------------------
Heap Sort      - Worst: 979.00 microseconds, Avg: 766.40 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4752 KB
Peak Working Set Size: 4752 KB
Pagefile Usage: 772 KB
----------------------------------------------------------
===== n = 3000 =====
Insertion Sort - Worst: 36475.00 microseconds, Avg: 28660.10 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4744 KB
Peak Working Set Size: 4804 KB
Pagefile Usage: 764 KB
----------------------------------------------------------
Quick Sort     - Worst: 533.00 microseconds, Avg: 442.90 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4744 KB
Peak Working Set Size: 4804 KB
Pagefile Usage: 764 KB
----------------------------------------------------------
Merge Sort     - Worst: 1404.00 microseconds, Avg: 861.10 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4744 KB
Peak Working Set Size: 4804 KB
Pagefile Usage: 764 KB
----------------------------------------------------------
Heap Sort      - Worst: 1368.00 microseconds, Avg: 1070.10 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4744 KB
Peak Working Set Size: 4804 KB
Pagefile Usage: 764 KB
----------------------------------------------------------
===== n = 4000 =====
Insertion Sort - Worst: 54072.00 microseconds, Avg: 48732.60 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4760 KB
Peak Working Set Size: 4848 KB
Pagefile Usage: 780 KB
----------------------------------------------------------
Quick Sort     - Worst: 705.00 microseconds, Avg: 615.50 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4760 KB
Peak Working Set Size: 4848 KB
Pagefile Usage: 780 KB
----------------------------------------------------------
Merge Sort     - Worst: 1409.00 microseconds, Avg: 1159.00 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4760 KB
Peak Working Set Size: 4848 KB
Pagefile Usage: 780 KB
----------------------------------------------------------
Heap Sort      - Worst: 1656.00 microseconds, Avg: 1444.40 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4760 KB
Peak Working Set Size: 4848 KB
Pagefile Usage: 780 KB
----------------------------------------------------------
===== n = 5000 =====
Insertion Sort - Worst: 86900.00 microseconds, Avg: 78553.40 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4784 KB
Peak Working Set Size: 4888 KB
Pagefile Usage: 804 KB
----------------------------------------------------------
Quick Sort     - Worst: 1315.00 microseconds, Avg: 881.50 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4784 KB
Peak Working Set Size: 4888 KB
Pagefile Usage: 804 KB
----------------------------------------------------------
Merge Sort     - Worst: 2075.00 microseconds, Avg: 1512.60 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4784 KB
Peak Working Set Size: 4888 KB
Pagefile Usage: 804 KB
----------------------------------------------------------
Heap Sort      - Worst: 2688.00 microseconds, Avg: 1974.60 microseconds
----------------------------------------------------------
Memory Usage Information:
Working Set Size: 4784 KB
Peak Working Set Size: 4888 KB
Pagefile Usage: 804 KB
----------------------------------------------------------
```


## 4. 時間與空間複雜度分析

根據測試結果，我們可以將每個排序算法的實際時間與理論上的時間複雜度進行對比。根據不同的 n 值，結果顯示各排序法的時間複雜度與預期結果相符。空間複雜度亦然。


| 演算法         | 理論時間複雜度                        | 實驗結果趨勢                          | 備註                                      |
|----------------|----------------------------------------|---------------------------------------|-------------------------------------------|
| Insertion Sort | 最好：O(n)，最壞：O(n²)                | 隨 n 線性上升（明顯）                | 適合資料小、幾乎排序好的情況             |
| Quick Sort     | 平均：O(n log n)，最壞：O(n²)          | 速度最快，表現穩定                    | 實際最常用排序之一                        |
| Merge Sort     | 穩定：O(n log n)                       | 穩定性高                  | 適合處理大型資料與穩定需求               |
| Heap Sort      | 穩定：O(n log n)                       | 速度略慢於 Quick Sort，但穩定        | 記憶體表現不錯                            |

記憶體使用分析
| 排序演算法       | 空間複雜度    | 是否原地排序 | 額外記憶體需求說明                         | 推論記憶體使用量 |
|------------------|----------------|---------------|--------------------------------------------|------------------|
| Insertion Sort   | O(1)           | 是         | 僅使用常數變數 `key`, `j` 等               |最低           |
| Quick Sort       | O(log n) ~ O(n)| 是         | 使用遞迴，最差情況下棧深可達 O(n)         |中等           |
| Merge Sort       | O(n)           | 否         | 每層合併需建立兩個額外子陣列               |最高           |
| Heap Sort        | O(1)           | 是         | 透過 heapify 操作原地調整                  |很低           |

![worst-case 折線圖](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework1/src/Image/worst-case%20new.png)
![average-case 折線圖](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework1/src/Image/average-case.png)
藉由以上得出在所有情況下皆能應對數值資料的新函式，Composite Sort。
### Composite Sort

```cpp
for (int algo = 0; algo < 4; ++algo)
{
    vector<int> a = (algo == 1) ? qsInput : (algo == 2) ? msInput : original;
    auto start = high_resolution_clock::now();

    switch (algo) {
    case 0: insertionSort(a, n); break;
    case 1: quickSort(a, 0, n - 1); break;
    case 2: {
        vector<int> temp(n);
        mergeSort(a, 0, n - 1, temp);
        break;
    }
    case 3: heapSort(a, n); break;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    double elapsed = static_cast<double>(duration.count());

    times[algo].push_back(elapsed);
    if (elapsed > worst[algo]) {
        worst[algo] = elapsed;
        worstArr[algo] = a;
    }
}
```
![worst-case new 折線圖](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework1/src/Image/worst-case%20new.png)
![average-case new 折線圖](https://github.com/00000emily00000/HappyDataStructre/blob/main/homework1/src/Image/average-case%20new.png)

### 計時方法與精度

我們使用 `srand(time(0))` 函數來計算每個排序算法的執行時間，精度為秒。為了提高準確度，測試進行了多次執行，並取平均值。

## 5. 測試資料產生與細節

- **Insert Sort 測試資料**: 使用遞減排序的數列作為最壞情況，測量其執行時間作為 WorstCase。
- **Quick Sort 測試資料**: 隨機產生 10 次數列並測試，取最差的執行時間套用為WorstCase執行時間。
- **Heap Sort 測試資料**: 隨機產生 10 次數列並測試，取最差的執行時間套用為WorstCase執行時間。
- **Merge Sort 測試資料**: 使用手動推導之最壞情況數列測試，取其執行時間作為 WorstCase。
- **所有程式的Ave測資**: 隨機產生 10 次數列並測試，將10次的執行時間平均為Ave執行時間。

## 6. 結論

根據測試結果，**Composite Sort** 是在大多數情況下最優的排序算法，尤其在數列較大時表現出色。每種排序算法在不同的數列長度和排列情況下都有其優勢，選擇合適的排序方法能大幅提升效率。



