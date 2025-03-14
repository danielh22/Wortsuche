#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <future>

#define NUMBER_OF_LETTERS 26

using namespace std;

struct TrieNode{
    public: 
        string data;
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

void searchHelper(TrieNode* root, vector<TrieNode*>& Nodes, vector<string>& foundWords, mutex& mtx){
    vector<TrieNode*> localNodes;
    for(char x = 'A'; x<='Z'; x++){
        if(root->children[x-'A'] != nullptr){
            localNodes.push_back(root->children[x-'A']);
        }
    }
    lock_guard<mutex> lock(mtx);
    Nodes.insert(Nodes.end(), localNodes.begin(), localNodes.end());
    for(TrieNode* t : localNodes){
        if(t->EndOfWord) foundWords.push_back(t->data);
    }
}

vector<string> searchFinal(TrieNode* root, string& key){
    TrieNode* current = root;
    vector<string> FoundWords;
    vector<TrieNode*> Nodes;
    mutex mtx;

    for(char c : key){
        if(current->children[c-'A'] == nullptr) return FoundWords;
        current = current->children[c-'A'];
    }
    if(current->EndOfWord) FoundWords.push_back(current->data);

    unsigned int numThreads = std::thread::hardware_concurrency(); // Adjust thread count based on hardware
    vector<thread> threads;

    
    // Helper to distribute the work among threads
    auto threadHelper = [&mtx, &FoundWords, &Nodes](TrieNode* node) {
        searchHelper(node, Nodes, FoundWords, mtx);
    };

    searchHelper(current, Nodes, FoundWords, mtx);
    while(!Nodes.empty()){
        vector<TrieNode*> Intermediate_nodes = Nodes;
        Nodes.clear();
        unsigned int batchSize = Intermediate_nodes.size() / numThreads + 1;

        for (unsigned int i = 0; i < numThreads; i++) {
            auto begin = Intermediate_nodes.begin() + i * batchSize;
            auto end = (i + 1) * batchSize < Intermediate_nodes.size() ? Intermediate_nodes.begin() + (i + 1) * batchSize : Intermediate_nodes.end();

            if (begin < end) {
                threads.push_back(thread([=]() {
                    for (auto node = begin; node != end; ++node) {
                        threadHelper(*node);
                    }
                }));
            }
        }
        // Warte auf alle asynchronen Tasks
        for (auto& t : threads) {
            t.join();
        }
        
        threads.clear();  // Leere die Futures-Liste für die nächste Runde
    }
    return FoundWords;
}