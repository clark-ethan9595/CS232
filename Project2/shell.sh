#!/bin/sh

routepart="No route to host"
windowspart="Connection timed out"

while read line
do
	echo $line
	ssh -n -o StrictHostKeyChecking=no -o ConnectTimeout=5 $line 'users' 2> error.txt 1> output.txt

	read error < error.txt

	read output < output.txt

	if echo "$error" | grep -q "$routepart"; then
		echo "$line is shut down"
	elif echo "$error" | grep -q "$windowspart"; then
		echo "$line is booted in windows"
	elif [ -z "$error" -a -z "$output" ]; then
		echo "$line has no users"
		echo "$line" >> openComp.txt
	else
		echo "$line has users logged on"
	fi

done < names.txt

while read line2
do
	echo $line2
done < openComp.txt