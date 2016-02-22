#!/bin/bash

function diffOutput {
    if [ "$1" != "" ]; then
        echo "FAIL"; 
        echo $DIFF;
        return 1;
    else
        echo "SUCCESS";
        return 0;
    fi;
}

function randMax {
    rand_max=$(( $RANDOM % $1 ));
    if [ "$rand_max" -eq 0 ]; then rand_max=1; fi

    echo $rand_max;
}

PATH_FILE=`dirname $0`

if ! [ -e $PROG ]; then
    echo "[TEST] Compilation : START"
    make rebuild > /dev/null
    
    if [ $? != 0 ]; then
        echo "Compilation error, abort test";
        return -1;
    fi;

    echo -e "[TEST] Compilation : SUCCESS\n";
fi;
cd $PATH_FILE

TOTAL_TEST=5
if [ ! -z "$1" ]; then 
    if ! [[ "$1" =~ ^[1-9]||1[0-9]+$ ]]; then
        echo "$1 need to be an integer >0";
    else
        TOTAL_TEST=$1;
    fi;
fi;

AllSuccess="";

for (( i = 0; i < $TOTAL_TEST; i++ )); do

    echo -e "\n--------------"
    echo "[TEST] Start creating a random board";
    ./createRandomBoard.sh 150 150
    echo "[TEST] End of creation";

    TOTAL_ITERATION=$(randMax 100);
    DEFAULT_OPT="-s -f ../Script/random.gol -t $TOTAL_ITERATION"

    echo -e "\n--------------"
    echo "[TEST] Let's start with $TOTAL_ITERATION iteration [$(( i + 1 ))/$TOTAL_TEST]";
    echo -e "--------------"

    # --------------------------------------------

    echo -e "\n[TEST] Sequential : START";
    ../BIN/GameOfLife $DEFAULT_OPT
    mv output.gol good.gol
    echo "[TEST] Sequential : End";

    # --------------------------------------------

    RANDOM_THREAD=$(randMax 20);

    echo -e "\n[TEST] $RANDOM_THREAD thread fined grained : START";
    ../BIN/GameOfLife $DEFAULT_OPT -p $RANDOM_THREAD -g
    DIFF=$(diff good.gol output.gol 2>&1)
    echo -n "[TEST] $RANDOM_THREAD thread fined grained : ";

    diffOutput $DIFF;
    AllSuccess+=$([ $? -eq 0 ] && echo "." || echo "#" );

    # ------------------------------------------

    RANDOM_THREAD=$(randMax 20);

    echo -e "\n[TEST] $RANDOM_THREAD thread average grained : START";
    ../BIN/GameOfLife $DEFAULT_OPT -p $RANDOM_THREAD
    DIFF=$(diff good.gol output.gol 2>&1)
    echo -n "[TEST] $RANDOM_THREAD thread average grained : ";

    diffOutput $DIFF;
    AllSuccess+=$([ $? -eq 0 ] && echo "." || echo "#" );

done;

rm good.gol

echo "";
echo "[TEST] All Done : $AllSuccess";


