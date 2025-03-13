#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

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

vector<string> createWordList(){
    random_device gen;
    mt19937 g(gen());
    vector<string> wordList;


    for (char one = 'A'; one<='Z'; ++one){
        for(char two = 'A'; two<='Z'; ++two){
            for(char three='A'; three<='Z'; three++){
                for(char four='A'; four<='Z'; four++){
                    string word = {one, two, three, four};
                    wordList.push_back(word);
                }
            }
        }
    }
    shuffle(wordList.begin(), wordList.end(), gen);
    return wordList;
}



bool search_withoutRec(TrieNode* root, string& key){
    TrieNode* current = root;
    TrieNode* keyRoot = nullptr;
    TrieNode* keyRoot2 = nullptr;
    TrieNode* keyRoot3 = nullptr;
    TrieNode* keyRoot4 = nullptr;
    vector<TrieNode*> FoundWords;

    for(char c : key){
        if(current->children[c-'A'] == nullptr) return false;
        current = current->children[c-'A'];
    }
    keyRoot = current;
    if(keyRoot->EndOfWord) FoundWords.push_back(keyRoot);
    for(char x = 'A'; x<='Z'; x++){
        if(keyRoot->children[x-'A'] != nullptr){
            keyRoot2 = keyRoot->children[x-'A'];
            if(keyRoot2->EndOfWord) FoundWords.push_back(keyRoot2);
            for(char y = 'A'; y<='Z'; y++){
                if(keyRoot2->children[y-'A'] != nullptr){
                    keyRoot3 = keyRoot2->children[y-'A'];
                    if(keyRoot3->EndOfWord) FoundWords.push_back(keyRoot3);
                    for(char z = 'A'; z<='Z'; z++){
                        if(keyRoot3->children[z-'A'] != nullptr){
                            keyRoot4 = keyRoot3->children[z-'A'];
                            if(keyRoot4->EndOfWord) FoundWords.push_back(keyRoot4);
                        }
                    }
                }   
            }   
        }
    }
    cout << "Found Words: " << endl;
    for (TrieNode* word : FoundWords){
        cout << word->data << " & ";
    }
    return true;
}

void searchWordsRecursive(TrieNode* root, vector<TrieNode*>& FoundTrieNodes, string currentPrefix=""){
    if(root==nullptr) return;

    if(root->EndOfWord == true){
        FoundTrieNodes.push_back(root);
    }

    for(char c='A'; c<='Z'; c++){
        int index = c-'A';
        if(root->children[index] != nullptr){
            searchWordsRecursive(root->children[index], FoundTrieNodes, currentPrefix+c);
        }
    }
}

vector<string> searchPrefixRecursive(TrieNode* root, string currentPrefix=""){
    vector<string> foundWords;
    vector<TrieNode*> FoundTrieNodes;

    for(char c : currentPrefix){
        if(root->children[c-'A'] == nullptr) return foundWords;
        root = root->children[c-'A'];
    }
    searchWordsRecursive(root, FoundTrieNodes, currentPrefix);
    for (TrieNode* word : FoundTrieNodes){
        foundWords.push_back(word->data);
    }
    return foundWords;
}