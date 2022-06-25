#ifndef CP_H
#define CP_H

#define CS_FILE "countSymbols.bin"  // countSymbols file

int* initDict();

int calcPoints(int* countSymbols, char symbol);

void writeDict(int* countSymbols);
void readDict();

#endif