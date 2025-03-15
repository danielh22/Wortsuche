#include <random>
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>

#include "wortsuche.h"

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

void generateWords(int length, const string& currentWord, vector<string>& wordList){
    if(currentWord.size() == length){
        wordList.push_back(currentWord);
        return;
    }

    for(char c='A'; c<='Z'; c++){
        generateWords(length, currentWord+c, wordList);
    }
}

vector<string> createWordListRecursive(int length){
    random_device gen;
    mt19937 g(gen());
    vector<string> wordList;

    generateWords(length, "", wordList);
    shuffle(wordList.begin(), wordList.end(), gen);

    return wordList;
}

void searchHelper(TrieNode* root, vector<TrieNode*>& threadNode){
    vector<TrieNode*> localNodes;
    for(char x = 'A'; x<='Z'; x++){
        if(root->children[x-'A'] != nullptr){
            localNodes.push_back(root->children[x-'A']);
        }
    }
    threadNode.insert(threadNode.end(), localNodes.begin(), localNodes.end());
}

vector<string> searchFinal(TrieNode* root, string& key){
    TrieNode* current = root;
    vector<string> FoundWords;
    vector<TrieNode*> Nodes;

    for(char c : key){
        if(current->children[c-'A'] == nullptr) return FoundWords;
        current = current->children[c-'A'];
    }
    if(current->EndOfWord) FoundWords.push_back(current->data);

    unsigned int numThreads = std::thread::hardware_concurrency(); // Adjust thread count based on hardware
    vector<thread> threads;

    
    // Helper to distribute the work among threads
    auto threadHelper = [](TrieNode* node, vector<TrieNode*>& threadNode) {
        searchHelper(node, threadNode);
    };
    searchHelper(current, Nodes);

    vector<vector<TrieNode*>> ThreadNodes(numThreads);

    while(!Nodes.empty()){
        unsigned int batchSize = Nodes.size() / numThreads + 1;
        
        for (unsigned int i = 0; i < numThreads; i++) {
            auto begin = Nodes.begin() + i * batchSize;
            auto end = (i + 1) * batchSize < Nodes.size() ? Nodes.begin() + (i + 1) * batchSize : Nodes.end();

            if (begin < end) {
                threads.push_back(thread([=, &ThreadNodes]() {
                    for (auto node = begin; node != end; ++node) {
                        threadHelper(*node, ThreadNodes[i]);
                    }
                }));
            }
        }
        // Warte auf alle asynchronen Tasks
        for (auto& t : threads) {
            t.join();
        }

        threads.clear();  // Leere die Threads-Liste für die nächste Runde
        Nodes.clear();
        for(int i=0; i<numThreads; ++i){
            Nodes.insert(Nodes.end(), ThreadNodes[i].begin(), ThreadNodes[i].end());
            ThreadNodes[i].clear();
        }
        for(TrieNode* t : Nodes){
            FoundWords.push_back(t->data);
        }
    }
    return FoundWords;
}





void searchHelperWithoutThreads(TrieNode* root, vector<TrieNode*>& Nodes, vector<string>& foundWords){
    vector<TrieNode*> localNodes;
    for(char x = 'A'; x<='Z'; x++){
        if(root->children[x-'A'] != nullptr){
            localNodes.push_back(root->children[x-'A']);
        }
    }
    Nodes.insert(Nodes.end(), localNodes.begin(), localNodes.end());
    for(TrieNode* t : localNodes){
        if(t->EndOfWord) foundWords.push_back(t->data);
    }
}


vector<string> searchFinalWithoutThreads(TrieNode* root, string& key){
    TrieNode* current = root;
    vector<string> FoundWords;
    vector<TrieNode*> Nodes;

    for(char c : key){
        if(current->children[c-'A'] == nullptr) return FoundWords;
        current = current->children[c-'A'];
    }
    if(current->EndOfWord) FoundWords.push_back(current->data);

    searchHelperWithoutThreads(current, Nodes, FoundWords);
    while(!Nodes.empty()){
        vector<TrieNode*> Intermediate_nodes = Nodes;
        Nodes.clear();

        for(TrieNode* inter : Intermediate_nodes){searchHelperWithoutThreads(inter, Nodes, FoundWords);}
    }
    return FoundWords;
}