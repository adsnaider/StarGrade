#/bin/bash

#echo "$@"
g++ -std=c++11 example.cc -o example
./example "$@"
