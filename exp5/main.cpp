#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>



void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
        std::swap(arr[min_idx], arr[i]);
    }
}

void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

std::vector<int> generateRandomArray(int size, int min_value, int max_value) {
    std::vector<int> arr(size);
    std::random_device rd;  // 随机数生成器
    std::mt19937 gen(rd()); // 以随机设备作为种子的梅森旋转算法生成器
    std::uniform_int_distribution<> distr(min_value, max_value); // 均匀分布的整数

    for (int &value : arr) {
        value = distr(gen); // 生成随机数并赋值给数组元素
    }
    return arr;
}

std::vector<int> generateAscendingArray(int size, int start = 1) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = start + i;
    }
    return arr;
}

std::vector<int> generateDescendingArray(int size, int start = 1) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = start - i;
    }
    return arr;
}

int main() {
    std::vector<int> arrA = generateRandomArray(1000, 1, 5000);
    std::vector<int> arrB = generateAscendingArray(1000, 1);
    std::vector<int> arrC = generateDescendingArray(1000, 1000);

    std::cout << "Random Array Test";
    // Bubble Sort
    std::vector<int> arr11 = arrA;
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr11);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Sorted array (Bubble Sort): ";

    std::cout << "Time taken by bubble sort: " << elapsed.count() << " seconds" << std::endl;

    // Insertion Sort
    std::vector<int> arr21 = arrA;
    start = std::chrono::high_resolution_clock::now();
    insertionSort(arr21);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Sorted array (Insertion Sort): ";

    std::cout << "Time taken by insertion sort: " << elapsed.count() << " seconds" << std::endl;

    // Selection Sort
    std::vector<int> arr31 = arrA;
    start = std::chrono::high_resolution_clock::now();
    selectionSort(arr31);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Sorted array (Selection Sort): ";

    std::cout << "Time taken by selection sort: " << elapsed.count() << " seconds" << std::endl;

    // Merge Sort
    std::vector<int> arr41 = arrA;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(arr41, 0, arr41.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Sorted array (Merge Sort): ";

    std::cout << "Time taken by merge sort: " << elapsed.count() << " seconds" << std::endl;

    // Quick Sort
    std::vector<int> arr51 = arrA;
    start = std::chrono::high_resolution_clock::now();
    quickSort(arr51, 0, arr51.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Sorted array (Quick Sort): ";

    std::cout << "Time taken by quick sort: " << elapsed.count() << " seconds" << std::endl;

    // Heap Sort
    std::vector<int> arr61 = arrA;
    start = std::chrono::high_resolution_clock::now();
    heapSort(arr61);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Sorted array (Heap Sort): ";

    std::cout << "Time taken by heap sort: " << elapsed.count() << " seconds"<<std::endl;

    std::cout << "Ascending Array Test"<<std::endl;
    // Bubble Sort
    std::vector<int> arr12 = arrB;
    auto start2 = std::chrono::high_resolution_clock::now();
    bubbleSort(arr12);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "Sorted array (Bubble Sort): ";

    std::cout << "Time taken by bubble sort: " << elapsed2.count() << " seconds" << std::endl;

    // Insertion Sort
    std::vector<int> arr22 = arrB;
    start2 = std::chrono::high_resolution_clock::now();
    insertionSort(arr22);
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "Sorted array (Insertion Sort): ";

    std::cout << "Time taken by insertion sort: " << elapsed2.count() << " seconds" << std::endl;

    // Selection Sort
    std::vector<int> arr32 = arrB;
    start2 = std::chrono::high_resolution_clock::now();
    selectionSort(arr32);
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "Sorted array (Selection Sort): ";

    std::cout << "Time taken by selection sort: " << elapsed2.count() << " seconds" << std::endl;

    // Merge Sort
    std::vector<int> arr42 = arrB;
    start2 = std::chrono::high_resolution_clock::now();
    mergeSort(arr42, 0, arr42.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "Sorted array (Merge Sort): ";

    std::cout << "Time taken by merge sort: " << elapsed2.count() << " seconds" << std::endl;

    // Quick Sort
    std::vector<int> arr52 = arrB;
    start2 = std::chrono::high_resolution_clock::now();
    quickSort(arr52, 0, arr52.size() - 1);
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "Sorted array (Quick Sort): ";

    std::cout << "Time taken by quick sort: " << elapsed2.count() << " seconds" << std::endl;

    // Heap Sort
    std::vector<int> arr62 = arrB;
    start2 = std::chrono::high_resolution_clock::now();
    heapSort(arr62);
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "Sorted array (Heap Sort): ";

    std::cout << "Time taken by heap sort: " << elapsed2.count() << " seconds"<<std::endl;

    std::cout << "Descending Array Test"<<std::endl;

    // Bubble Sort
    std::vector<int> arr13 = arrC;
    auto start3 = std::chrono::high_resolution_clock::now();
    bubbleSort(arr13);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed3 = end3 - start3;
    std::cout << "Sorted array (Bubble Sort): ";

    std::cout << "Time taken by bubble sort: " << elapsed3.count() << " seconds" << std::endl;

    // Insertion Sort
    std::vector<int> arr23 = arrC;
    start = std::chrono::high_resolution_clock::now();
    insertionSort(arr23);
    end3 = std::chrono::high_resolution_clock::now();
    elapsed3 = end3 - start3;
    std::cout << "Sorted array (Insertion Sort): ";

    std::cout << "Time taken by insertion sort: " << elapsed3.count() << " seconds" << std::endl;

    // Selection Sort
    std::vector<int> arr33 = arrC;
    start3 = std::chrono::high_resolution_clock::now();
    selectionSort(arr33);
    end3 = std::chrono::high_resolution_clock::now();
    elapsed3 = end3 - start3;
    std::cout << "Sorted array (Selection Sort): ";

    std::cout << "Time taken by selection sort: " << elapsed3.count() << " seconds" << std::endl;

    // Merge Sort
    std::vector<int> arr43 = arrC;
    start3 = std::chrono::high_resolution_clock::now();
    mergeSort(arr43, 0, arr43.size() - 1);
    end3 = std::chrono::high_resolution_clock::now();
    elapsed3 = end3 - start3;
    std::cout << "Sorted array (Merge Sort): ";

    std::cout << "Time taken by merge sort: " << elapsed3.count() << " seconds" << std::endl;

    // Quick Sort
    std::vector<int> arr53 = arrC;
    start3 = std::chrono::high_resolution_clock::now();
    quickSort(arr53, 0, arr53.size() - 1);
    end3 = std::chrono::high_resolution_clock::now();
    elapsed3 = end3 - start3;
    std::cout << "Sorted array (Quick Sort): ";

    std::cout << "Time taken by quick sort: " << elapsed3.count() << " seconds" << std::endl;

    // Heap Sort
    std::vector<int> arr63 = arrC;
    start3 = std::chrono::high_resolution_clock::now();
    heapSort(arr63);
    end3 = std::chrono::high_resolution_clock::now();
    elapsed3 = end3 - start3;
    std::cout << "Sorted array (Heap Sort): ";

    std::cout << "Time taken by heap sort: " << elapsed3.count() << " seconds";
}