#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

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

void startGame(int numRounds, int numSymbols) {
    //for(int i = 0; i < numRounds; i++)
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

            if(*numSymbols <= 0){
                cout << endl << "> Invalid quantity!" << endl;
                Sleep(1000);
            }

            system("cls");
        }else if(answer == '2') {  // Rounds
            system("cls");
            cout << "> Enter new quantity of rounds: ";
            cin >> *numRounds;

            if(*numRounds <= 0){
                cout << endl << "> Invalid quantity!" << endl;
                Sleep(1000);
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
    system("cls");
    vector<player> players = readPlayersFromFile("highscores.bin");
    printScoreBoard(players);

	getch();
}

void gameLoop() {
    int numRounds = 10;
    int numSymbols = 10;

    int* dict = initDict();
    struct trieNode* root = getTrieFromDict("dictionary.txt", dict);

    while(true) {
        system("cls");
        printMenu();

        jump:
            char answer;
            answer = getch();
        system("cls");
        if (answer == '1') {  // New Game
            startGame(numRounds, numSymbols);
        }else if(answer == '2') {  // Settings
            if(settingsLoop(&numRounds, &numSymbols)) break;
        }else if(answer == '3') {  // Enter new guess
            guessLoop(root, dict);
        }else if(answer == '4') {
            showLeaderboard();
        }else if(answer == '5'){ // Exit
            break;
        }else goto jump;



    }
}

int main() {
    gameLoop();
    return 0;
}
