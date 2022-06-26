#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "HS.h"

struct player {
    float highscore;
    char name[50];
};

void printScoreBoard(std::vector <player> players) {
    std::cout << "\n\t\tScore Board:" << std::endl << std::endl;

    if (players.size() == 0)
        return;

    for (int i = 0; i < players.size(); i++) {
        std::cout << "\t\tNAME: " << players.at(i).name << std::endl;
        std::cout << "\t\tHIGHSCORE: " << players.at(i).highscore << std::endl;
    }
}

int checkIfPlayerAlreadyExists(char name[50], std::vector <player>& players) {
    for (int i = 0; i < players.size(); i++) {
        if (!strcmp(players.at(i).name, name)) {
            std::cout << "Player: " << name << " already exists!" << std::endl;
            return 0;
        }
    }

    return 1;
}

void insertNewPlayer(char name[50], float highscore, std::vector <player>& players) {
    struct player newPlayer;
    newPlayer.highscore = highscore;
    strcpy(newPlayer.name, name);

    checkIfPlayerAlreadyExists(name, players);

    players.push_back(newPlayer);

    int i;
    for(i = players.size() - 1; i > 0 && players.at(i - 1).highscore < highscore; i--) {
        players.at(i) = players.at(i - 1);
    }
    players.at(i) = newPlayer;
}

void savePlayersToFile(std::string filename, std::vector <player>& players) {
    std::ofstream inputFile(filename, std::ios::binary);
	if (inputFile.is_open()) {
        int numOfPlayers = players.size();

        inputFile.write(reinterpret_cast<char *>(&numOfPlayers), sizeof(numOfPlayers));

        for (int i = 0; i < players.size(); i++) {
            inputFile.write(reinterpret_cast<char *>(&players.at(i)), sizeof(players.at(i)));
        }
        inputFile.close();

	}else{
        std::cout << "Error while opening file:" << filename << std::endl;
	}

}

std::vector <player> readPlayersFromFile(std::string filename) {
    struct player newPlayer;
    std::vector <player> players;

    std::ifstream input_file(filename, std::ios::binary);

    if(!input_file)
        return players;

    int numOfPlayers;
    input_file.read(reinterpret_cast<char *>(&numOfPlayers), sizeof(numOfPlayers));

    while(numOfPlayers > 0){
        input_file.read(reinterpret_cast<char *>(&newPlayer), sizeof(newPlayer));
        players.push_back(newPlayer);
        numOfPlayers--;

    }

    return players;
}
