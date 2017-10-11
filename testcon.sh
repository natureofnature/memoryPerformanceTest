#!/bin/bash
FILED=./Data/
FILES=*
echo "mkdir"
mkdir -p $FILED
echo $FILED$FILES 
rm -f $FILED$FILES
ls $FILED
