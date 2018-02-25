#!/bin/bash
echo "" > outputSer.txt
for number in {0..100000000..500000}
do
./pi_ser $number >> outputSer.txt
done
cat outputSer.txt | python3 plot.py
./pi_ser 200 > outputPar.txt
cat outputPar.txt | python3 plot.py
rm outputSer.txt outputPar.txt
exit 0
