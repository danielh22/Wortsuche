#include <iostream> 
#include <chrono>
#include "wortsuche.h"

using namespace std;

void Testclient(TrieNode* root, string& key, int numRuns);

int main(void) {

    vector<string> wordList = createWordListRecursive(4);

    /*cout << "all words: " << endl; 
    for(string& word : wordList){
        cout << word << " ";
    }*/

    TrieNode* root = new TrieNode();
 
    for (string& s : wordList){
        insert(root, s);
    }

    string searchKey = "F";

    Testclient(root, searchKey, 50);

    //vector<string> foundWords = searchFinal(root, searchKey);

    //for(string& word : foundWords){
    //    cout << word << " ";
    //}
}



void Testclient(TrieNode* root, string& key, int numRuns){
    cout << "Start testclient" << endl;
    auto start1 = chrono::high_resolution_clock::now();
    vector<string> foundWords;

    for(int i=0; i<=numRuns; ++i){
        foundWords = searchFinalWithoutThreads(root, key);
    }
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1-start1);

    auto start2 = chrono::high_resolution_clock::now();

    for(int i=0; i<=numRuns; ++i){
        foundWords = searchFinal(root, key);
    }
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2-start2);
    //cout << "Found the following words: " << endl;
    //for(string& word : foundWords){
    //   cout << word << ", ";
    //}
    cout << endl << "The search without Threading took an average of " << duration1.count()/numRuns << " microseconds (" << numRuns << " Runs)." << endl;
    cout << "The search with Threading took an average of " << duration2.count()/numRuns << " microseconds (" << numRuns << " Runs)." << endl;


}