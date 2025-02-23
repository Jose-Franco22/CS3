#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int binarySearch(vector<char> &A, char key, int start, int end) {

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

int fastFind(vector<char> &A, char key){
    int i=0;

    if(A[0] == key){
        return 0;
    }

    while(A[i] =< key && i < A.size()){
        i = i * 2;
    }

    return binarySearch(A,key,i/2,i);

}


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
    vector<char> A = {'A', 'B', 'C', 'D', 'E', 'F','G'}; 

    fastFind(A,2);

    //levelOrderTraversal(buildTree(A, 0, 6));
}

