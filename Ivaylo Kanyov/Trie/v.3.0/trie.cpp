#include <iostream>
#include <fstream>
#include <sstream>
#define NUM_LETTERS 26

using namespace std;


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

unsigned int letterToIndex(char letter) {
    return letter - 'a';
}

bool trieInsert(struct trieNode* root, string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;
    bool smthAdded = false;

    for(int i = 0; i < word.size(); i++) {
        unsigned int letterIndex = letterToIndex(word[i]);

        if (cur->children[letterIndex] == NULL) {
            cur->children[letterIndex] = initNode(word[i], (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[letterIndex];
    }

    return smthAdded;
}

bool trieSearch(struct trieNode* root, string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;

    for(int i = 0; i < word.size(); i++) {
        unsigned int letterIndex = letterToIndex(word[i]);
        if (cur->children[letterIndex] != nullptr) {
            cur = cur->children[letterIndex];
        } else return false;
    }

    return (cur->terminal == true);
}

struct trieNode* getTrieFromDict(string filename) {
    if (filename.empty()) return nullptr;
    struct trieNode* root = initNode('#', false);

    ifstream dictionary(filename);

    string line;
    string token;
    while(getline(dictionary, line)) {
        stringstream ss(line);
        while(ss >> token) trieInsert(root, token);
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
    *(count) = 0;

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
    struct trieNode* root = getTrieFromDict("dict.txt");
    printTrie(root);

    cout << endl << (trieSearch(root, "fact") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "a") ? "Found!" : "Not Found!") << endl;
    cout << (trieSearch(root, "ab") ? "Found!" : "Not Found!") << endl;
}