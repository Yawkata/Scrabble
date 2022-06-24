#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#define NUM_LETTERS 26

struct trieNode;

struct trieNode* initNode(char letter, bool terminal);

unsigned int letterToIndex(char letter);
bool trieInsert(struct trieNode* root, std::string word);
bool trieSearch(struct trieNode* root, std::string word);

struct trieNode* getTrieFromDict(std::string filename);

void printTrieRec(struct trieNode* node, std::string cur, int* count);
void printTrie(struct trieNode* root);

#endif