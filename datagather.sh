#!/bin/bash
#ex: bash datagather.sh
g++ subset.cpp -o subset -std=c++11
g++ datagenerator.cpp -o datagenerator -std=c++11
g++ ntuple.cpp -o ntuple -std=c++11

for j in `seq 3 5`; do
    for k in `seq 1 4`; do
        for i in `seq 1 50`; do 
            ./datagenerator $j $k
	    	(time ./ntuple) 2> ntupleResult.txt	
			while read -r line
			do
				#echo "$line"
				gline=$(grep "real" $line)
				#echo "$gline"
				fTime=${gline/real/}
				#echo $fTime
				fTime2=${fTime/[0-9]*m/}
				#echo $fTime2
				nTupleTime=${fTime2/s/}
				#echo $nTupleTime
			done < ntupleResult.txt	
	    	(time ./subset) 2> subsetResult.txt
			while read -r subLine
			do
				#echo "$subLine"
				gsline=$(grep "real" $subLine)
				#echo "$gsline"
				fsTime=${gsline/real/}
				#echo "$fsTime"
				fsTime2=${fsTime/[0-9]*m/}
				#echo "$fsTime2"
				subsetTime=${fsTime2/s/}
				#echo $subsetTime
			done < subsetResult.txt
	    	echo "$j,$k,$subsetTime,$nTupleTime" >> results.csv
	    	rm ntupleResult.txt
	    	rm subsetResult.txt 
            rm tester.txt
        done
    done
done

rm subset
rm ntuple
rm datagenerator