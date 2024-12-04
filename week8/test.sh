#!/bin/bash

for i in {1..5}
do
    echo "(input$i)"
    cat input/in$i.txt
    echo -e "\n(p$i 's output)"
    g++ -std=c++20 -o p$i p$i.cpp
    ./p$i < input/in$i.txt
    rm p$i
    echo "---"
done