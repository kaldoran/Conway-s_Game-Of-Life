#!/bin/bash

mkdir -p ../Random_example

ROWS=$(( ( RANDOM % 4 )  + 15 ));
COLS=$(( ( RANDOM % 4 )  + 15 ));

echo "$ROWS rows and $COLS column";

NOW=$(date +"%m_%d_%Y");
FILE_NAME="../Random_example/${ROWS}-${COLS}_${NOW}.gol"

echo "Rows : $ROWS" > "$FILE_NAME";
echo "Cols : $COLS" >> "$FILE_NAME";

for i in $(seq 1 $ROWS); do
	for j in $(seq 1 $COLS); do
		PROBA_CELL_ALIVE=$(( RANDOM % 100 ));
		if [ $PROBA_CELL_ALIVE -lt 40 ]; then 
			echo -n "." >> "$FILE_NAME";
		else
			echo -n "#" >> "$FILE_NAME";
		fi
	done;
	echo "" >> "$FILE_NAME";
done;

echo "File generate under the name : $FILE_NAME";
