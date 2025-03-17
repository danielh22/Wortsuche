#ifndef WORTSUCHE_H
#define WORTSUCHE_H

#include "trie.h"

void searchHelper(TrieNode* root, std::vector<TrieNode*>& threadNode);

std::vector<std::string> searchWords(TrieNode* root, std::string& key);

#endif