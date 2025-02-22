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
    char data;
    node * left;
    node * right;
    };

    node* buildTree(vector<char> &A, int start, int end){
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
        
        levelOrderTraversal(r->left);
        cout << (r->data) << endl;
        levelOrderTraversal(r->right);
    };


int main() {
    vector<char> A = {'A', 'B', 'C', 'D', 'E', 'F'}; 

    levelOrderTraversal(buildTree(A, 0, 5));
}

