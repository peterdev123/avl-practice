#include <iostream>
using namespace std;

class QuickSort{
    public:
    QuickSort() {}

    int partition(int arr[], int start, int end) {
        int pivot = arr[end];
        int pivotIndex = start;

        for (int i = start; i < end; ++i) {
            if(arr[i] <= pivot) {
                swap(arr[i], arr[pivotIndex]);
                pivotIndex++;
            }
        }

        swap(arr[pivotIndex], arr[end]);
        return pivotIndex;
    }

    void quickSort(int arr[], int start, int end) {
        if (start >= end) {
            return;
        }

        int p = partition(arr, start, end);
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
};