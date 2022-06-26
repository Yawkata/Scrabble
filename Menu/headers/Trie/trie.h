#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#define NUM_VALID_SYMBOLS 29 // букви + ' ' + '-' + '
#define HTL_VALUE 'a'-'A'  // HTL - higher to lower

struct trieNode;

struct trieNode* initNode(char symbol, bool terminal);

int symbolToIndex(char symbol);
char toLower(char symbol);

bool trieInsert(struct trieNode* root, int* countSymbols, std::string word);
bool trieSearch(struct trieNode* root, std::string word);

struct trieNode* getTrieFromDict(std::string filename, int* countSymbols);

void printTrieRec(struct trieNode* node, std::string cur, int* count);
void printTrie(struct trieNode* root);

#endif