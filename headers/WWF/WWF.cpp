#include <iostream>
#include <fstream>
#include "WWF.h"
#include "../Trie/trie.h"
#include "../CP/CP.h"

void updateLoadFile(std::string filename) {
    std::fstream loadFile;
    loadFile.open(LOAD_FILE, std::ios::out);

    if(loadFile.is_open()){
        loadFile << filename << std::endl;
        loadFile.close();
    }else{
        std::cout << "Error" << std::endl;
    }
}

void deconstructTrieToFile(struct trieNode* root, FILE *fp) {
    if(!root) return;

    fwrite(root, sizeof(struct trieNode), 1, fp);

    for(int i = 0; i < NUM_VALID_SYMBOLS; i++) {
        if (root->children[i]) {
            deconstructTrieToFile(root->children[i],  fp);
        }
    }

    struct trieNode* marker = initNode(SYMBOL, false);
    fwrite(marker, sizeof(struct trieNode), 1, fp);
}

void updateCacheFile(struct trieNode* root) {
    FILE *fp = fopen(CACHE_FILE, "wb");

    if (fp == NULL)
    {
        std::cout << "Error while opening: " << CACHE_FILE << std::endl;
        return;
    }

    deconstructTrieToFile(root, fp);
    fclose(fp);
}

int constructTrieFromFile(struct trieNode*&root, FILE *fp) {
    struct trieNode node;
    if (!fread(&node, sizeof(struct trieNode), 1, fp) || node.symbol == SYMBOL)
        return 1;

    root = initNode(node.symbol, node.terminal);
    for (int i = 0; i < NUM_VALID_SYMBOLS; i++) {
        if(constructTrieFromFile(root->children[i], fp))
            break;
    }

    return 0;
}

struct trieNode* getTrieFromCacheFile() {
    struct trieNode* root;

    FILE *binFile = fopen(CACHE_FILE, "rb");
    constructTrieFromFile(root, binFile);
    fclose(binFile);

    return root;
}

int chooseFile(std::string dictFileName, std::string cacheFileName, std::string loadFileName) {
    std::string fileToLoad;

    std::fstream loadFile;
    loadFile.open(LOAD_FILE, std::ios::in);
    if(loadFile.is_open()) {
        getline(loadFile, fileToLoad);
        loadFile.close();
    }else {
        loadFile.open(LOAD_FILE, std::ios::out);
        std::cout << std::endl << "Tree will be loaded from the .txt file!" << std::endl;
        updateLoadFile(cacheFileName);
        loadFile.close();
        return 0;
    }


    if(fileToLoad == cacheFileName){
        std::cout << std::endl << "Tree will be loaded from the .bin file!" << std::endl;
        return 1;
    }

    std::cout << std::endl << "Tree will be loaded from the .txt file!" << std::endl;
    updateLoadFile(cacheFileName);
    return 0;
}

void loadTrie() {
    struct trieNode* trie;
    int* dict = initDict();

    if (chooseFile(DICTIONARY_FILE, CACHE_FILE, LOAD_FILE)) {
        trie = getTrieFromCacheFile();
    } else {
        trie = getTrieFromDict(DICTIONARY_FILE, dict);
        updateCacheFile(trie);
    }

    delete[] dict;
    printTrie(trie);
}

void addWordToDictionary(std::string word) {
    std::fstream dictFile;
    dictFile.open(DICTIONARY_FILE, std::ios::app);

    if(dictFile.is_open()){
        dictFile << std::endl <<word;
        dictFile.close();
    }else{
        std::cout << "Error" << std::endl;
    }

    updateLoadFile(DICTIONARY_FILE);
}
