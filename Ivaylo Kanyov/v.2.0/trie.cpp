#include <iostream>
#include <fstream>
#include <sstream>
#define NUM_LETTERS 26

using namespace std;

struct trieNode {
    string content;
    bool terminal;
    struct trieNode* children[NUM_LETTERS];
};

struct trieNode* initNode(string content, bool terminal) {
    struct trieNode* node = new trieNode;

    node->content = content;
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
            cur->children[letterIndex] = initNode(word.substr(0, i+1), (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[letterIndex];
    }

    return smthAdded;
}

void printTrieRec(struct trieNode* node) {
    if (node->terminal) cout << "Word: " << node->content << endl;

    for (struct trieNode* child : node->children) {
        // prefix += child->letter;
        if (child != NULL) printTrieRec(child);
    }
}

void printTrie(struct trieNode* root) {
    if (!root) {
        cout << "Empty Trie!" << endl;
        return;
    }

    for (struct trieNode* node : root->children) {
        if (node != NULL) printTrieRec(node);
    }
}

struct trieNode* getTrieFromDict(string filename) {
    if (filename.empty()) return nullptr;
    struct trieNode* root = initNode("#", false);

    ifstream dictionary(filename);

    string line;
    string token;
    while(getline(dictionary, line)) {
        stringstream ss(line);
        while(ss >> token) trieInsert(root, token);
    }

    return root;
}


int main() {
    struct trieNode* root = getTrieFromDict("dict.txt");
    printTrie(root);

    // char a = 'a';
    // cout << (int)(a - 'a') << endl;
    // cout << (a - 'a') << endl;
    // cout << a << endl;

    // string a = "duner";
    // for(int i = 0; i < a.size(); i++) cout << "Word: " << a.substr(0, i+1) << endl;
}