#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate N random numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> numbers;
    srand(time(0));
    for (int i = 0; i < N; i++) {
        numbers.push_back(rand() % 1000);  // Random number between 0-999
    }
    return numbers;
}

// Binary Search
int binarySearch(vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Interpolation Search
int interpolationSearch(vector<int>& arr, int N, int target) {
    int low = 0, high = N - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int N = arr.size();
    for (int i = 0; i < N - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < N; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Merge Sort Helper Function
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort Function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Measure Execution Time
void measureTime(void (*sortFunction)(vector<int>&), vector<int>& arr, string sortName) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " took " << duration.count() << " microseconds." << endl;
}

int main() {
    int N, target;
    cout << "Enter number of elements: ";
    cin >> N;
    
    vector<int> numbers = generateRandomNumbers(N);
    vector<int> sortedNumbers = numbers; 

    // Sorting the numbers
    mergeSort(sortedNumbers, 0, N - 1);

    // Search Operations
    cout << "Enter number to search: ";
    cin >> target;
    
    int binaryResult = binarySearch(sortedNumbers, 0, N - 1, target);
    cout << (binaryResult != -1 ? "Found using Binary Search" : "Not found using Binary Search") << endl;
    
    int interpolationResult = interpolationSearch(sortedNumbers, N, target);
    cout << (interpolationResult != -1 ? "Found using Interpolation Search" : "Not found using Interpolation Search") << endl;

    // Sorting Performance
    vector<int> selectionSortNumbers = numbers;
    measureTime(selectionSort, selectionSortNumbers, "Selection Sort");

    vector<int> mergeSortNumbers = numbers;
    measureTime([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, mergeSortNumbers, "Merge Sort");

    return 0;
}
