#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct trieNode {
    char letter;
    vector<trieNode*> children;
    bool terminal;
};

struct trie {
    vector <trieNode*> base;
    unsigned int wordsCount;
};


struct trie* trieInit() {
    struct trie* newTrie = new trie;
    newTrie->wordsCount = 0;
    return newTrie;
}

struct trieNode* trieNodeInit(char letter) {
    struct trieNode* newTrieNode = new trieNode;

    newTrieNode->letter = letter;
    newTrieNode->terminal = false;

    return newTrieNode;
}


struct trieNode* getChildByLetter(vector<struct trieNode*> children, char letter) {
    for(struct trieNode* curNode : children)
        if (curNode->letter == letter) return curNode;
    
    return nullptr;
}

bool trieInsert(struct trie* trie, string word) {
    if (!trie) return false;

    struct trieNode* curNode = getChildByLetter(trie->base, word[0]);

    // if the first letter is not found in the base => we add the whole word
    if (!curNode) {
        curNode = trieNodeInit(word[0]);

        if (word.size() == 1) curNode->terminal = true;
        trie->base.push_back(curNode);

        if (curNode->terminal == true) {
            trie->wordsCount++;
            return true;
        }

        // we are going to push every letter into the trie
        for(int i = 1; i < word.size(); i++) {
            curNode->children.push_back(trieNodeInit(word[i]));
            curNode = curNode->children[0];
        }

        curNode->terminal = true;
        trie->wordsCount++;
        return true;
    } else {
        bool addStraight = false;
        struct trieNode* newNode = nullptr;

        for(int i = 1; i < word.size(); i++) {
            newNode = getChildByLetter(curNode->children, word[i]);
            
            if (!newNode) addStraight = true;
            
            if (addStraight) {
                newNode = trieNodeInit(word[i]);
                
                if (i + 1 == word.size()) newNode->terminal = true;
                curNode->children.push_back(newNode);
                
                if (newNode->terminal == true) {
                    trie->wordsCount++;
                    return true;
                }

                // we are going to push every letter into the trie
                for(int j = i+1; j < word.size(); j++) {
                    newNode->children.push_back(trieNodeInit(word[j]));
                    newNode = newNode->children[0];
                }

                newNode->terminal = true;
                trie->wordsCount++;
                break;
            }

            curNode = newNode;
        }

        // if (newNode->terminal) return false;
        // newNode->terminal = true;
        // trie->wordsCount++;
        if (!addStraight && curNode->terminal) return false; // if only the completion of a new word is set
        return true;
    }
}

bool findWordInTrie(struct trie* trie, string word) {
    if(!trie) return false;

    struct trieNode* curNode = getChildByLetter(trie->base, word[0]);
    if (!curNode) return false;

    for(int i = 1; i < word.size(); i++) {
        curNode = getChildByLetter(curNode->children, word[i]);
        if (!curNode) return false;
    }

    if (!curNode->terminal) return false;
    return true;
}

struct trie* getTrieFromDict(string fileName) {
    struct trie* newTrie = trieInit();
    ifstream dictionary(fileName);

    string line;
    string token;
    while(getline(dictionary, line)) {
        stringstream ss(line);
        while(ss >> token) trieInsert(newTrie, token);
    }

    return newTrie;
}

void printTrieRec(struct trieNode* node, string prefix) {
    if (node->terminal) cout << "Word: " << prefix << "\tTerminal: " << node->letter << endl;

    for (struct trieNode* child : node->children) {
        // prefix += child->letter;
        printTrieRec(child, prefix+child->letter);
    }
}

void printTrie(struct trie* trie) {
    if (!trie) {
        cout << "Empty Trie!" << endl;
        return;
    }else if (trie->base.empty()) {
        cout << "Empty Trie!" << endl;
        return;
    } 

    for (struct trieNode* node : trie->base) {
        string beg = "";
        beg.push_back(node->letter);
        printTrieRec(node, beg);
    }
}


int main() {
    /* struct trie* Trie = trieInit();

    // vector<string> testStrings;
    // testStrings.insert(testStrings.end(), { "duner", "duneger", "apple",
    //                                         "app", "application", "zz",
    //                                         "zza", "appy", "abdom", "abdomen",
    //                                         "abdominohysterectomy", "abdominohysterotomy" });

    // for(string item : testStrings)
    //     cout << item << " -> " << ((trieInsert(Trie, item)) ? "True" : "False" )<< endl;
    
    // cout << endl;

    // for(string item : testStrings) // MUST BE FOUND SOMETHING
    //     cout << item << " -> " << ((trieInsert(Trie, item)) ? "True" : "False" )<< endl;


    // cout << endl << "Words in the Trie: " << Trie->wordsCount << endl;

    // cout << endl << "TRIE" << endl;
    // printTrie(Trie); */
    
    struct trie* trieFromFile = getTrieFromDict("dict.txt");
    printTrie(trieFromFile);

    cout << endl;

    cout << "pizza -> " << (findWordInTrie(trieFromFile, "pizza") ? "Found!" : "Not Found!") << endl;
    cout << "abdominohysterotomy -> " << (findWordInTrie(trieFromFile, "abdominohysterotomy") ? "Found!" : "Not Found!") << endl;
    cout << "zza -> " << (findWordInTrie(trieFromFile, "zza") ? "Found!" : "Not Found!") << endl;
    cout << "z -> " << (findWordInTrie(trieFromFile, "z") ? "Found!" : "Not Found!") << endl;
}
