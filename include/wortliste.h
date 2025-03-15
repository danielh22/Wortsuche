#ifndef WORTLISTE_H
#define WORTLISTE_H

#include <string>
#include <vector>

using namespace std;

void generateWords(int length, const std::string& currentWord, std::vector<std::string>& wordList);

std::vector<std::string> createWordListRecursive(int length);

#endif