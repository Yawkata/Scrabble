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


int main() {
    struct letter* dict = initDict();
    struct trieNode* root = getTrieFromDict("dict.txt", dict);
    
    vector<char> testLetters = { 'a', 't', 'c', '&' };
    
    for(char letter : testLetters) {
        int points = calcPoints(dict, letter);

        if(points == -1)
            cout << "Invalid character!" << endl;
        else
            cout << "Points of letter " << letter << ": " << points << " -> " << dict[letterToIndex(letter)].count << endl;
        
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < NUM_LETTERS; i++) cout << "Letter: " << (char)(i+'a') << "\t\t" << dict[i].count << endl;

    cout << "Words: "<< dict[NUM_LETTERS].count << endl;

    // cout << endl;

    // printTrie(root);
}