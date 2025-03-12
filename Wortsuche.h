#include <string>
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
    }
    current->EndOfWord = true;
}

bool search(TrieNode* root, string& key){
    TrieNode* current = root;
    
    for (int i=0; i<key.length(); ++i){
        char c = key[i];
        if (current->children[c-'a'] == nullptr) return false;
        current = current->children[c-'a'];
    }
    return current->EndOfWord;
}
