#include "trie.h"
#include <iostream>

using namespace std;

TrieNode::TrieNode() : EndOfWord(false) {
    for(int i=0; i<NUMBER_OF_LETTERS; ++i){
        children[i] = nullptr;
    }
}

Trie::Trie(){
    this->root = new TrieNode;
}

Trie::~Trie(){
    deleteTrie(root);
    cout << "Trie deleted" << endl;
}

void Trie::deleteTrie(TrieNode* node) {
    if (node == nullptr) return; // Base case for recursion
    
    // Recursively delete all child nodes
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
            deleteTrie(node->children[i]); // Recursive delete
        }
    }
    
    delete node; // Delete the current node after its children are deleted
}

void Trie::insert(string& key){
    TrieNode* current = this->root;
    string parent_data;
    
    for (int i=0; i<key.length(); ++i){
        char c = key[i];
        if (current->children[c-'A'] == nullptr){
            TrieNode* newNode = new TrieNode();
            current->children[c-'A'] = newNode;
        }
        current = current->children[c-'A'];
        current->data = parent_data + c;
        parent_data = parent_data + c;
    }
    current->EndOfWord = true;
}