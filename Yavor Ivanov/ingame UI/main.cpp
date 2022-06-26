#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printFile(const string& fileName) {
    ifstream file (fileName.c_str());
    string line;
    while (getline(file, line)) {
        cout <<  line << endl;
    }
    file.close();
}

int main()
{
    char letter = 'd';
    string directory = "./resources/letters/";
    string fileExtention = ".txt";
    fileExtention.insert(0, 1, letter);
    directory = directory + fileExtention;
    cout << directory;
    cout << endl;
    printFile(directory);


    return 0;
}
