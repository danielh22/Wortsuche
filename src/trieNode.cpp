#include "trieNode.h"

using namespace std;

TrieNode::TrieNode() : EndOfWord(false) {
    for(int i=0; i<NUMBER_OF_LETTERS; ++i){
        children[i] = nullptr;
    }
}


void insert(TrieNode* root, string& key){
    TrieNode* current = root;
    string parent_data;
    
    for (int i=0; i<key.length(); ++i){
        char c = key[i];
        if (current->children[c-'A'] == nullptr){
            TrieNode* newNode = new TrieNode();
            current->children[c-'A'] = newNode;
        }
        current = current->children[c-'A'];
        string inter(1,c);
        current->data = parent_data + c;
        parent_data = parent_data + c;
    }
    current->EndOfWord = true;
}