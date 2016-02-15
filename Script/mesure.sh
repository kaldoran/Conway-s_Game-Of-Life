#!/bin/bash

make rebuild

time ./BIN/GameOfLife -r 10 -c 10
time ./BIN/GameOfLife -r 10 -c 10 -p 5 
time ./BIN/GameOfLife -r 10 -c 10 -p 5 -g
