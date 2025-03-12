#include <string>
#include <iostream>
#include <vector>
#define NUMBER_OF_LETTERS 26

using namespace std;

struct TrieNode {
    public: 
        char data;
        TrieNode* children[NUMBER_OF_LETTERS];
        bool EndOfWord;

        TrieNode() : EndOfWord(false) {
            for(int i=0; i<NUMBER_OF_LETTERS; ++i){
                children[i] = nullptr;
            }
        }
};

void insert(TrieNode* root, string& key){
    TrieNode* current = root;
    
    for (int i=0; i<key.length(); ++i){
        char c = key[i];
        if (current->children[c-'a'] == nullptr){
            TrieNode* newNode = new TrieNode();
            current->children[c-'a'] = newNode;
        }
        current = current->children[c-'a'];
        current->data = c;
    }
    current->EndOfWord = true;
}

bool search(TrieNode* root, string& key){
    TrieNode* current = root;
    vector<TrieNode*> FoundWords;

    if(key.length() == 4){
    for (int i=0; i<key.length(); ++i){
        char c = key[i];
        if (current->children[c-'a'] == nullptr) return false;
        current = current->children[c-'a'];
    }
    return current->EndOfWord;
    }
    
    else if(key.length() < 4){
        for (int i=0; i<key.length(); ++i){
            char c = key[i];
            if(current->children[c-'a'] == nullptr) return false;
            current = current->children[c-'a'];
        }
        for(char x = 'a'; x<='z'; x++){
            if(current->children[x-'a'] != nullptr) FoundWords.push_back(current->children[x-'a']);
        }
        cout << "Found Words: " << endl;
        for (TrieNode* word : FoundWords){
            cout << word->data << "_";
        }
    }
    return true;
}
