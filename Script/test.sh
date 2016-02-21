#!/bin/bash

readonly PROG=./BIN/GameOfLife

AllSucces="";

echo "[TEST] Compilation : START"
make rebuild > /dev/null;
if [ $? != 0 ]; then
    echo "Compilation error, abort test";
    return -1;
fi;

echo -e "[TEST] Compilation : SUCCESS\n";

echo -e "--------------\n";

input=("block.gol" "blinker.gol" "beacon.gol" "empty.gol" "toad.gol")

# If you use odd number of iteration those file WON'T work [cause all of them got a period of 2 
output=("block.gol" "blinker.gol" "beacon.gol" "empty.gol" "toad.gol")

thread=(1 2 5 10)

for file in $(seq 0 $(( ${#input[@]} - 1)) ); do

    TOTAL_ITERATION=$(( $RANDOM % 100 )) 
    if [ $(( $TOTAL_ITERATION % 2 )) -ne 0 ]; then ((--TOTAL_ITERATION)); fi
    if [ $TOTAL_ITERATION -eq 0 ]; then TOTAL_ITERATION=2; fi # We don't want 0 [cause it's infinit] 

    echo -e "--------------";
    echo "Lets start for file : ${input[$file]} - Use : $TOTAL_ITERATION interation";
    echo -e "--------------";
    
    DEFAULT_OPT="-s -f ./Famous_example/${input[$file]} -t $TOTAL_ITERATION"
    DIFF_FILE="./Famous_example/${output[$file]}";

    echo -e "[TEST] Sequential : START";
    
    $PROG $DEFAULT_OPT
    DIFF=$(diff output.gol $DIFF_FILE 2>&1)
       
    echo -n "[TEST] Sequential : ";

    if [ "$DIFF" != "" ]; then
        echo "FAIL";
        echo "$DIFF";
    else 
        echo "SUCCESS";
    fi

    AllSucces+=$([ "$DIFF" == "" ] && echo "." || echo "#")

    echo "";

    echo -e "--------------";
    echo "Multi thread : ";
    echo -e "--------------\n";

    for i in ${thread[@]}; do
        
        echo -e "[TEST] $i thread fined grained : START";

        $PROG $DEFAULT_OPT -p $i -g
        DIFF=$(diff output.gol $DIFF_FILE 2>&1)

        echo -n "[TEST] $i thread fined grained : ";
        
        if [ "$DIFF" != "" ]; then
            echo "FAIL";
            echo "$DIFF";
            echo "";
        else
            echo "SUCCESS";
        fi

        AllSucces+=$([ "$DIFF" == "" ] && echo "." || echo "#")
        
        echo "";
    done;

    echo -e "--------------";
    echo "Multi thread : ";
    echo -e "--------------\n";

    for i in ${thread[@]}; do

        echo -e "[TEST] $i thread average grained : START";

        $PROG $DEFAULT_OPT -p $i
        DIFF=$(diff output.gol $DIFF_FILE 2>&1)
        
        echo -n "[TEST] $i thread average grained : ";
        
        if [ "$DIFF" != "" ]; then
            echo "FAIL";
            echo "$DIFF";
            echo "";
        else 
            echo "SUCCESS";
        fi

        AllSucces+=$([ "$DIFF" == "" ] && echo "." || echo "#")

        echo "";
    done;
done

echo "";
echo "[TEST] All Done : $AllSucces";
