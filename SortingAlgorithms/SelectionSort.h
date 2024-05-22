#include <iostream>
#include "Sorting.h"
using namespace std;

class SelectionSort : Sorting{
    
    public:
    SelectionSort() {
        
    }

    int* sort(int arr[], int n) {
        for (int i = 0; i < n - 1; ++i) {
            // Find the minimum element in the unsorted part of the array
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            // Swap the found minimum element with the first element of the unsorted part
            swap(arr[minIndex], arr[i]);
        }
        return arr;
    }
};