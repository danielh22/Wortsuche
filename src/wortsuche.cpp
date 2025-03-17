#include <iostream>
#include <thread>

#include "wortsuche.h"

using namespace std;

void searchHelper(TrieNode* root, vector<TrieNode*>& threadNode){
    vector<TrieNode*> localNodes;
    for(char x = 'A'; x<='Z'; x++){
        if(root->children[x-'A'] != nullptr){
            localNodes.push_back(root->children[x-'A']);
        }
    }
    threadNode.insert(threadNode.end(), localNodes.begin(), localNodes.end());
}

vector<string> searchWords(TrieNode* root, string& key){
    TrieNode* current = root;
    vector<string> FoundWords;
    vector<TrieNode*> Nodes;

    for(char c : key){
        if(current->children[c-'A'] == nullptr) return FoundWords;
        current = current->children[c-'A'];
    }
    if(current->endOfWord) FoundWords.push_back(current->data);

    unsigned int numThreads = std::thread::hardware_concurrency(); // Adjust thread count based on hardware
    vector<thread> threads;

    
    // Helper to distribute the work among threads
    auto threadHelper = [](TrieNode* node, vector<TrieNode*>& threadNode) {
        searchHelper(node, threadNode);
    };
    searchHelper(current, Nodes);

    vector<vector<TrieNode*>> ThreadNodes(numThreads);

    while(!Nodes.empty()){
        for(TrieNode* t : Nodes){
            if(t->endOfWord==true) FoundWords.push_back(t->data);
        }
            
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

        Nodes.clear();
        for(int i=0; i<numThreads; ++i){
            Nodes.insert(Nodes.end(), ThreadNodes[i].begin(), ThreadNodes[i].end());
            ThreadNodes[i].clear();
        }

        threads.clear();  // Leere die Threads-Liste für die nächste Runde

    }
    return FoundWords;
}