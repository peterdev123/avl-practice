#include <iostream>
// #include "BubbleSort.h"
// #include "QuickSort.h"
// #include "InsertionSort.h"
// #include "MergeSort.h"
#include "ShellSort.h"
using namespace std;

int main() {
    // BubbleSort sorter;
    // InsertionSort sorter;
    // QuickSort sorter;
    ShellSort sorter;
    int array[] = {12, 2, 7, 5, 6, 1, 8};
    int size = sizeof(array) / sizeof(array[0]);

    // sorter.quickSort(array, 0, size - 1);
    sorter.sort(array, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}