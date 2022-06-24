#include <iostream>
#include "../headers/header-v.7.0/trie.h"
#include "../headers/header-v.7.0/trie.cpp"

using namespace std;

int main() {
    struct trieNode* root = getTrieFromDict("dict.txt");
    printTrie(root);
}