#include <iostream>
#include <fstream>

using namespace std;

struct trie{
    char letter;
    int wordEnding;
    struct trie* next[30];
};

struct trie* initNode(char newLetter, int wordEnding){
    struct trie* newNode = new struct trie;

    newNode->letter = newLetter;

    newNode->wordEnding = wordEnding;

    for(int i = 0; i < 30; i++)
        newNode->next[i] = nullptr;

    return newNode;
}

int* initDic(){
    int* newCountLetters = new int[30];

    for(int i = 0; i < 30; i++)
        newCountLetters[i] = 0;

    return newCountLetters;
};

int getIndex(char letter) {
    int index;

    if(letter == ' ')
        return 26;
    else if(letter == '-')
        return 27;
    else if(letter == 39)
        return 28;

    if(letter >= 'A' && letter <= 'Z')
        letter += 32;

    index = letter - 'a';

    return index;
}

struct trie* addWord(struct trie* root, int* countLetters, string newWord){
    struct trie* current = root;
    int passed[29];

    for(int i = 0; i < 29; i++)
        passed[i] = 0;

    for(int i = 0; newWord[i] != '\0'; i++){
        int index = getIndex(newWord[i]);

        if(passed[index] == 0)
            countLetters[index]++;

        passed[index] = 1;

        if(current->next[index] == nullptr)
            current->next[index] = initNode(newWord[i], 0);

        current = current->next[index];
    }

    current->wordEnding = 1;
    countLetters[29]++;

    return root;
}

int calcPoints(int* countLetters, char letter){
    int index = getIndex(letter);
    return countLetters[29] - countLetters[index];
}

void writeDict(int* countLetters){
    ///ofstream output("countLetters.bin", ios::binary);
    ///output << countLetters;
    ///output.close();

    FILE* f = fopen("countLetters.bin", "wb");

    if(!f)
        cout << "Error opening file to write!";

    fwrite(countLetters, sizeof(int), 30, f);

    fclose(f);
}

void readDict(int* output){
    ///ifstream input("countLetters.bin", ios::binary);
    ///input.read((char*)&output, sizeof(output));
    ///input.close();

    FILE* f = fopen("countLetters.bin", "rb");

    if(!f)
        cout << "Error opening file to read!";

    fread(output, sizeof(int), 30, f);

    fclose(f);
}

int main(){
    struct trie* root = initNode('#', 0);
    int* countLetters = initDic();

    root = addWord(root, countLetters, "tea");
    root = addWord(root, countLetters, "ten");
    root = addWord(root, countLetters, "inn");
    root = addWord(root, countLetters, "in");
    root = addWord(root, countLetters, "i");
    root = addWord(root, countLetters, "a");
    root = addWord(root, countLetters, "to");

    char letter = 't';
    int points = calcPoints(countLetters, letter);

    if(points == -1)
        cout << "Invalid character!" << endl;
    else
        cout << "Points of letter " << letter << ": " << points << endl;

    //writeDict(countLetters);

    int* countLettersInput = new int[30];
    readDict(countLettersInput);

    points = calcPoints(countLettersInput, letter);

    if(points == -1)
        cout << "Invalid character!" << endl;
    else
        cout << "Points of letter " << letter << ": " << points << endl;

    return 0;
}
