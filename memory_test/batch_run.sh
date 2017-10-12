#!/bin/bash
while IFS='     ' read -r option 
do
	echo " "
	echo "option is $option"
	sh run.sh $option	 
	echo " "

done < "$1" #filename
