#!/bin/bash
echo "" > outputSer.txt
echo "" > outputPar.txt
for number in {0..100000000..500000}
do
./saxpy_ser $number >> outputSer.txt
./saxpy_par $number >> outputPar.txt
done
cat outputSer.txt | python3 plot.py
cat outputPar.txt | python3 plot.py
rm outputSer.txt outputPar.txt
exit 0
