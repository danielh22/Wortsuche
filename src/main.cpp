#include <iostream> 
#include <chrono>
#include "wortsuche.h"
#include "wortliste.h"

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

    string searchKey = "TF";

    Testclient(root, searchKey, 20);

    //vector<string> foundWords = searchFinal(root, searchKey);

    //for(string& word : foundWords){
    //    cout << word << " ";
    //}
}



void Testclient(TrieNode* root, string& key, int numRuns){
    cout << "Start testclient" << endl;
    auto start = chrono::high_resolution_clock::now();
    vector<string> foundWords;

    for(int i=0; i<=numRuns; ++i){
        foundWords = searchFinal(root, key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

    cout << "Found the following words: " << endl;
    for(string& word : foundWords){
       cout << word << ", ";
    }
    cout << endl << "The search took an average of " << duration.count()/numRuns << " microseconds (" << numRuns << " Runs)." << endl;


}