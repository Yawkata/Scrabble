#include "trie.h"
#include <iostream>
#include <fstream>

struct trieNode {
    char symbol;
    bool terminal;
    struct trieNode* children[NUM_VALID_SYMBOLS];  // [abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -']
};

struct trieNode* initNode(char symbol, bool terminal) {
    struct trieNode* node = new trieNode;

    node->symbol = symbol;
    node->terminal = terminal;

    for(int i = 0; i < NUM_VALID_SYMBOLS; i++)
        node->children[i] = nullptr;

    return node;
}

int symbolToIndex(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return symbol - 'a';
    else if (symbol >= 'A' && symbol <= 'Z') return symbol - 'A';
    else if (symbol == ' ') return NUM_VALID_SYMBOLS - 3;
    else if (symbol == '-') return NUM_VALID_SYMBOLS - 2;
    else if (symbol == 39) return NUM_VALID_SYMBOLS - 1;  // 39 => ' code
    return -1;
}

char toLower(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z') return symbol + HTL_VALUE;
    return symbol;
}

bool trieInsert(struct trieNode* root, int* countSymbols, std::string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;
    bool smthAdded = false;

    bool passedLetters[NUM_VALID_SYMBOLS];
    for(int i = 0; i < NUM_VALID_SYMBOLS; i++) passedLetters[i] = false;

    for(int i = 0; i < word.size(); i++) {
        int symbolIndex = symbolToIndex(word[i]);
        if (symbolIndex == -1) return false;

        if (!passedLetters[symbolIndex]) {
            countSymbols[symbolIndex]++;
            passedLetters[symbolIndex] = true;
        }

        if (cur->children[symbolIndex] == NULL) {
            cur->children[symbolIndex] = initNode(toLower(word[i]), (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[symbolIndex];
    }

    countSymbols[NUM_VALID_SYMBOLS]++;
    return smthAdded;
}

bool trieSearch(struct trieNode* root, std::string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;

    for(int i = 0; i < word.size(); i++) {
        int symbolIndex = symbolToIndex(word[i]);
        if (symbolIndex == -1) return false;

        if (cur->children[symbolIndex] != nullptr) {
            cur = cur->children[symbolIndex];
        } else return false;
    }

    return (cur->terminal == true);
}

struct trieNode* getTrieFromDict(std::string filename, int* countSymbols) {
    if (filename.empty()) return nullptr;
    struct trieNode* root = initNode('#', false);

    std::ifstream dictionary(filename);

    std::string line;
    while(std::getline(dictionary, line))
        trieInsert(root, countSymbols, line);

    return root;
}

void printTrieRec(struct trieNode* node, std::string cur, int* count) {
    if (node->terminal) {
        std::cout << "Guess: " << cur << std::endl;
        (*count)++;
    }

    for (struct trieNode* child : node->children) {
        if (child != NULL) {
            printTrieRec(child, cur+child->symbol, count);
        }
    }
}

void printTrie(struct trieNode* root) {
    if (!root) {
        std::cout << "Empty Trie!" << std::endl;
        return;
    }

    int* count = new int;
    *(count) = 0;

    for (struct trieNode* node : root->children) {
        if (node != NULL) {
            std::string cur = "";
            cur.push_back(node->symbol);
            printTrieRec(node, cur, count);
        }
    }

    std::cout << "Number of guesses: " << *count << std::endl;
    delete count;
}