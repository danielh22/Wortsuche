#include <iostream>  // Ensure this is properly included
#include "Wortsuche.h"
#include <string>
#include <vector>

using namespace std;

int main(void) {

    vector<string> wordList = createWordList();

    TrieNode* root = new TrieNode();
 
    for (string& s : wordList){
        insert(root, s);
    }

    string searchKey = "BAR";

    vector<string> foundWords = searchPrefixRecursive(root, searchKey);
    //vector<string> foundWords = searchPrefixNoRecursion(root, searchKey);

    for(string& word : foundWords){
        cout << word << " ";
    }
}