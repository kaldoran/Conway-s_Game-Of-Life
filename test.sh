#!/bin/bash


make rebuild;

thread=(1 2 5 10)

for i in ${thread[@]}; do
	./BIN/GameOfLife -s -f ./Famous_example/block.gol
	diff output.gol ./Famous_example/block.gol > /tmp/diffgol 2>&1
	if [ $? != 0 ]; then
		echo "The grid compute by program and the one made by hand are different, checkout /tmp/diffgol to see the diff";
		cat /tmp/diffgol
	else 
		echo "Test with $i thread success";
	fi
done;

for i in ${thread[@]}; do
	./BIN/GameOfLife -s -f ./Famous_example/block.gol -p $i -g
	diff output.gol ./Famous_example/block.gol > /tmp/diffgol 2>&1
	if [ $? != 0 ]; then
		echo "The grid compute by program and the one made by hand are different, checkout /tmp/diffgol to see the diff";
		cat /tmp/diffgol
	else 
		echo "Test with $i thread success";
	fi
done;

for i in ${thread[@]}; do
	./BIN/GameOfLife -s -f ./Famous_example/block.gol -p $i
	diff output.gol ./Famous_example/block.gol > /tmp/diffgol 2>&1
	if [ $? != 0 ]; then
		echo "The grid compute by program and the one made by hand are different, checkout /tmp/diffgol to see the diff";
		cat /tmp/diffgol
	else 
		echo "Test with $i thread success";
	fi
done;
echo "Done";
