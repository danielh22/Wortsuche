#include "wortliste.h"
#include "testclient.h"
#include "wortsuche.h"
#include <iostream>

using namespace std;


int main(void) {

    vector<string> wordList = createWordListRecursive(4);

    // cout << "all words: " << endl; 
    // for(string& word : wordList){
    //     cout << word << " ";
    // }

    Trie* trie = new Trie();
 
    for (string& s : wordList){
        trie->insert(s);
    }

    string searchKey = "VEC";

    Testclient(trie, searchKey, wordList, 20);

    // vector<string> foundWords = searchFinal(trie->root, searchKey);

    // for(string& word : foundWords){
    //     cout << word << " ";
    // }
}