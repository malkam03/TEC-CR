#!/bin/bash
echo "" > output.txt
for nTPB in {0..1000..50}
do
    for n in {1..10000000..500000}
    do 
		./vecadd $nTPB $n >> output.txt
    done
done
cat output.txt | python3 plot.py
rm output.txt
exit 0
