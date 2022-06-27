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

vector<char> generateSymbols(struct trieNode* root, int numSymbols, int* countSymbols, int* temp){
    vector<char> symbols;

    srand(time(0));

    struct trieNode* current = root;
    int count = 0;

    for(int i = 0; i < numSymbols; i++){
        int index = rand() % NUM_VALID_SYMBOLS;
        if(current->children[index] != nullptr){
            symbols.push_back(current->children[index]->symbol);
            countSymbols[symbolToIndex(current->children[index]->symbol)]++;
            temp[symbolToIndex(current->children[index]->symbol)]++;
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
    for(unsigned int i = 0; i < guessedWords.size(); i++)
        cout << "\t\t\t" << i + 1 << ". " << guessedWords.at(i) << endl;
}

void printAvailableSymbols(vector<char> symbols, int score){
    cout << endl << endl << "\t\t\tCurrent Score: " << score << "\t     Available Symbols: " << endl << "\t\t\t\t\t\t     ";

    for(unsigned int i = 0; i < symbols.size(); i++)
        cout << symbols.at(i) << " ";

}

int containsEnough(int* passed, int* countSymbols){
    for(int i = 0; i < NUM_VALID_SYMBOLS; i++){
        if(passed[i] != 0 && passed[i] > countSymbols[i])
            return 0;
        else if(passed[i] != 0 && passed[i] <= countSymbols[i])
            countSymbols[i] -= passed[i];
    }

    return 1;
}

int containWord(vector<string> guessedWords, string word){
    for(unsigned int i = 0; i < guessedWords.size(); i++){
        if(word == guessedWords.at(i))
            return 0;
    }

    return 1;
}

string toLowerCase(string word){
    for(int i = 0; i < word.size(); i++){
        if(word[i] >= 'A' && word[i] <= 'Z')
            word[i] += 32;
    }

    return word;
}

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

void startGame(int numRounds, int numSymbols, struct trieNode* root, int* dict) {
    int score = 0;
    for(int i = 0; i < numRounds; i++){
        int passed[NUM_VALID_SYMBOLS];
        int countSymbols[NUM_VALID_SYMBOLS];
        int temp[NUM_VALID_SYMBOLS];
        for(int i = 0; i < NUM_VALID_SYMBOLS; i++){
            passed[i] = 0;
            countSymbols[i] = 0;
            temp[i] = 0;
        }

        vector<char> symbols = generateSymbols(root, numSymbols, countSymbols, temp);
        vector<string> guessedWords;

        while(true){
            printPart("./resources/Menu/title.txt");
            cout << endl << endl << "\t\t\t\t\t\t\t  ROUND " << i + 1 << endl << endl;
            printAvailableSymbols(symbols, score);
            printGuessedWords(guessedWords);

            for(int i = 0; i < NUM_VALID_SYMBOLS; i++){
                countSymbols[i] = temp[i];
                passed[i] = 0;
            }

            cout << endl << endl << "\t\t\t\t\t\t\tEnter word:" << endl << "\t\t\t\t\t\t\t";
            string newWord;
            getline(cin, newWord);

            if(newWord == "next round"){
                system("cls");
                break;
            }

            if(newWord == "exit game"){
                system("cls");
                saveScore(score);
                return;
            }

            int containAllLetters = 0;
            for(int i = 0; i < newWord.size(); i++){
                containAllLetters = countSymbols[symbolToIndex(newWord[i])];
                cout << endl << symbolToIndex(newWord[i]) << endl;
                passed[symbolToIndex(newWord[i])]++;
                if(!containAllLetters)
                    break;

            }


            newWord = toLowerCase(newWord);

            if(trieSearch(root, newWord) && containsEnough(passed, countSymbols) && containWord(guessedWords, newWord) && symbolToIndex(newWord[i]) != -1){
                guessedWords.push_back(newWord);
                for(int i = 0; i < newWord.size(); i++)
                    score += calcPoints(dict, newWord[i]);
            }

            system("cls");

        }

    }

    saveScore(score);
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
    //struct trieNode* root = loadTrie(dict);
    struct trieNode* root = getTrieFromDict("dictionary.txt", dict);

    while(true) {
        system("cls");
        printMenu();

        jump:
            char answer;
            answer = getch();
        system("cls");
        if (answer == '1') {  // New Game
            system("cls");
            startGame(numRounds, numSymbols, root, dict);
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
