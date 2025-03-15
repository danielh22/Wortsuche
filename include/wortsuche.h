#ifndef WORTSUCHE_H
#define WORTSUCHE_H

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

void insert(TrieNode* root, std::string& key);

void generateWords(int length, const std::string& currentWord, std::vector<std::string>& wordList);

std::vector<std::string> createWordListRecursive(int length);

void searchHelper(TrieNode* root, std::vector<TrieNode*>& threadNode);

std::vector<std::string> searchFinal(TrieNode* root, std::string& key);


void searchHelperWithoutThreads(TrieNode* root, std::vector<TrieNode*>& Nodes, std::vector<std::string>& foundWords);


std::vector<std::string> searchFinalWithoutThreads(TrieNode* root, std::string& key);

#endif