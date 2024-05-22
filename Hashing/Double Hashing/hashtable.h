#include <cstdlib>
#include <iostream>
using namespace std;

class HashTable {
    char* table;
    int N;
    int count;
    
    // Use the ASCII code of the character
    int hash_code(char key) {
        // TODO
        return (int) key;
    }
    
    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509
    int compress(int code) {
        // TODO
        return ((59 * code + 17) % 509) % N;
    }
    
    // Using the knowledge that a hash function is composed of two portions
    int hashfn(char key) {
        return compress(hash_code(key));
    }
    
    public:
    HashTable(int N) {
        // TODO
        this->N = N;
        table = new char[N];
        count = 0;
    }
    
    int insert(char key) {
        // TODO
        if (count >= N) {return -1;}
        
        int collisions = 0;
        int index = hashfn(key);

        while (table[index] != '\0') {
            if (table[index] == key) {
                return -1;
            }
            index++; 
            collisions++;
            if (index == N) {
                index = 0;
            }
        }
        
        table[index] = key;
        count++;
        return collisions; 
    }
    
    int search(char key) {
        // TODO
        int check = 0;
        int check1 = 0;
        int index = hashfn(key);
        int surrIndex = index;

        while (table[index] != key && check < count) {
            if (table[index] != '\0') {
                check++;
            }
            index++;
            check1++;
            if (index == N) {
                index = 0;
            }
            if (surrIndex == index) {
                check1--;
                break;
            }
        }

        if (table[index] == key) {
            return check1;
        }
        return (check1 + 1) * -1;
    }
    
    int remove(char key) {
        // TODO
        bool found = false;

        int check = 0;
        int check1 = 0;
        int index = hashfn(key);

        while (table[index] != key && check < count) {
            if (table[index] != '\0') {
                check++;
            }
            check1++;
            index++;
            if (index == N) {
                index = 0;
            }
        }

        if (table[index] == key) {
            table[index] = '\0';
            count--;
            found = true;
        }

        if (!found) {
            return -1;
        }
        return check1;
    }
    
    void print() {
      for (int i = 0; i < N; i++) {
        cout << i << "\t";
      }
      cout << "\n";
      for (int i = 0; i < N; i++) {
        cout << table[i] << "\t";
      }
      cout << "\n";
    }
};