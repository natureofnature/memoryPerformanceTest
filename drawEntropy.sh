#!/bin/bash
para1=./Data/CUTCPSM
para2=./Data/LBMSM
para3=./Data/Mix
for i in $(seq 0 1 19)
do
	tmppara1=$para1$i
	tmppara2=$para2$i
	tmppara3=$para3$i
	./CalcuEntropy $tmppara1 $tmppara2 $tmppara3
	python ./Data/line.py $tmppara3 
done;
