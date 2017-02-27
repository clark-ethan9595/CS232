#!/bin/sh

# Ethan Clark - 1370068
# CS 232 Operating Systems and Networking
# Project 2
# February 27, 2017

# Create variables to compare error messages with
#		routepart is if the computer is shut down
#		windowspart is if the computer is booted in Windows
routepart="No route to host"
windowspart="Connection timed out"

# While loop to read through the names of the computers from the names.txt file
while read line

do
	# ssh into the computer, storing an error message in error.txt and output in output.txt
	#		-n allowed me to continue iterating through the list of names
	#		-o StrictHostKeyChecking=no doesn't prompt me to enter 'yes'
	#		-o ConnectTimeout=5 sets a connection timeout for when the target is down or unreachable, not if it refuses
	#		users lists the users that are logged on to the computer
	ssh -n -o StrictHostKeyChecking=no -o ConnectTimeout=5 $line 'users && exit' 2> error.txt 1> output.txt

	# Read in the error message and output message from the ssh command
	read error < error.txt
	read output < output.txt

	# If the error message shows the computer is shut down...
	if echo "$error" | grep -q "$routepart"; then
		echo $line >> shutDown.txt

	#If the error message shows the computer is booted in Windows...
	elif echo "$error" | grep -q "$windowspart"; then
		echo $line >> windows.txt

	#If there is no error message, but there is output, then there are users logged on...
	elif [ -z "$error" -a -n "$output" ]; then
		echo $line >> occupied.txt
	
	# Otherwise, no error message and no output, there are no users!
	else
		echo "$line" >> openComp.txt
	fi

done < names.txt

# Read in the openComp.txt file to get the open computers
echo
if [ -f $openComp ]; then
	echo "These computer(s) are open..."
	while read name
	do
		echo $name
	done < openComp.txt
else
	echo "There are no open computers..."
fi
echo

# Read in the occupied.txt file to get the computers with users logged on
if [ -f $occupied ]; then
	echo "These computer(s) are occupied by users, booted in Linux..."
	while read name
	do
		echo $name
	done < occupied.txt
else
	echo "There are no computers occupied by users that are booted in Liunx..."
fi
echo

# Read in the shutDown.txt file to get the computers that are shut down
if [ -f $shutDown ]; then
	echo "These computer(s) are shut down..."
	while read name
	do
		echo $name
	done < shutDown.txt
else
	echo "There are no computers that are shut down..."
fi
echo

# Read in the windows.txt file to get the computers booted in Windows
if [ -f $windows ]; then
	echo "These computer(s) are booted in windows..."
	while read name
	do
		echo $name
	done < windows.txt
else
	echo "There are no computers booted in Windows..."
fi
echo

# Delete files so that it starts with a clean slate for next time the program is run
rm windows.txt shutDown.txt openComp.txt occupied.txt error.txt output.txt