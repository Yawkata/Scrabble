#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie{
    char* string;
    int wordEnding;
    struct trie* next;
};

struct trie* initNode(char* newString, int wordEnding){
    struct trie* newNode = malloc(sizeof(struct trie));

    newNode->string = malloc(sizeof(char));
    strcpy(newNode->string, newString);

    newNode->wordEnding = wordEnding;

    newNode->next = malloc(sizeof(struct trie) * 26);

    for(int i = 0; i < 26; i++)
        newNode->next[i].string = NULL;

    return newNode;
}

struct letters{
    int count;
};

struct letters* initDic(){
    struct letters* newLettersDic = malloc(sizeof(struct letters) * 26);
    return newLettersDic;
};

int calcPoints(struct letters* lettersDic, char letter, int allWords){
    return allWords - lettersDic[letter - 'a'].count;
}

int main(){
    struct trie* root = initNode("", 0);

    root->next['t' - 'a'] = *initNode("t", 0);
    root->next['a' - 'a'] = *initNode("a", 1);
    root->next['i' - 'a'] = *initNode("i", 1);

    root->next['t' - 'a'].next['o' - 'a'] = *initNode("to", 1);
    root->next['t' - 'a'].next['e' - 'a'] = *initNode("te", 0);

    root->next['i' - 'a'].next['n' - 'a'] = *initNode("in", 1);
    root->next['i' - 'a'].next['n' - 'a'].next['n' - 'a'] = *initNode("inn", 1);

    root->next['t' - 'a'].next['e' - 'a'].next['a' - 'a'] = *initNode("tea", 1);
    root->next['t' - 'a'].next['e' - 'a'].next['d' - 'a'] = *initNode("ted", 0);
    root->next['t' - 'a'].next['e' - 'a'].next['n' - 'a'] = *initNode("ten", 1);

    struct letters* lettersDic = initDic();
    lettersDic['a' - 'a'].count = 2;
    lettersDic['i' - 'a'].count = 3;
    lettersDic['t' - 'a'].count = 3;
    lettersDic['o' - 'a'].count = 1;
    lettersDic['e' - 'a'].count = 2;
    lettersDic['n' - 'a'].count = 3;
    lettersDic['d' - 'a'].count = 0;

    int allWords = 7;

    FILE* f = fopen("dictionary.bin", "wb");

    fwrite(&allWords, sizeof(int), 1, f);
    fwrite(lettersDic, sizeof(struct letters), 26, f);

    fclose(f);

    f = fopen("dictionary.bin", "rb");

    int allWordsInput = 0;
    fread(&allWordsInput, sizeof(int), 1, f);

    struct letters* lettersDicInput = initDic();
    fread(lettersDicInput, sizeof(struct letters), 26, f);

    fclose(f);

    printf("%d\n", allWordsInput);
    printf("%d\n", lettersDicInput['d' - 'a'].count);

    char letter = 't';
    int points = calcPoints(lettersDicInput, letter, allWordsInput);

    if(points == -1)
        printf("Invalid character!\n");
    else
        printf("Points of letter %c: %d\n", letter, points);



    return 0;
}
