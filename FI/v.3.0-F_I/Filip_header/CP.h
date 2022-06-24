#ifndef CP_H
#define CP_H

#define CL_FILE "countLetters.bin"  // countLetters file

int* initDict();

int calcPoints(int* countLetters, char letter);

void writeDict(int* countLetters);
int* readDict();

#endif