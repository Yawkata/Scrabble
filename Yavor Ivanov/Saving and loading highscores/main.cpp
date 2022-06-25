#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>


using namespace std;

struct player{
    float highscore;
    char name[50];
};

void printScoreBoard(vector <player> Players){
    cout << "\n\t\tScore Board:" << endl << endl;
    for(int i = 0; i < Players.size(); i++){
        cout << "\t\tNAME: " << Players.at(i).name << endl;
        cout << "\t\tHIGHSCORE: " << Players.at(i).highscore << endl;

    }
}

int checkIfPlayerAlreadyExists(char name[50], vector <player>& Players){
    for(int i = 0; i < Players.size(); i++){
        if(!strcmp(Players.at(i).name, name)){
            cout << "Player: " << name << " already exists!" << endl;
            return 0;
        }
    }
    return 1;

}

void insertNewPlayer(char name[50], float highscore, vector <player>& Players){
    struct player newPlayer;
    newPlayer.highscore = highscore;
    strcpy(newPlayer.name, name);

    checkIfPlayerAlreadyExists(name, Players);

    Players.push_back(newPlayer);

    int i;
    for(i = Players.size() - 1; i > 0 && Players.at(i - 1).highscore < highscore; i--){
        Players.at(i) = Players.at(i - 1);
    }
    Players.at(i) = newPlayer;
}

void savePlayersToFile(string fileName, vector <player>& Players){
    ofstream inputFile(fileName, ios::binary);
	if(inputFile.is_open()){
        int numOfPlayers = Players.size();

        inputFile.write(reinterpret_cast<char *>(&numOfPlayers), sizeof(numOfPlayers));

        for(int i = 0; i < Players.size(); i++){
            inputFile.write(reinterpret_cast<char *>(&Players.at(i)), sizeof(Players.at(i)));
        }
        inputFile.close();

	}else{
        cout << "Error while opening file:" << fileName << endl;
	}

}

vector <player> readPlayersFromFile(string fileName){
    struct player newPlayer;
    vector <player> Players;

    ifstream input_file(fileName, ios::binary);

    int numOfPlayers;
    input_file.read(reinterpret_cast<char *>(&numOfPlayers), sizeof(numOfPlayers));

    while(numOfPlayers > 0){
        input_file.read(reinterpret_cast<char *>(&newPlayer), sizeof(newPlayer));
        Players.push_back(newPlayer);
        numOfPlayers--;

    }
    return Players;
}

int main()
{
    vector<player>Players;

    insertNewPlayer("gosho", 123, Players);
    insertNewPlayer("Tosho", 23, Players);
    insertNewPlayer("Pesho", 234, Players);
    insertNewPlayer("Concho", 150, Players);
    insertNewPlayer("Concho", 30, Players);


    savePlayersToFile("highscores.bin", Players);

    vector<player> Highscores = readPlayersFromFile("highscores.bin");

    printScoreBoard(Players);

    return 0;
}
