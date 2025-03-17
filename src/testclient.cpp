#include "testclient.h"
#include <iostream>
#include "wortsuche.h"
#include <chrono>
#include <algorithm>
#include <unordered_set>

using namespace std;

void Testclient(Trie* trie, string& key, vector<string> wordList, int numRuns){
    cout << "Start testclient..." << endl;
    vector<string> foundWords;

    auto start = chrono::high_resolution_clock::now();
    
    for(int i=0; i<numRuns; ++i){
        foundWords = searchFinal(trie->root, key);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

    cout << "Found the following words: " << endl;
    for(string& word : foundWords){
       cout << word << ", ";
    }
    cout << endl << "The search took an average of " << duration.count()/numRuns << " microseconds (" << numRuns << " Runs)." << endl;
    cout << "Start Validation..." << endl;

    bool correct = Validation(wordList, foundWords, key);
    if(correct) cout << "Validation completed. Search was successful!" <<endl;
    else cout << "Validation error" << endl;

}


bool Validation(vector<string> allWords, vector<string>& foundWords, string& key){

    for(string& str : foundWords){
        if(str.rfind(key, 0) != 0){
            cout << "Not all words have correct Prefix!" << endl; 
            return false;
        }
    }


    unordered_set<string> allWordsSet(allWords.begin(), allWords.end());
    unordered_set<string> foundWordsSet(foundWords.begin(), foundWords.end());
    for(auto it = allWordsSet.begin(); it!= allWordsSet.end();){
        if(foundWordsSet.find(*it) != foundWordsSet.end()){
            it = allWordsSet.erase(it);
        }
        else ++it;
    }
    
    for(const string& word : allWordsSet){
        if(word.substr(0, key.size()) == key){
            cout << word;
            cout << "Not all words found! " << endl;
            return false;
        }
    }

    return true;
}