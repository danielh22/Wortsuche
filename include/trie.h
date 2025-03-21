#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

#define NUMBER_OF_LETTERS 26

struct TrieNode{
    public: 
        std::string data;
        TrieNode* children[NUMBER_OF_LETTERS];
        bool endOfWord;

        TrieNode();
};

struct Trie{
    public:
        TrieNode* root;

        void insert(std::string& key);
        Trie();
        ~Trie();
    
    private:
        void deleteTrie(TrieNode* node);    
};

#endif