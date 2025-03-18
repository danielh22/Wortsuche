#ifndef WORTLISTE_H
#define WORTLISTE_H

#include <string>
#include <vector>

using namespace std;

void createWord(int length, const std::string& currentWord, std::vector<std::string>& wordList);

std::vector<std::string> createWordList(int wordlength);

#endif