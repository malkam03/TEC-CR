#!/bin/bash
echo "" > output.txt
export SHOW_IMAGES=0
for host in "master" "master,node1" "master,node3" "master,node1,node3"
do
	for image in "Images/1.jpg" "Images/2.jpg" "Images/3.jpeg"
	do
		for div in 1 2 4 5 6 9 13 15 20 
		do
			mpirun -np $div -host $host ./imageFilter_MPI $image 150 >> output.txt
		done
	done
done
cat output | python3 plot.py
rm output.txt
exit 0
