#include <iostream>  // Ensure this is properly included
#include "Wortsuche.h"
#include <string>
#include <vector>
#include <chrono>

using namespace std;

void Testclient(TrieNode* root, string& key, vector<string>& expectedResult);

int main(void) {

    vector<string> wordList = createWordList();
    /*cout << "all words: " << endl; 
    for(string& word : wordList){
        cout << word << " ";
    }*/
    
    TrieNode* root = new TrieNode();
 
    for (string& s : wordList){
        insert(root, s);
    }

    string searchKey = "R";
    vector<string> expectedResults = {"AFGA", "AFGB"};

    Testclient(root, searchKey, expectedResults);

    //vector<string> foundWords = searchPrefixRecursive(root, searchKey);
    //vector<string> foundWords = searchFinal(root, searchKey);

    //for(string& word : foundWords){
    //    cout << word << " ";
    //}
}



void Testclient(TrieNode* root, string& key, vector<string>& expectedResult){
    auto start = chrono::high_resolution_clock::now();

    vector<string> foundWords = searchFinal(root, key);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end-start);

    
    cout << "Found the following words in " << duration.count() << " nanoseconds: " << endl;
    //for(string& word : foundWords){
    //    cout << word << " ";
    //}


}