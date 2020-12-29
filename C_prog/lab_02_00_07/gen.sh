#!/bin/bash

size=$1


touch data.txt

echo $size > data.txt

for (( i=0; i<size; i++))
do
echo $((RANDOM * 10))

done >> data.txt

exit 0 	