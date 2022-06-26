#ifndef WWF_H
#define WWF_H

#include <iostream>
#include "../Trie/trie.h"
#define DICTIONARY_FILE "dictionary.txt"
#define CACHE_FILE "cache.bin"
#define LOAD_FILE "last_modified.txt"
#define SYMBOL '@'

int chooseFile(std::string dictFileName, std::string cacheFileName, std::string loadFileName);
void updateLoadFile(std::string filename);
void updateCacheFile(struct trieNode* root);
void addWordToDictionary(STD::string word);

void deconstructTrieToFile(struct trieNode* root, FILE *fp);
int constructTrieFromFile(struct trieNode*&root, FILE *fp);
struct trieNode* getTrieFromCacheFile();
void loadTrie();

#endif