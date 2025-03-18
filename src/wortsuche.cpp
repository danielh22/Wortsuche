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

    //find the prefix-node here
    for(char c : key){
        if(current->children[c-'A'] == nullptr) return FoundWords;
        current = current->children[c-'A'];
    }
    if(current->endOfWord) FoundWords.push_back(current->data);  //check if prefix node is already a word.

    unsigned int numThreads = std::thread::hardware_concurrency(); // check how many threads possible
    vector<thread> threads;

    
    // Helper to distribute the work among threads
    auto threadHelper = [](TrieNode* node, vector<TrieNode*>& threadNode) {
        searchHelper(node, threadNode);
    };


    searchHelper(current, Nodes); //call search helper from prefix node
    //Nodes contains all nodes wich are children from prefix node

    vector<vector<TrieNode*>> ThreadNodes(numThreads); //One vector<TrieNode*> for each thread


    while(!Nodes.empty()){
        //check if any node from Nodes is end of a word
        for(TrieNode* t : Nodes){
            if(t->endOfWord==true) FoundWords.push_back(t->data);
        }
            
        unsigned int batchSize = Nodes.size() / numThreads + 1; // batchSize = How many nodes ech thread takes
        

        for (unsigned int i = 0; i < numThreads; i++) {
            auto begin = Nodes.begin() + i * batchSize; //start pointer on startnode for each thread

            //end pointer, points to  last Node in batch if this Node is stil in Nodes. Otherwise points to Nodes.end().
            auto end = (i + 1) * batchSize < Nodes.size() ? Nodes.begin() + (i + 1) * batchSize : Nodes.end();

            if (begin < end) {
                threads.push_back(thread([=, &ThreadNodes]() {      //create new thread and push it in thread-vector
                    for (auto node = begin; node != end; ++node) {
                        threadHelper(*node, ThreadNodes[i]);        //call  searchHelper() for each thread
                    }
                }));
            }
        }
        // wait for asynchron Tasks
        for (auto& t : threads) {
            t.join();
        }

        Nodes.clear();
        //combine vector from each thread to the Nodes vector.
        for(int i=0; i<numThreads; ++i){
            Nodes.insert(Nodes.end(), ThreadNodes[i].begin(), ThreadNodes[i].end());
            ThreadNodes[i].clear();
        }

        threads.clear();  // empty thread list for next round

    }
    return FoundWords;
}