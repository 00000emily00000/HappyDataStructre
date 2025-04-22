# 排序演算法實作與效能分析報告

## 一、作業目標與內容
本作業旨在實作五種排序演算法，並對其在不同資料量 (n = 500, 1000, 2000, 3000, 4000, 5000) 下的效能進行分析與比較。內容包含：

1. 討論各演算法的 worst-case 與 average-case。
2. 實作以下排序演算法：
   - Insertion Sort
   - Quick Sort（採用 median-of-three pivot）
   - Merge Sort（採用 iterative 方法）
   - Heap Sort
   - Composite Sort（依據資料特性選擇最佳排序法）
3. 實測每種演算法的執行時間與記憶體用量，並繪製圖表。
4. 分析理論時間複雜度與實測結果的差異。
5. 探討計時方式與精度。
6. 說明測試資料產生方式。
7. 提供完整程式碼與說明。

---

## 二、各排序法之 Worst-case 與 Average-case 分析

### 1. Insertion Sort
- **Worst-case**: 當輸入為反向排序（如：[n, n-1, ..., 1]）
- **Average-case**: 輸入為隨機排列
- **時間複雜度**：
  - Worst: $O(n^2)$
  - Average: $O(n^2)$

### 2. Quick Sort（Median-of-three）
- **Worst-case**: 若 pivot 選擇仍不佳（極端偏向一側），如幾乎已排序的資料。
- **Average-case**: 輸入為隨機排列，median-of-three 有助於減少 worst-case 機率
- **時間複雜度**：
  - Worst: $O(n^2)$
  - Average: $O(n \log n)$

### 3. Merge Sort（Iterative）
- **Worst-case / Average-case**: 均為隨機或任何輸入，演算法穩定
- **時間複雜度**：
  - Worst: $O(n \log n)$
  - Average: $O(n \log n)$

### 4. Heap Sort
- **Worst-case / Average-case**: 隨機資料、特定資料形狀皆會觸發相同操作數
- **時間複雜度**：
  - Worst: $O(n \log n)$
  - Average: $O(n \log n)$

### 5. Composite Sort
- 根據資料特性動態選擇排序法，會在程式中實作對應邏輯。

---

## 三、實作與測試資料說明

### 1. 測試資料產生方式
- **Average-case**:
  - 每個 n 值產生 10 組隨機資料，並儲存供所有排序法使用
- **Worst-case**:
  - Insertion Sort: 使用倒序列
  - Quick Sort: 利用已排序或幾乎已排序資料（透過 median-of-three 產生最差分割）
  - Merge Sort / Heap Sort: 產生多筆隨機資料後挑選排序最慢者

### 2. 測試方法
- 每次排序皆使用 `time.perf_counter()` 測量執行時間（精度可達奈秒）
- 使用 `tracemalloc` 測量記憶體使用量

---

## 四、實驗結果與圖表
（此處將插入執行時間與記憶體圖表）

### 範例圖表：執行時間（ms）
| n | Insertion | Quick | Merge | Heap | Composite |
|---|-----------|-------|-------|------|-----------|
|500|   3.1     | 1.2   | 1.3   | 1.5  | 1.1       |
|...| ...       | ...   | ...   | ...  | ...       |

### 範例圖表：記憶體使用量（KB）
（待測試數據填入）

---

## 五、時間複雜度與結果比對分析
- Merge Sort 與 Heap Sort 在大型資料量表現穩定
- Insertion Sort 僅於小資料量具優勢，n>1000 後效能明顯下降
- Quick Sort 平均表現佳，但最差情況需注意
- Composite Sort 根據資料特性能有效選用最佳演算法

---

## 六、Composite Sort 設計邏輯
```python
if n <= 1000:
    use Insertion Sort
elif 資料接近排序:
    use Insertion Sort 或 Quick Sort
elif 重複元素多:
    use Merge Sort
else:
    use Heap Sort
```

---

## 七、程式碼分段說明
（每個排序法會提供實作程式碼與註解，詳見附錄）

---

## 八、結語
本作業透過五種排序演算法的實作與比對，深入探討不同資料量與資料形狀對排序效率的影響，進一步設計出針對性更高的 Composite Sort，以達到最佳排序效率。

---

## 九、附錄：程式碼
（將完整程式碼拆分並標註說明）

