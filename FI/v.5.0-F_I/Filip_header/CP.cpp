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
    FILE* f = fopen(CS_FILE, "wb");

    if(!f) {
        std::cout << "Error opening file to write!" << std::endl;
        return;
    }

    fwrite(countSymbols, sizeof(int), NUM_VALID_SYMBOLS+1, f);

    fclose(f);
}

void readDict(int* output) {
    FILE* f = fopen(CS_FILE, "rb");

    if(!f) {
        std::cout << "Error opening file to read!" << std::endl;
        return;
    }

    fread(output, sizeof(int), NUM_VALID_SYMBOLS+1, f);

    fclose(f);
}