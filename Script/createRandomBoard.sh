#!/bin/bash

readonly MIN_ROWS=10
readonly MIN_COLS=10
LC_NUMERIC=C
PATH_NAME=`/usr/bin/dirname $0`

/usr/bin/mkdir -p ../Random_example

MAX_ROWS=150
MAX_COLS=150

if [ ! -z "$1" ]; then
    if ! [[ "$1" =~ ^[0-9]+$ ]]; then
        echo "$1 need to be an integer";
    else
        ROWS=$1;
    fi
fi

if [ ! -z "$2" ]; then
    if ! [[ "$2" =~ ^[0-9]+$ ]]; then
        echo "$2 need to be an integer";
    else
        COLS=$2;
    fi
fi

if [ -z "$1" ]; then
    ROWS=$(( RANDOM % $MAX_ROWS ));
    COLS=$(( RANDOM % $MAX_COLS ));
fi

if [ "$ROWS" -lt "$MIN_ROWS" ]; then ROWS=$MIN_ROWS; fi
if [ "$COLS" -lt "$MIN_COLS" ]; then COLS=$MIN_COLS; fi

echo "$ROWS rows and $COLS column";

FILE_NAME="${PATH_NAME}/random.gol"
POURCENT_SLICE=$(echo "scale=2;$ROWS/100" | /usr/bin/bc -l)

echo "Rows : $ROWS" > "$FILE_NAME";
echo "Cols : $COLS" >> "$FILE_NAME";

for (( i = 1; i <= $ROWS; i++ )); do
    for (( j = 1; j <= $COLS; j++ )); do
		PROBA_CELL_ALIVE=$(( RANDOM % 100 ));
		if [ $PROBA_CELL_ALIVE -lt 40 ]; then 
			echo -n "." >> "$FILE_NAME";
		else
			echo -n "#" >> "$FILE_NAME";
		fi
	done;
	echo "" >> "$FILE_NAME";
    printf '\r%.2f %% done' "$(echo "scale=2; $i/$POURCENT_SLICE" | bc -l )"
done;
echo ""
echo "File generate under the name : $FILE_NAME";
