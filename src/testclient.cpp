#include "testclient.h"
#include <iostream>
#include "wortsuche.h"
#include <chrono>

using namespace std;

void Testclient(Trie* trie, string& key, int numRuns){
    cout << "Start testclient" << endl;
    vector<string> foundWords;

    auto start = chrono::high_resolution_clock::now();
    
    for(int i=0; i<=numRuns; ++i){
        foundWords = searchFinal(trie->root, key);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

    cout << "Found the following words: " << endl;
    for(string& word : foundWords){
       cout << word << ", ";
    }
    cout << endl << "The search took an average of " << duration.count()/numRuns << " microseconds (" << numRuns << " Runs)." << endl;

}