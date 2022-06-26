#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

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
    printPart("./resources/Settings/title.txt");
    printPart("./resources/Settings/options.txt");
    printPart("./resources/Settings/bottom.txt");
}

bool startGame() {
    return false;
}

int settingsLoop() {
    while(true) {
        printSettings();

        jump:
            char answer;
            answer = getch();

        if (answer == '1') {  // Given symbols
            system("cls");
        }else if(answer == '2') {  // Rounds
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

bool wordLoop() {
    while(true) {
        string newGuess;
        cout << "Please enter a new word" << endl;
        cin >> newGuess;
        // check if the word is already in the dict
        return false;
    }
}

void gameLoop() {
    while(true) {
        printMenu();

        jump:
            char answer;
            answer = getch();

        if (answer == '1') {  // New Game
            system("cls");
            if(startGame()) break;
        }else if(answer == '2') {  // Settings
            system("cls");
            if(settingsLoop()) break;
        }else if(answer == '3') {  // Enter new guess
            system("cls");
            if(wordLoop()) break;
            system("cls");
        }else if(answer == '4') {  // Exit
            system("cls");
            break;
        }else goto jump;
    }
}

int main() {
    gameLoop();
    return 0;
}