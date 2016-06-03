#!/bin/bash
#input: [number of iterations] [number of items] [number of copies] 
#ex: bash sanity_check.sh 10 6 2
g++ subset.cpp -o subset
g++ datagenerator.cpp -std=c++11 -o datagenerator
g++ ntuple.cpp -std=c++11 -o ntuple

FAILED=0
for i in `seq 1 $1`; do 

    ./datagenerator $2 $3

    ./subset >> subset.txt
    ./ntuple tester.txt >> ntuple.txt
    
    diff subset.txt ntuple.txt >> results.txt
    
    if [ -s results.txt ]
    then
        cat subset.txt >> subset_failed_test_$i.txt
        cat ntuple.txt >> ntuple_failed_test_$i.txt
        FAILED=$((FAILED+1))        
    fi

    rm subset.txt
    rm ntuple.txt
    
    rm tester.txt
    rm results.txt
done
if [ "$FAILED" -gt 0 ];
then
    echo "$FAILED tests failed."
else
    echo "All tests passed."
fi