#include "CP.h"
#include "../Ivaylo_header/trie.h"
#include "../Ivaylo_header/trie.cpp"

#include <iostream>
#include <fstream>

int* initDict() {
    int* newCountSymbols = new int[NUM_VALID_SYMBOLS+1];

    for(int i = 0; i < NUM_VALID_SYMBOLS+1; i++)
        newCountSymbols[i] = 0;

    return newCountSymbols;
}

int calcPoints(int* countSymbols, char symbol) {
    int index = symbolToIndex(symbol);
    if (index == -1) return -1;
    return countSymbols[NUM_VALID_SYMBOLS] - countSymbols[index];
}

void writeDict(int* countLetters) {
    std::ofstream output(CL_FILE, std::ios::binary);
    output.write((char*)&countLetters, sizeof(countLetters));
    output.close();
}

int* readDict() {
    int* output = initDict();

    std::ifstream input(CL_FILE, std::ios::binary);
    input.read((char*)&output, sizeof(output));
    input.close();

    return output;
}