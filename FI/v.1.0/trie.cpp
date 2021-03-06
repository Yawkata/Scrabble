#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> /*<+>*/
#define NUM_LETTERS 26

using namespace std;


struct letter {
    unsigned int count;
};

struct letter* initDict() {
    struct letter* newCountLetters = new letter[27];

    for(int i = 0; i < NUM_LETTERS+1; i++)
        newCountLetters[i].count = 0;

    return newCountLetters;
};

int letterToIndex(char letter) {
    return letter - 'a';
}

int calcPoints(struct letter* countLetters, char letter) {
    unsigned int letterIndex = letterToIndex(letter);
    if (letterIndex < 0 || letterIndex > NUM_LETTERS-1) return -1;

    return countLetters[NUM_LETTERS].count - countLetters[letterIndex].count;
}

struct trieNode {
    char letter;
    bool terminal;
    struct trieNode* children[NUM_LETTERS];
};

struct trieNode* initNode(char letter, bool terminal) {
    struct trieNode* node = new trieNode;

    node->letter = letter;
    node->terminal = terminal;
    for(int i = 0; i < NUM_LETTERS; i++) node->children[i] = nullptr;

    return node;
}

bool trieInsert(struct trieNode* root, string word, struct letter* dict) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;
    bool smthAdded = false;

    bool passedLetters[NUM_LETTERS];
    for(int i = 0; i < NUM_LETTERS; i++) passedLetters[i] = false;

    for(int i = 0; i < word.size(); i++) {
        int letterIndex = letterToIndex(word[i]);
        if (letterIndex < 0 || letterIndex > NUM_LETTERS-1) return false;

        if (!passedLetters[letterIndex]) {
            dict[letterIndex].count++;
            passedLetters[letterIndex] = true;
        }

        if (cur->children[letterIndex] == NULL) {
            cur->children[letterIndex] = initNode(word[i], (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[letterIndex];
    }

    dict[NUM_LETTERS].count++;  // на последния индекс се пази броят на всички думи в дървото
    return smthAdded;
}

bool trieSearch(struct trieNode* root, string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;

    for(int i = 0; i < word.size(); i++) {
        unsigned int letterIndex = letterToIndex(word[i]);
        if (letterIndex < 0 || letterIndex > NUM_LETTERS-1) return false;

        if (cur->children[letterIndex] != nullptr) {
            cur = cur->children[letterIndex];
        } else return false;
    }

    return (cur->terminal == true);
}

struct trieNode* getTrieFromDict(string filename, struct letter* dict) {
    if (filename.empty()) return nullptr;
    struct trieNode* root = initNode('#', false);

    ifstream dictionary(filename);

    string line;
    string token;
    while(getline(dictionary, line)) {
        stringstream ss(line);
        while(ss >> token) trieInsert(root, token, dict);
    }

    return root;
}

void printTrieRec(struct trieNode* node, string cur, int* count) {
    if (node->terminal) {
        cout << "Word: " << cur << endl;
        (*count)++;
    }

    for (struct trieNode* child : node->children) {
        if (child != NULL) printTrieRec(child, cur+child->letter, count);
    }
}

void printTrie(struct trieNode* root) {
    if (!root) {
        cout << "Empty Trie!" << endl;
        return;
    }

    int* count = new int;
    *count = 0;

    for (struct trieNode* node : root->children) {
        if (node != NULL) {
            string cur = "";
            cur.push_back(node->letter);
            printTrieRec(node, cur, count);
        }
    }

    cout << "Number of words: " << *count << endl;
    delete count;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
#define DICTIONARY_FILE "dictionary.txt"
#define CACHE_FILE "cache.bin"
#define LOAD_FILE "last_modified.txt"

void updateLoadFile(string fileName){
    fstream loadFile;
    loadFile.open(LOAD_FILE, ios::out);

    if(loadFile.is_open()){
        loadFile << fileName << endl;
        loadFile.close();
    }else{
        cout << "Error" << endl;
    }
}

void updateCacheFile(struct trieNode* root){
    fstream binFile;
    binFile.open(CACHE_FILE, ios::out);

    if(binFile.is_open()){
        binFile.write((char*)root, sizeof(struct trieNode));
        binFile.close();
    }else{
        cout << "Error" << endl;
    }
}

struct trieNode* getTrieFromCacheFile(){
    struct trieNode* root = initNode('#', false);

    fstream binFile;
    binFile.open(CACHE_FILE, ios::in | ios::binary);

    if(binFile.is_open()){
        binFile.read((char*)root, sizeof(struct trieNode));
        binFile.close();
    }

    return root;
}

int chooseFile(string dictFileName, string cacheFileName, string loadFileName){
    string fileToLoad;

    fstream loadFile;
    loadFile.open(LOAD_FILE, ios::in);
    if(loadFile.is_open()){
        getline(loadFile, fileToLoad);
        loadFile.close();
    }else{
        loadFile.open(LOAD_FILE, ios::out);
        printf("\nTree will be loaded from the .txt file!\n");
        updateLoadFile(cacheFileName);
        loadFile.close();
        return 0;
    }


    if(fileToLoad == cacheFileName){
        printf("\nTree will be loaded from the .bin file!\n");
        return 1;
    }

    printf("\nTree will be loaded from the .txt file!\n");
    updateLoadFile(cacheFileName);
    return 0;
}

void addWordToDictionary(string word){
    fstream dictFile;
    dictFile.open(DICTIONARY_FILE, ios::app);

    if(dictFile.is_open()){
        dictFile << word << endl;
        dictFile.close();
    }else{
        cout << "Error" << endl;
    }

    updateLoadFile(DICTIONARY_FILE);
}

void loadTrie(){
    struct trieNode* trie = initNode('#', false);
    struct letter* dict = initDict();

    if(chooseFile(DICTIONARY_FILE, CACHE_FILE, LOAD_FILE)){
        trie = getTrieFromCacheFile();
    }else{
        trie = getTrieFromDict(DICTIONARY_FILE, dict);
        updateCacheFile(trie);
    }
}



int main() {
    addWordToDictionary("novaduma");
    loadTrie();
}
