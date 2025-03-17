#ifndef TESTCLIENT_H
#define TESTCLEINT_H

#include <string>
#include <trie.h>

using namespace std;

void Testclient(Trie* trie, string& key, vector<string> wordList, int numRuns);
bool Validation(vector<string> allWords, vector<string>& foundWords, string& key);

#endif