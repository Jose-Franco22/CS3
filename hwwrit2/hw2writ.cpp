#include <vector>
#include <iostream>
using namespace std;

int fastFind(vector<double> &A, double key) {
    int start = 0;
    int end = A.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (A[mid] == key) {
            return mid;  // Key found, return index
        }
        else if (A[mid] < key) {
            start = mid + 1;  // Move start to mid + 1
        }
        else {
            end = mid - 1;  // Move end to mid - 1
        }
    }
    
    return -1;  // Key not found, return -1
}

int main() {
    vector<double> A;

    // Populate the vector A with values from 0 to 98
    for (int i = 0; i < 99; i++) {
        A.push_back(static_cast<double>(i));  // Explicitly cast to double
    }
    
    // Search for the value 1 and print the result
    cout << "Index of 1: " << fastFind(A, 1) << endl;

    return 0;
}
