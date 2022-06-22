#include <iostream>
#include "./headers/Trie/trie.h"
#include "./headers/Trie/trie.cpp"

int main() {
    struct trieNode* root = getTrieFromDict("dict.txt");
    printTrie(root);
}