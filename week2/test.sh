#!/bin/bash

for i in {1..5}
do
    echo "(input$i)"
    cat input/in$i.txt
    echo -e "\n(p$i 's output)"
    ./p$i < input/in$i.txt
    echo "---"
done