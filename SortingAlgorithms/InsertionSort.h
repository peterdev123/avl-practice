#include <iostream>
using namespace std;

class InsertionSort : Sorting{
    
    public:
    InsertionSort() {
        
    }

    int* sort(int* array, int size) {
        int i, key, j;
        for (int i = 1; i < size; i++) {
            key = array[i];
            j = i - 1;

            while(j >= 0 && key < array[j]) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
        return array;
    }
};