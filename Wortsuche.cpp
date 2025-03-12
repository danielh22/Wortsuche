#include <iostream>  // Ensure this is properly included
#include "Wortsuche.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;


int main(void) {

    random_device gen;
    mt19937 g(gen());

    vector<string> wordList;
    for (char one = 'a'; one<='z'; ++one){
        for(char two = 'a'; two<='z'; ++two){
            for(char three='a'; three<='z'; three++){
                for(char four='a'; four<='z'; four++){
                    string word = {one, two, three, four};
                    wordList.push_back(word);
                }
            }
        }
    }

    shuffle(wordList.begin(), wordList.end(), gen);
    
    int counter = 0;
    for(auto iterator=wordList.begin(); iterator!=wordList.end(); iterator++){
        //cout << *iterator << endl;
        counter++;
    }
    cout << "Total words: " << counter << endl;


    TrieNode* root = new TrieNode();
    for (string& s : wordList){
        insert(root, s);
    }
    vector<string> searchKeys = {"ball", "bati", "geek"};
    for(string& s : searchKeys){
        cout << "Searching " << s << endl;
        if(search(root, s)==true){
            cout << "FOUND" << endl;
        }
        else cout << "NOT FOUND" << endl;
    }
    return 0;
}