#include "Autocompleter.h"

// Constructor
Autocompleter::Autocompleter() {
    // Initialize the root
    root = nullptr;
}

// Inserts a string into the dictionary with a given frequency
void Autocompleter::insert(string x, int freq) {
    Entry e;
    e.freq = freq;
    e.s = x;
    
    insert_recurse(e,root);
}

// Returns the number of strings in the dictionary
int Autocompleter::size() {
    return size_recurse(root);
}

// Fills the vector with the top 3 completions
void Autocompleter::completions(string x, vector<string> &T) {
    completions_recurse(x,root,T);
}







// static int Autocompleter::height(Node* p)
// {
// 	if (p == nullptr)
// 		return -1;
// 	return p->height;
// }

// Returns the size of the binary tree rooted at p
int Autocompleter::size_recurse(Node* p) {
    if(p == nullptr){
        return 0;
    }
    return 1 + size_recurse(p->left) + size_recurse(p->right);
}

// Fills C with the completions of x in the BST rooted at p
void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C) {
    // Method body
}

// Inserts an Entry into an AVL tree rooted at p
void Autocompleter::insert_recurse(Entry e, Node* &p) {
    if(p == nullptr){
        p = new Node(e);
    }

    else{
        if (e.freq < p->e.freq)
        {
            insert_recurse(e,p->left); 
        }
        else
        {
            insert_recurse(e,p->right);
        }

        update_height(p);
        rebalance(p);

    }
    
}

// Rebalances the AVL tree rooted at p
void Autocompleter::rebalance(Node* &p) {
    // Method body
}

// Performs a right rotation on the AVL tree rooted at p
void Autocompleter::right_rotate(Node* &p) {
    node* A = p;
    node* B = p->left;
    node* BR = B->right;

    p = B;
    B->right = A;
    A->left = BR;

    update_height(A);
    update_height(B);

}

// Performs a left rotation on the AVL tree rooted at p
void Autocompleter::left_rotate(Node* &p) {
    node* A = p;
    node* B = p->right;
    node* BL = B->left;

    p = B;
    B->left = A;
    A->right = BL;

    update_height(A);
    update_height(B);
}

// // Updates the height of a node
// void Autocompleter::update_height(Node*& p)
// {
//     if (p != nullptr)
//         p->height = 1 + max(height(p->left), height(p->right));
// }
