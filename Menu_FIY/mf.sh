#! /bin/bash

(g++ -c ./headers/CP/CP.cpp)
(g++ -c ./headers/HighScores/HS.cpp)
(g++ -c ./headers/Trie/trie.cpp)
(g++ -c ./headers/WWF/WWF.cpp)
(g++ -c code.cpp)

(g++ code.o trie.o CP.o HS.o WWF.o -o output)
(./output)

(rm *.o output)