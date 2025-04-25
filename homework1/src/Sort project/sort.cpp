#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>

using namespace std;
using namespace chrono;

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "----------------------------------------------------------" << endl;
    cout << "Memory Usage Information:" << endl;
    cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout << "----------------------------------------------------------" << endl;
}

template<class T>
void Permute(T* a, int n) {
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        swap(a[j], a[i]);
    }
}

void insertionSort(vector<int>& arr, int n) {
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

void quickSort(vector<int>& arr, int left, int right) {
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

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(arr.begin() + l, arr.begin() + m + 1), R(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    srand(time(0));
    const int trials = 10;
    for (int n = 1000; n <= 5000; n += 1000) {
        cout << "===== n = " << n << " =====" << endl;

        vector<double> times[4];
        double worst[4] = {};
        vector<int> worstArr[4]; // 用於儲存每個演算法的最差情況資料

        for (int t = 0; t < trials; ++t) {
            vector<int> original(n);
            for (int i = 0; i < n; ++i) original[i] = i;
            Permute(&original[0], n);

            for (int algo = 0; algo < 4; ++algo) {
                vector<int> a = original;  // 使用副本

                auto start = high_resolution_clock::now();

                switch (algo) {
                case 0: insertionSort(a, n); break;
                case 1: quickSort(a, 0, n - 1); break;
                case 2: mergeSort(a, 0, n - 1); break;
                case 3: heapSort(a, n); break;
                }

                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - start); // 改為微秒計算
                double elapsed = static_cast<double>(duration.count());

                times[algo].push_back(elapsed);
                if (elapsed > worst[algo]) {
                    worst[algo] = elapsed;
                    worstArr[algo] = a; // 保存最差情況的資料
                }
            }
        }

        const char* names[] = { "Insertion Sort", "Quick Sort    ", "Merge Sort    ", "Heap Sort     " };
        for (int i = 0; i < 4; ++i) {
            double avg = 0;
            for (double x : times[i]) avg += x;
            avg /= times[i].size();
            printf("%s - Worst: %.2f microseconds, Avg: %.2f microseconds\n", names[i], worst[i], avg);
            printMemoryUsage();
        }
    }
    return 0;
}