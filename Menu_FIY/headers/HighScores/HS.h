#ifndef HS_H
#define HS_H

#include <iostream>
#include <vector>

struct player;

void printScoreBoard(std::vector <player> players);

int checkIfPlayerAlreadyExists(char name[50], std::vector <player>& players);
void insertNewPlayer(char name[50], float highscore, std::vector <player>& players);

void savePlayersToFile(std::string filename, std::vector <player>& players);
std::vector <player> readPlayersFromFile(std::string filename);

#endif