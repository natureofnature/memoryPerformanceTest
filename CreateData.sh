#!/bin/bash
FileToDir=./Data/
oldFiles=*
prefix1=LBM
prefix2=CUTCP
dataMixer=Mix
numberofsm=0
pythondraw=./drawline.py
python2draw=./draw2line.py
picturefolder=./picture/
pictureprefix=$picturefolder"sm"
echo "compiling resources"
sh ./compile.sh
echo "Now transfer data"
#scp wzliu@147.8.176.244:~/ParallelOpenCL/*.dat .
echo "!!!!!!!Note no transfer now \n"
echo "Transfer data completed"
echo "Now creating folder"
mkdir -p $FileToDir
rm -f $FileToDir$oldFiles

./split_Sm LBM*.dat $FileToDir$prefix1
./split_Sm CUTCP*.dat $FileToDir$prefix2

echo "Now generating pictures"
mkdir -p $picturefolder
rm -f $picturefolder/* 
for i in $(seq 0 1 $numberofsm)
do
	echo "Now dealing with "$i"th SM's data"
	sourcefile1=$FileToDir$prefix1$i
	sourcefile2=$FileToDir$prefix2$i
	mixedEntropy=$FileToDir$dataMixer
	totalcounter=$FileToDir$dataMixer.counter
	portioncounter1=$FileToDir$dataMixer.portion1
	portioncounter2=$FileToDir$dataMixer.portion2
	./CalcuEntropy $sourcefile1 $sourcefile2 $mixedEntropy 4 4 $totalcounter $portioncounter1 $portioncounter2 
	echo "drawing..."
# 	python $pythondraw $mixedEntropy $pictureprefix$i".Entropy.png" "Entropy on SM"$i
	python $pythondraw $totalcounter $pictureprefix$i".totalWarps.png" "Number of total warps from two kernels on SM"$i
#	python $pythondraw $portioncounter1 $pictureprefix$i".Counter1.png" "Kernel1 total warps on SM"$i
#	python $pythondraw $portioncounter2 $pictureprefix$i".Counter2.png" "Kernel2 total warps on SM"$i
#	python $python2draw $portioncounter1 $portioncounter2 $pictureprefix$i".Counter1_2.png" "Kernel1 and Kernel2 total warps on SM"$i
	
done;
