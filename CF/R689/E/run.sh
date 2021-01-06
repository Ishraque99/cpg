#!/usr/bin/env bash

# Build and run
g++ main.cpp -o solution
./solution < input1.txt
./solution < input2.txt
./solution < input3.txt
./solution < input4.txt
./solution < input5.txt
rm solution