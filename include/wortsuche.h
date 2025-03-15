#ifndef WORTSUCHE_H
#define WORTSUCHE_H

#include "trieNode.h"

void searchHelper(TrieNode* root, std::vector<TrieNode*>& threadNode);

std::vector<std::string> searchFinal(TrieNode* root, std::string& key);

#endif