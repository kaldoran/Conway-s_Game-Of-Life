#!/bin/bash

readonly MIN_ROWS=15
readonly MIN_COLS=15

PATH=`/usr/bin/dirname $0`

/usr/bin/mkdir -p ../Random_example

MAX_ROWS=4
MAX_COLS=4

if [ ! -z "$1" ]; then
    if ! [[ "$1" =~ ^[0-9]+$ ]]; then
        echo "$1 need to be an integer";
    else
        MAX_ROWS=$1;
    fi
fi

if [ ! -z "$2" ]; then
    if ! [[ "$2" =~ ^[0-9]+$ ]]; then
        echo "$2 need to be an integer";
    else
        MAX_COLS=$2;
    fi
fi


ROWS=$(( RANDOM % $MAX_ROWS ));
COLS=$(( RANDOM % $MAX_COLS ));

if [ "$ROWS" -lt "$MIN_ROWS" ]; then ROWS=$MIN_ROWS; fi
if [ "$COLS" -lt "$MIN_COLS" ]; then COLS=$MIN_COLS; fi

echo "$ROWS rows and $COLS column";

FILE_NAME="${PATH}/random.gol"

echo "Rows : $ROWS" > "$FILE_NAME";
echo "Cols : $COLS" >> "$FILE_NAME";

for i in $(/usr/bin/seq 1 $ROWS); do
	for j in $(/usr/bin/seq 1 $COLS); do
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
