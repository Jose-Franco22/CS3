#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int binarySearch(vector<double> &A, double key, int start, int end) {

    while (start <= end) {
        int mid = (end + start) / 2;
        if (A[mid] == key) {
            return mid;
        } else if (A[mid] < key) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}


int fastFind(vector<double> &A, double key) {


    if (A[0] == key) {
        return 0;
    }

    int i = 1;
    while (i < A.size() && A[i] <= key) {
        i *= 2;
    }



    return binarySearch(A, key, i/2, i);
}


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
        
        queue<node *> x;
        x.push(r);


        while(x.empty() != true){

            node * curr = x.front();
            cout << curr->data << " ";
            x.pop();
            
            if(curr->left != nullptr){
                x.push(curr->left);
            }

            if(curr->right != nullptr){
                x.push(curr->right);
            }


        }

    };


int main() {
    vector<double> A = {1.41, 1.73, 2.58, 2.71, 3.14, 4.67, 5.89};


    cout << fastFind(A,5.89) << endl;

    levelOrderTraversal(buildTree(A, 0, 6));

}

