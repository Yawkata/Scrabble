#include <iostream>
#include "./Filip_header/CP.h"
#include "./Ivaylo_header/trie.h"

using namespace std;

int main() {
    /**/
    int* countSymbols = initDict();
    struct trieNode* root = getTrieFromDict("dict.txt", countSymbols);
    printTrie(root);

    cout << endl;

    for(int i = 0; i < NUM_VALID_SYMBOLS-3; i++) {
        if (countSymbols[i] != 0)
            cout << (char)('a'+i) << " -> " << countSymbols[i] << " (" << calcPoints(countSymbols, (char)('a'+i)) << ")" << endl;
    }

    cout << "Spaces -> " << countSymbols[symbolToIndex(' ')] << " (" << calcPoints(countSymbols, ' ') << ")" << endl;
    cout << "- -> " << countSymbols[symbolToIndex('-')] << " (" << calcPoints(countSymbols, '-') << ")" << endl;
    cout << "' -> " << countSymbols[symbolToIndex((char)39)] << " (" << calcPoints(countSymbols, (char)39) << ")" << endl;

    cout << "Count of guesses: " << countSymbols[NUM_VALID_SYMBOLS] << endl << endl;

    cout <<(trieSearch(root, "IVAN's home") ? "Found!" : "Not Found!") << endl;

    writeDict(countSymbols);
    cout << "Done!" << endl;
    /*
    int* countSymbolsInput = initDict();
    readDict(countSymbolsInput);

    for(int i = 0; i < NUM_VALID_SYMBOLS-3; i++) {
        if (countSymbolsInput[i] != 0)
            cout << (char)('a'+i) << " -> " << countSymbolsInput[i] << endl;
    }

    cout << "Spaces -> " << countSymbolsInput[symbolToIndex(' ')] << endl;
    cout << "- -> " << countSymbolsInput[symbolToIndex('-')] << endl;
    cout << "' -> " << countSymbolsInput[symbolToIndex((char)39)] << endl;

    cout << "Count of guesses: " << countSymbolsInput[NUM_VALID_SYMBOLS] << endl;
    */
}