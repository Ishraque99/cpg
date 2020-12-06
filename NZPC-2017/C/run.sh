#!/usr/bin/env bash

# Build and run
g++ main.cpp -o solution
./solution < input.txt
./solution < input2.txt
rm solution