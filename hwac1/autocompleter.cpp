#include "Autocompleter.h"

// Constructor
Autocompleter::Autocompleter() {
    // Initialize the root
    root = nullptr;
}

// Inserts a string into the dictionary with a given frequency
void Autocompleter::insert(string x, int freq) {
    // Method body
}

// Returns the number of strings in the dictionary
int Autocompleter::size() {
    return size_recurse(root);
}

// Fills the vector with the top 3 completions
void Autocompleter::completions(string x, vector<string> &T) {
    // Method body
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

    //make new node if null/at the end
    
    //recurse through tree to find where it belongs

    //

    if(p == nullptr)
    {
        Node * temp = new Node(e);
        

    }

    if (e.freq <= p->e.freq)
    {
        insert_recurse(e,p->left);
    }
    else
    {
        insert_recurse(e,p->right);
    }
    
}

// Rebalances the AVL tree rooted at p
void Autocompleter::rebalance(Node* &p) {
    // Method body
}

// Performs a right rotation on the AVL tree rooted at p
void Autocompleter::right_rotate(Node* &p) {
    // Method body
}

// Performs a left rotation on the AVL tree rooted at p
void Autocompleter::left_rotate(Node* &p) {
    // Method body
}

// // Updates the height of a node
// void Autocompleter::update_height(Node*& p)
// {
//     if (p != nullptr)
//         p->height = 1 + max(height(p->left), height(p->right));
// }
