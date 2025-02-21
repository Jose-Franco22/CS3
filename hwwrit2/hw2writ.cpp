#include <vector>
#include <iostream>
using namespace std;

int fastFind(vector<double> &A, double key) {
    int start = 0;
    int end = A.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (A[mid] == key) {
            return mid;
        }
        else if (A[mid] < key) {
            start = mid + 1;  
        }
        else {
            end = mid - 1;  
        }
    }
    
    return -1;  
}

//missing fastfind


class node{
    public:
    double data;
    node * left;
    node * right;
    };

    node* buildTree(vector<double> &A, int start, int end){
        if(end < start){
            return nullptr;
        }

        int mid = (start+end)/2;

        node * midnode = new node();
        midnode->data = A[mid];
        midnode->left = buildTree(A, start, mid-1);
        midnode->right = buildTree(A, mid+1, end);

        return midnode;
    };


    void levelOrderTraversal(node * r){
        if(r == nullptr){
            return;
        }
        
        cout << (r->data) << endl;

        levelOrderTraversal(r->left);
        levelOrderTraversal(r->right);
    };



int main() {
    vector<double> A = {1.0, 2.5, 3.3, 4.7, 5.9, 6.2, 7.8}; // Explicitly cast to double
    // }
    
    // // Search for the value 1 and print the result
    // cout << "Index of 1: " << fastFind(A, 1) << endl;

    // return 0;
    levelOrderTraversal(buildTree(A, 0, 6));
}

