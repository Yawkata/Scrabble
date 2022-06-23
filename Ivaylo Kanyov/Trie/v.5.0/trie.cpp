#include <iostream>
#include <fstream>
#define NUM_VALID_SYMBOLS 28 // букви + ' ' + '-'
#define HTL_VALUE 'a'-'A'  // HTL - higher to lower

using namespace std;

struct trieNode {
    char symbol;
    bool uppercase;
    bool terminal;
    struct trieNode* children[NUM_VALID_SYMBOLS];
};

struct trieNode* initNode(char symbol, bool uppercase, bool terminal) {
    struct trieNode* node = new trieNode;

    node->symbol = symbol;
    node->uppercase = uppercase;
    node->terminal = terminal;
    for(int i = 0; i < NUM_VALID_SYMBOLS; i++) node->children[i] = nullptr;

    return node;
}

int symbolToIndex(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z') return symbol - 'A';
    else if (symbol >= 'a' && symbol <= 'z') return symbol - 'a';
    else if (symbol == ' ') return NUM_VALID_SYMBOLS-2;
    else if (symbol == '-') return NUM_VALID_SYMBOLS-1;
    return -1;
}

bool symbolIsUp(char symbol) {
    return (symbol >= 'A' && symbol <= 'Z');
}

char lowerToUpper(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return symbol - HTL_VALUE;
    return symbol;
}

bool trieInsert(struct trieNode* root, string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;
    bool smthAdded = false;

    for(int i = 0; i < word.size(); i++) {
        int symbolIndex = symbolToIndex(word[i]);
        if (symbolIndex == -1) return false;

        if (cur->children[symbolIndex] == NULL) {
            cur->children[symbolIndex] = initNode(word[i], symbolIsUp(word[i]), (i == word.size()-1));
            smthAdded = true;
        }

        cur = cur->children[symbolIndex];
    }

    return smthAdded;
}

bool trieSearch(struct trieNode* root, string word) {
    if (!root || word.empty()) return false;

    struct trieNode* cur = root;

    for(int i = 0; i < word.size(); i++) {
        int symbolIndex = symbolToIndex(word[i]);
        if (symbolIndex == -1) return false;

        if (cur->children[symbolIndex] != nullptr && cur->children[symbolIndex]->uppercase == symbolIsUp(word[i])) {
            cur = cur->children[symbolIndex];
        } else return false;
    }

    return (cur->terminal == true);
}

struct trieNode* getTrieFromDict(string filename) {
    if (filename.empty()) return nullptr;
    struct trieNode* root = initNode('#', false, false);

    ifstream dictionary(filename);

    string line;
    while(getline(dictionary, line)) {
        trieInsert(root, line);
    }

    return root;
}

void printTrieRec(struct trieNode* node, string cur, int* count) {
    if (node->terminal) {
        cout << "Guess: " << cur << endl;
        (*count)++;
    }

    for (struct trieNode* child : node->children) {
        if (child != NULL) {
            if (child->uppercase) printTrieRec(child, cur+lowerToUpper(child->symbol), count);
            else printTrieRec(child, cur+child->symbol, count);
        }
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

            if (node->uppercase) cur.push_back(lowerToUpper(node->symbol));
            else cur.push_back(node->symbol);
            
            printTrieRec(node, cur, count);
        }
    }

    cout << "Number of guesses: " << *count << endl;
    delete count;
}


int main() {
    struct trieNode* root = getTrieFromDict("testDict.txt");
    printTrie(root);
    cout << (trieSearch(root, "Kukata") ? "True" : "False") << endl;
    cout << (trieSearch(root, "BaNaN S PaTlAjAn") ? "True" : "False") << endl;

    // cout << endl << (trieSearch(root, "fact") ? "Found!" : "Not Found!") << endl;
    // cout << (trieSearch(root, "a") ? "Found!" : "Not Found!") << endl;
    // cout << (trieSearch(root, "ab") ? "Found!" : "Not Found!") << endl;
    // cout << (trieSearch(root, "$") ? "Found!" : "Not Found!") << endl;
}