#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> /*<+>*/
#define NUM_LETTERS 30

using namespace std;

int* initDict() {
    int* newCountLetters = new int[NUM_LETTERS];

    for(int i = 0; i < NUM_LETTERS; i++)
        newCountLetters[i] = 0;

    return newCountLetters;
};

int letterToIndex(char letter) {
    if(letter >= 'A' && letter <= 'Z')
        letter += 32;

    return letter - 'a';
}

int calcPoints(int* countLetters, char letter) {
    int letterIndex = -1;

    if(letter >= 'A' && letter <= 'Z')
        letter += 32;

    if(letter != ' ' && letter != '-' && letter != 39)
        letterIndex = letterToIndex(letter);
    else if(letter == ' ')
        letterIndex = 26;
    else if(letter == '-')
        letterIndex = 27;
    else
        letterIndex = 28;

    if (letterIndex < 0 || letterIndex > NUM_LETTERS-1) return -1;

    return countLetters[NUM_LETTERS-1] - countLetters[letterIndex];
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

bool trieInsert(struct trieNode* root, string word, int* dict) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;
    bool smthAdded = false;

    bool passedLetters[NUM_LETTERS];
    for(int i = 0; i < NUM_LETTERS; i++) passedLetters[i] = false;

    for(int i = 0; i < word.size(); i++) {
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 32;

        int letterIndex = -1;
        if(word[i] != ' ' && word[i] != '-' && word[i] != 39)
            letterIndex = letterToIndex(word[i]);
        else if(word[i] == ' ')
            letterIndex = 26;
        else if(word[i] == '-')
            letterIndex = 27;
        else
            letterIndex = 28;

        if (letterIndex < 0 || letterIndex > NUM_LETTERS-1) return false;

        if (!passedLetters[letterIndex]) {
            dict[letterIndex]++;
            passedLetters[letterIndex] = true;
        }

        if (cur->children[letterIndex] == NULL) {
            cur->children[letterIndex] = initNode(word[i], (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[letterIndex];
    }

    dict[NUM_LETTERS-1]++;  // на последния индекс се пази броят на всички думи в дървото
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

struct trieNode* getTrieFromDict(string filename, int* dict) {
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

    for (int i = 0; i < NUM_LETTERS; i++) {
        struct trieNode* child = node->children[i];
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

    for (int i = 0; i < NUM_LETTERS-4; i++) {
        struct trieNode* node = root->children[i];

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
    ofstream binFile(CACHE_FILE, ios::binary);

    if(binFile.is_open()){
        binFile.write((char*)root, sizeof(root));
        binFile.close();
    }else{
        cout << "Error" << endl;
    }
}

struct trieNode* getTrieFromCacheFile(){
    struct trieNode* root = initNode('#', false);

    ifstream binFile(CACHE_FILE, ios::binary);

    if(binFile.is_open()){
        binFile.read((char*)root, sizeof(root));
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
    int* dict = initDict();

    if(chooseFile(DICTIONARY_FILE, CACHE_FILE, LOAD_FILE)){
        trie = getTrieFromCacheFile();
    }else{
        trie = getTrieFromDict(DICTIONARY_FILE, dict);
        updateCacheFile(trie);
    }

    printTrie(trie);

    vector<char> testLetters = { 'F', 'i', 'l', 'i', 'p'};
    int sum = 0;

    for(char letter : testLetters) {
        int points = calcPoints(dict, letter);
        sum += points;

        if(points == -1)
            cout << "Invalid character!" << endl;
        else
            cout << "Points of letter " << letter << ": " << points << " -> " << dict[letterToIndex(letter)] << endl;

        cout << endl;
    }

    cout << "Overall points: " << sum << endl;

    cout << endl;
    for (int i = 0; i < NUM_LETTERS-4; i++) cout << "Letter: " << (char)(i+'a') << "\t\t" << dict[i] << endl;

    cout << "Space: " << dict[NUM_LETTERS - 4] << endl;
    cout << "Dash: " << dict[NUM_LETTERS - 3] << endl;
    cout << "Apostrophe: " << dict[NUM_LETTERS - 2] << endl;

    cout << "Words: "<< dict[NUM_LETTERS-1] << endl << endl;

}

int main() {
    //addWordToDictionary("novaduma");
    loadTrie();


}
