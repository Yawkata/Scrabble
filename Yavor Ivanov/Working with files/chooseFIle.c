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

int chooseFile(char file1Name[50], char file2Name[50]){
    int timestamp;
    int cond = 0;

    FILE *txt;
    txt = fopen(file1Name,"r+");

    if(txt == NULL){
      printf("Error!");
      exit(1);
    }

    FILE *bin;
    bin = fopen("file2Name","wb+");

    if(bin == NULL)
    {
      printf("\nTree will be loaded from the .txt file!!!\n");
      return 1;
    }

    fread(&timestamp, sizeof(int), 1, txt);
    if(timestamp){
        printf("\nTree will be loaded from the .txt file!\n");
        fseek(txt, 0, SEEK_SET);
        fwrite(&cond, sizeof(int), 1, txt);

        fclose(txt);
        fclose(bin);
        return 1;
    }else{
        printf("\nTree will be loaded from the .bin file!\n");

        fclose(txt);
        fclose(bin);
        return 0;

    }

    return -1;
}

void addWord(char file1Name[50], char word[50]){
    FILE *fptr;
    fptr = fopen(file1Name,"r+");

    int cond = 1;

    fwrite(&cond, sizeof(int), 1, fptr);

    fseek(fptr, 0, SEEK_END);
    fprintf(fptr, "%s", "\n");
    fprintf(fptr, "%s", word);

    fclose(fptr);

}

void setup(char file1Name[50]){
    int cond = 1;

    FILE *fptr;
    fptr = fopen(file1Name,"r+");
    fwrite(&cond, sizeof(int), 1, fptr);

    fclose(fptr);
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

    //setup("dictionary.txt");

    chooseFile("dictionary.txt", "cache.bin");
    //addWord("dictionary.txt", "New Word");





    /*
    FILE *bin;
    bin = fopen("file2Name","r");

    if(bin == NULL)
    {
      printf("\nerror\n");
      return 0;
    }

    struct trie* root2 = initNode("", 0);

    fread(&root2, sizeof(struct trie), 1, bin);

    printf("\n\n%s", root->next['t' - 'a'].next['e' - 'a'].next['n' - 'a'].string);
    */



    return 0;
}
