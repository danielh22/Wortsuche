#include <iostream>  // Ensure this is properly included
#include "Wortsuche.h"
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void Testclient(TrieNode* root, string& key);

int main(void) {

    //vector<string> wordList = createWordList();
    vector<string> wordList = createWordListRecursive(4);

    /*cout << "all words: " << endl; 
    for(string& word : wordList){
        cout << word << " ";
    }*/

    TrieNode* root = new TrieNode();
 
    for (string& s : wordList){
        insert(root, s);
    }

    string searchKey = "XS";

    Testclient(root, searchKey);

    //vector<string> foundWords = searchFinal(root, searchKey);

    //for(string& word : foundWords){
    //    cout << word << " ";
    //}
}



void Testclient(TrieNode* root, string& key){
    auto start = chrono::high_resolution_clock::now();

    vector<string> foundWords = searchFinal(root, key);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

    
    cout << "Found the following words: " << endl;
    for(string& word : foundWords){
        cout << word << ", ";
    }
    cout << endl << "The search took " << duration.count() << " microseconds." << endl;


}