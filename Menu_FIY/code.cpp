#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <time.h>

#include "./headers/Trie/trie.cpp"
#include "./headers/Trie/trie.h"

#include "./headers/CP/CP.cpp"
#include "./headers/CP/CP.h"

#include "./headers/WWF/WWF.cpp"
#include "./headers/WWF/WWF.h"

#include "./headers/HighScores/HS.cpp"
#include "./headers/HighScores/HS.h"

using namespace std;

void printPart(string filename) {
    Sleep(45);
    ifstream part(filename);
    string line;

    while(getline(part, line)) {
        cout << line << endl;
        Sleep(40);
    }
}

void printMenu() {
    printPart("./resources/Menu/title.txt");
    printPart("./resources/Menu/options.txt");
    printPart("./resources/Menu/creators.txt");
}

void printSettings() {
    printPart("./resources/Menu/title.txt");
    printPart("./resources/Settings/options.txt");
    printPart("./resources/Menu/creators.txt");
}

vector<char> generateSymbols(struct trieNode* root, int numSymbols){
    vector<char> symbols;

    srand(time(0));

    struct trieNode* current = root;

    for(int i = 0; i < numSymbols; i++){
        int index = rand() % NUM_VALID_SYMBOLS;
        //cout << current->children[0]->symbol;
        if(current->children[index] != nullptr){
            cout << endl << "asdf: " << index << endl;
            symbols.push_back(current->children[index]->symbol);
            current = current->children[index];
        }else
            i--;
    }

    return symbols;
}

void startGame(int numRounds, int numSymbols, struct trieNode* root, int* dict) {
    for(int i = 0; i < numRounds; i++){
        int wordsCount = 0;
        //while(true){
            printPart("./resources/Menu/title.txt");

            vector<char> symbols = generateSymbols(root, numSymbols);

        //}

        char symbol;

    }
}

void saveSettings(string filename, int* data) {
    ofstream file(filename);
    file << *(data);
}

int getSettings(string filename) {
    ifstream file(filename);
    string line;
    getline(file, line);
    return stoi(line);
}

bool settingsLoop(int* numRounds, int* numSymbols) {
    while(true) {
        printSettings();

        jump:
            char answer;
            answer = getch();

        if (answer == '1') {  // Given symbols
            system("cls");
            cout << "> Enter new quantity of given symbols: ";
            cin >> *numSymbols;

            if (*numSymbols <= 0 && *numSymbols > 50) {
                cout << endl << "> Invalid quantity!" << endl;
                Sleep(1000);
            }else {
                saveSettings("givenSymbols.txt", numSymbols);
            }

            system("cls");
        }else if(answer == '2') {  // Rounds
            system("cls");
            cout << "> Enter new quantity of rounds: ";
            cin >> *numRounds;

            if(*numRounds <= 0 && *numRounds > 20){
                cout << endl << "> Invalid quantity!" << endl;
                Sleep(1000);
            }else {
                saveSettings("rounds.txt", numRounds);
            }

            system("cls");
        }else if(answer == '3') {  // Back
            system("cls");
            return false;
        }else if(answer == '4') {  // Exit
            system("cls");
            return true;
        }else goto jump;
    }
}

void guessLoop(struct trieNode* root, int* dict) {
    string newGuess;
    cout << "> Please enter a new guess: ";
    getline(cin, newGuess);

    if(!trieSearch(root, newGuess)){
        trieInsert(root, dict, newGuess);
        addWordToDictionary(newGuess);
    }else{
        cout << endl << "> This word already exists";
        Sleep(1000);
    }
}

void showLeaderboard(){
    vector<player> players = readPlayersFromFile("leaderboard.bin");
    printScoreBoard(players);
}

void gameLoop() {
    int numRounds = getSettings("rounds.txt");
    int numSymbols = getSettings("givenSymbols.txt");

    int* dict = initDict();
    struct trieNode* root = getTrieFromDict("dictionary.txt", dict);

    while(true) {
        printMenu();

        jump:
            char answer;
            answer = getch();

        if (answer == '1') {  // New Game
            system("cls");
            startGame(numRounds, numSymbols, root, dict);
        }else if(answer == '2') {  // Settings
            system("cls");
            if(settingsLoop(&numRounds, &numSymbols)) break;
        }else if(answer == '3') {  // Enter new guess
            system("cls");
            guessLoop(root, dict);
            system("cls");
        }else if(answer == '4') {  // Exit
            system("cls");
            break;
        }else if(answer == '5'){
            system("cls");
            showLeaderboard();
        }else goto jump;

    }
}

int main() {
    gameLoop();
    return 0;
}