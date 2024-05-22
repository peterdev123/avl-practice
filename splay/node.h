#include <algorithm>
using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        int leftHeight = (left != nullptr) ? left->height() : 0;
        int rightHeight = (right != nullptr) ? right->height() : 0;
        return 1 + max(leftHeight, rightHeight);
    }
};