#include <random>
#include <algorithm>

using namespace std;

void generateWords(int length, const string& currentWord, vector<string>& wordList){
    if(currentWord.size() == length){
        wordList.push_back(currentWord);
        return;
    }

    for(char c='A'; c<='Z'; c++){
        generateWords(length, currentWord+c, wordList);
    }
}

vector<string> createWordListRecursive(int length){
    random_device gen;
    mt19937 g(gen());
    vector<string> wordList;

    generateWords(length, "", wordList);
    shuffle(wordList.begin(), wordList.end(), gen);

    return wordList;
}