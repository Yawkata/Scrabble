#include <iostream>
#include <fstream>
#include "CP.h"
#include "../Ivaylo_header/trie.h"


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

void writeDict(int* countSymbols) {
    std::ofstream output(CS_FILE, std::ios::binary);

    int count = 30;
    output.write((char*)&count, sizeof(count));

    for(int i = 0; i < count; i++)
        output.write((char*)&countSymbols[i], sizeof(countSymbols[i]));

    output.close();
}

void readDict(int* output) {
    std::ifstream input(CS_FILE, std::ios::binary);
    int count;
    input.read((char*)&count, sizeof(count));

    for(int i = 0; i < count; i++)
        input.read((char*)&output[i], sizeof(output[i]));

    input.close();
}