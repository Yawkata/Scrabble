#include <iostream>

using namespace std;

struct trie{
    char letter;
    int wordEnding;
    struct trie* next[26];
};

struct letters{
    int count;
};

struct trie* initNode(char newLetter, int wordEnding){
    struct trie* newNode = new struct trie;

    newNode->letter = newLetter;

    newNode->wordEnding = wordEnding;

    for(int i = 0; i < 26; i++)
        newNode->next[i] = nullptr;

    return newNode;
}

struct letters* initDic(){
    struct letters* newCountLetters = new struct letters[27];

    for(int i = 0; i < 27; i++)
        newCountLetters[i].count = 0;

    return newCountLetters;
};

struct trie* addWord(struct trie* root, struct letters* countLetters, string newWord){
    struct trie* current = root;
    int passed[26];

    for(int i = 0; i < 26; i++)
        passed[i] = 0;

    for(int i = 0; newWord[i] != '\0'; i++){
        if(passed[newWord[i] - 'a'] == 0)
            countLetters[newWord[i] - 'a'].count++;

        passed[newWord[i] - 'a'] = 1;

        if(current->next[newWord[i] - 'a'] == nullptr)
            current->next[newWord[i] - 'a'] = initNode(newWord[i], 0);

        current = current->next[newWord[i] - 'a'];
    }

    current->wordEnding = 1;
    countLetters[26].count++;

    return root;
}

int calcPoints(struct letters* countLetters, char letter){
    if(letter < 'a' || letter > 'z')
        return -1;

    return countLetters[26].count - countLetters[letter - 'a'].count;
}

int main(){
    struct trie* root = initNode('\0', 0);
    struct letters* countLetters = initDic();

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

    return 0;
}
