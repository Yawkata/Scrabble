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

#define HIGHSCORES "highscores.bin"

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

<<<<<<< HEAD
vector<char> generateSymbols(struct trieNode* root, int numSymbols){
    vector<char> symbols;

    srand(time(0));

    struct trieNode* current = root;
    int count = 0;

    for(int i = 0; i < numSymbols; i++){
        int index = rand() % NUM_VALID_SYMBOLS;
        if(current->children[index] != nullptr){
            symbols.push_back(current->children[index]->symbol);
            current = current->children[index];
        }else{
            i--;
            count++;
            if(count > 30){
                int newIndex = rand() % NUM_VALID_SYMBOLS;
                current = root->children[newIndex];

                while(current == nullptr){
                    newIndex = rand() % NUM_VALID_SYMBOLS;
                    current = root->children[newIndex];
                }

                count = 0;
            }
        }
    }

    return symbols;
}

void printGuessedWords(vector<string> guessedWords){
    cout << endl << endl << "\t\t\tGuessed words: " << endl;
    for(int i = 0; i < guessedWords.size(); i++)
        cout << "\t\t\t" << i + 1 << ". " << guessedWords.at(i) << endl;
}

void printAvailableSymbols(vector<char> symbols){
    cout << endl << endl << "\t\t\tAvailable Symbols: " << endl << "\t\t\t";

    for(unsigned int i = 0; i < symbols.size(); i++)
        cout << symbols.at(i) << " ";

}

void startGame(int numRounds, int numSymbols, struct trieNode* root, int* dict) {
    for(int i = 0; i < numRounds; i++){
        cout << "ROUND 1" << endl << endl;

        vector<char> symbols = generateSymbols(root, numSymbols);
        vector<string> guessedWords;

        while(true){
            printPart("./resources/Menu/title.txt");
            printGuessedWords(guessedWords);
            printAvailableSymbols(symbols);

            cout << endl << endl << "\t\t\t\t\t\t\tEnter word:" << endl << "\t\t\t\t\t\t\t";
            string newWord;
            getline(cin, newWord);

            if(trieSearch(root, newWord))
                guessedWords.push_back(newWord);

        }
    }
=======
void saveScore(int highscore){
    char name[50];
    vector <player> players = readPlayersFromFile(HIGHSCORES);
    cout << "Do you want to save your score? (y/n): ";
    char answer;
    answer = getch();
    if (answer == 'y') {
        cout << "\nEnter your name: ";
        cin >> name;
        insertNewPlayer(name, highscore, players);
        savePlayersToFile(HIGHSCORES, players);
    }else{
        return;
    }
}

void startGame(int numRounds, int numSymbols) {
    //for(int i = 0; i < numRounds; i++)

>>>>>>> 719b909094d32ea2eaaca27fd129f83e90ff4ef8

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
    vector<player> players = readPlayersFromFile(HIGHSCORES);
    printScoreBoard(players);

	getch();
}

void gameLoop() {
    int numRounds = 10;
    int numSymbols = 10;

    int* dict = initDict();
    struct trieNode* root = getTrieFromDict(DICTIONARY_FILE, dict);

    while(true) {
        system("cls");
        printMenu();

        jump:
            char answer;
            answer = getch();
        system("cls");
        if (answer == '1') {  // New Game
<<<<<<< HEAD
            system("cls");
            startGame(numRounds, numSymbols, root, dict);
=======
            startGame(numRounds, numSymbols);
>>>>>>> 719b909094d32ea2eaaca27fd129f83e90ff4ef8
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
