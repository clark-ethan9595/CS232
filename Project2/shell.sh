#!/bin/sh

while read line
do
	echo $line
	ssh -o StrictHostKeyChecking=no $line 'who' > test.txt
	echo $line
done < names.txt