#include <iostream>
#include "../headers/trie.h"
#include "../headers/trie.cpp"

using namespace std;

int main() {
    // struct trieNode* root = initNode('a', false);
    // trieInsert(root, "duner");
    // trieInsert(root, "pizza");
    // trieInsert(root, "dunerger");
    // printTrie(root);

    struct trieNode* root = getTrieFromDict("dict.txt");
    printTrie(root);

    cout << endl;
    
    cout << (trieSearch(root, "duner") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "pizza") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "pp") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "d") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "fact") ? "Found!" : "Not Found!") << endl;
}