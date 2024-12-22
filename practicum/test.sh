#!/bin/bash

for i in $*
#for i in {1..10}
do
    echo -e "(p$i)"
    g++ -std=c++20 -o p$i p$i.cpp
    ./p$i
    rm p$i
    echo "---"
done