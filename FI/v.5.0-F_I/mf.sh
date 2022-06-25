#! /bin/bash

(g++ -c ./Filip_header/CP.cpp)
(g++ -c ./Ivaylo_header/trie.cpp)
(g++ -c test.cpp)

(g++ test.o trie.o CP.o -o output)
(./output)

(rm *.o output)