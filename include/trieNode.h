#ifndef TRIENODE_H
#define TRIENODE_H

#include <string>
#include <vector>

#define NUMBER_OF_LETTERS 26

struct TrieNode{
    public: 
        std::string data;
        TrieNode* children[NUMBER_OF_LETTERS];
        bool EndOfWord;

        TrieNode();
};

#endif

void insert(TrieNode* root, std::string& key);
