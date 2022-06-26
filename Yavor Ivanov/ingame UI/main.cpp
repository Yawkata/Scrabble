#include <iostream>
#include <fstream>

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
    printFile("New Text Document.txt");
    return 0;
}
