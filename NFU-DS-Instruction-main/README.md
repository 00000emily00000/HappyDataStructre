# NFU 資料結構作業規範

- [教學投影片連結](https://docs.google.com/presentation/d/1U31srG7KL6rc0ls3-XUchzfBFKQkm7f2B_Ab9VUwRks)
- [**作業報告樣板請點我**](https://github.com/NFU-OpenDataStructure/Homework-template)

作業上傳三步驟：

1. 上傳程式碼（.cpp 或 .h ）至專案。
2. 上傳 markdown 作業報告至專案。
3. 上傳專案連結至 uLearn 作業區。

## 作業繳交重點

- 報告只能使用 markdown 格式，不接受其他格式。
- 報告檔名必需完全為 `report`。
- 作業以資料夾為單位，請務必建立相同的[目錄架構](#目錄架構)。
- 上傳程式碼到專案後，仍需把程式碼付在作業報告中。

作業報告配分：

| 項目              | 配分 |
|-------------------|------|
| 1. 解題說明       | 15%  |
| 2. 程式實作       | 30%  |
| 3. 效能分析       | 10%  |
| 4. 測試與驗證     | 20%  |
| 5. 申論及開發報告 | 25%  |

上學期限用標頭（下學期不限制）：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
```

> [!CAUTION]
>
> 1. 作業使用 GitHub Action 做格式檢查。
> 2. 你的專案要有 `.github` 資料夾和底下的所有檔案。
> 3. 作業截止前 GitHub Action 沒通過，請根據規格更新你的作業報告。
> 4. 作業截止後 GitHub Action 沒狀態、沒通過，**作業等於沒交**。

## 目錄架構

```plain
.
├── homework1/
│   ├── src/
│   └── report.md
├── homework2/
│   ├── src/
│   └── report.md
└── homework3/
    ├── src/
    └── report.md
```

## markdown 語法教學

| **功能**     | **語法**                      | **顯示效果**                           |
|--------------|-------------------------------|----------------------------------------|
| **粗體**     | `**粗體**` 或 `__粗體__`      | **粗體**                               |
| **斜體**     | `*斜體*` 或 `_斜體_`          | *斜體*                                 |
| **超連結**   | `[超連結文字說明](網址)` | [點我](https://example.com)            |
| **圖片**     | `![圖片描述](圖片網址)`       | ![示例](https://picsum.photos/200/300) |
| **無序清單** | `- 項目 1` <br> `- 項目 2`    | - 項目 1 <br> - 項目 2                 |
| **有序清單** | `1. 第一項` <br> `2. 第二項`  | 1. 第一項 <br> 2. 第二項               |
| **數學式**   | `$O(\log n)$`。               | $O(\log n)$                            |

使用以下語法就可以將程式附加在 markdown 報告中：

``````plain
```cpp
#include <iostream>

using namesapce std;

int main() {
    cout << "hello world" << '\n';
}
```
``````

markdown 預覽：

```cpp
#include <iostream>

using namesapce std;

int main() {
    cout << "hello world" << '\n';
}
```

## 作業章節說明

### 1. 解題說明

需撰寫「解題方法」：

1. 問題描述：清楚陳述題目背景與要求。
2. 解題策略：提供您的規劃步驟，例如使用演算法或資料結構。

### 2. 程式實作

上傳程式碼到專案後，仍需把程式碼付在 markdown 報告中。

> [!CAUTION]
> 編輯器、IDE 使用者**請把程式碼自行貼在報告裡**。

### 3. 效能分析

針對程式碼的效能進行 Big-O 分析，說明兩種複雜度的狀況：

1. 時間複雜度。
2. 空間複雜度。

> [!NOTE]  
>
> - 通用格式： $O(1)$ 、 $O(\log n)$ 、 $O(n)$ 、 $O(n^2)$ 、 $O(2^n)$
> - 詳細分析： $O(100\times \log n + \pi)$
>

### 4. 測試與驗證

程式的輸入與輸出。

> [!IMPORTANT]  
> 非 IDE 使用者「程式輸入與輸出」需含編譯指令、編譯參數以及輸出，如下列表示：
>
> ``````plain
> ```shell
> $ g++ main.c --std=c++21 -o main.exe
> $ .\main.exe
> hello world!
> ```
> ``````
>
> `$` 代表使用者在 shell 中的輸入。
>
> - `$ g++ main.c --std=c++21 -o main.exe` 是編譯指令
> - `$ .\main.exe` 是執行指令
> - 最後沒有 `$` 的 `hello world!` 代表程式輸出。
>
> 只要像這樣寫就能清楚表達，哪個是使用者輸入與程式輸出。
>

### 5. 申論及開發報告

寫下使用到某資料結構、演算法的原因。
