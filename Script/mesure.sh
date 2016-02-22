#!/bin/bash

if ! [ -e $PROG ]; then
    echo "[TEST] Compilation : START"
    make rebuild > /dev/null
    
    if [ $? != 0 ]; then
        echo "Compilation error, abort test";
        return -1;
    fi;

    echo -e "[TEST] Compilation : SUCCESS\n";
fi;

time ./BIN/GameOfLife -r 10 -c 10
time ./BIN/GameOfLife -r 10 -c 10 -p 5 
time ./BIN/GameOfLife -r 10 -c 10 -p 5 -g
