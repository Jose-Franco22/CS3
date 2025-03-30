#include "autocompleter.h"

Autocompleter::Autocompleter() {
    root = new Node();
    count = 0;
}

void Autocompleter::insert(string x, int freq) {
    Node* cur = root;

    for(int i = 0; i < x.length(); i++){
        int index = x[i];
        if(cur->children[index] == nullptr){
            cur->children[index] = new Node(); 
        }
        cur = cur->children[index];  
    }
    
    if(cur->marked){
        return;
    }

    cur->marked = true;
    count++;

    Entry e = {x, freq};

    vector<Node*> chars;
    chars.push_back(root);
    
    for(int i = 0; i < x.size(); i++){
        int index = x[i]; 
        chars.push_back(chars.back()->children[index]); 
    }

    for(int i = 0; i < chars.size(); i++){
        Node* node = chars[i];
    
        int val = 0;
        while(val < node->top.size() && (e.freq < node->top[val].freq || (e.freq == node->top[val].freq && e.s > node->top[val].s) ) ) {
            val++;
        }

        if(val < 3){
            node->top.insert(node->top.begin() + val, e);
        }
    
        if(node->top.size() > 3){
            node->top.resize(3);
        }
    }
}

int Autocompleter::size() {
    return count;
}

void Autocompleter::completions(string x, vector<string>& T) {
    T.clear();
    Node* cur = root;
        
    for(int i = 0; i < x.size(); i++){
        char c = x[i];
        int index = c;

        if(cur->children[index] == nullptr){
            return;
        }

        cur = cur->children[index];
    }
        
    for(int i = 0; i < cur->top.size(); i++){
        T.push_back(cur->top[i].s);
    }
}
    

