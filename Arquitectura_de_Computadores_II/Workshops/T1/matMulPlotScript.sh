#!/bin/bash
echo "" > outputSer.txt
echo "" > outputPar.txt
for number in {0..2500..100}
do
./matmul_ser $number $number $number $number >> outputSer.txt
./matmul_par $number $number $number $number >> outputPar.txt
done
cat outputSer.txt | python3 plot.py
cat outputPar.txt | python3 plot.py
rm outputSer.txt outputPar.txt
exit 0
