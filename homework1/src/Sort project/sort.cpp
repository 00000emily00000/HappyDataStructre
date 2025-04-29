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

void buildMergeWorstCase(vector<int>& a, int left, int right) {
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

void merge(vector<int>& arr, int l, int m, int r, vector<int>& temp) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int x = l; x <= r; ++x) arr[x] = temp[x];
}

void mergeSort(vector<int>& arr, int l, int r, vector<int>& temp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, temp);
        mergeSort(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
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
        vector<int> worstArr[4];

        for (int t = 0; t < trials; ++t) {
            vector<int> original(n);
            for (int i = 0; i < n; ++i) original[i] = i;

            // 快速排序隨機輸入
            Permute(&original[0], n);
            vector<int> qsInput = original;

            // 合併排序最壞輸入
            vector<int> msInput(n);
            for (int i = 0; i < n; ++i) msInput[i] = i;
            buildMergeWorstCase(msInput, 0, n - 1);

            for (int algo = 0; algo < 4; ++algo) {
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
