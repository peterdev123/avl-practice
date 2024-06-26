#include <iostream>
#include "Sorting.h"
using namespace std;

class BubbleSort : Sorting{
    
    public:
    BubbleSort() {
        cout << "BubbleSort() constructor called" << endl;
    }

    int* sort(int* array, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    swap(array[j], array[j + 1]);
                }
            }
        }
        return array;
    }
};