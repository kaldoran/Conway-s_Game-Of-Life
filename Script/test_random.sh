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

/usr/bin/make rebuild
cd $PATH_FILE


AllSuccess="";
echo "[TEST] Start creating a random board";
./createRandomBoard.sh 100 100
echo "[TEST] End of creation";

TOTAL_ITERATION=$(randMax 100);
DEFAULT_OPT="-s -f ../Script/random.gol -t $TOTAL_ITERATION"

echo -e "\n--------------"
echo "[TEST] Let's start with $TOTAL_ITERATION iteration";
echo -e "--------------"

# --------------------------------------------

echo -e "\n[TEST] Sequential : START";
../BIN/GameOfLife $DEFAULT_OPT
mv output.gol good.gol
echo "[TEST] Sequential : End";

# --------------------------------------------

RANDOM_THREAD=$(randMax 10);

echo -e "\n[TEST] $RANDOM_THREAD thread fined grained : START";
../BIN/GameOfLife $DEFAULT_OPT -p $RANDOM_THREAD -g
DIFF=$(diff good.gol output.gol 2>&1)
echo -n "[TEST] $RANDOM_THREAD thread fined grained : ";

diffOutput $DIFF;
AllSuccess+=$([ $? -eq 0 ] && echo "." || echo "#" );

# ------------------------------------------

RANDOM_THREAD=$(randMax 10);

echo -e "\n[TEST] $RANDOM_THREAD thread average grained : START";
../BIN/GameOfLife $DEFAULT_OPT -p $RANDOM_THREAD
DIFF=$(diff good.gol output.gol 2>&1)
echo -n "[TEST] $RANDOM_THREAD thread average grained : ";

diffOutput $DIFF;
AllSuccess+=$([ $? -eq 0 ] && echo "." || echo "#" );

echo "";
echo "[TEST] All Done : $AllSuccess";


