#include <random>
#include <algorithm>

using namespace std;

void createWord(int length, const string& currentWord, vector<string>& wordList){
    if(currentWord.size() == length){
        wordList.push_back(currentWord);
        return;
    }

    for(char c='A'; c<='Z'; c++){
        createWord(length, currentWord+c, wordList);
    }
}

vector<string> createWordListRecursive(int length){
    random_device gen;
    mt19937 g(gen());
    vector<string> wordList;

    createWord(length, "", wordList);
    shuffle(wordList.begin(), wordList.end(), gen);

    return wordList;
}