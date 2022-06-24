#include <iostream>
#include "./Filip_header/CP.h"
#include "./Filip_header/CP.cpp"
// #include "./Ivaylo_header/trie.h"
// #include "./Ivaylo_header/trie.cpp"

using namespace std;

int main() {
    int* countSymbols = initDict();
    struct trieNode* root = getTrieFromDict("dict.txt", countSymbols);
    printTrie(root);

    cout << endl;

    for(int i = 0; i < NUM_VALID_SYMBOLS-3; i++) {
        cout << (char)('a'+i) << " -> " << countSymbols[i] << endl;
    }

    cout << "Count of guesses: " << countSymbols[NUM_VALID_SYMBOLS] << endl;
}