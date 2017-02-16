/*
 * prank.c displays an annoying message and cannot be interrupted by Cntl-c (by default)
 * 
 * Created by: Ethan Clark
 * Student ID: 1370068
 * CS 232 - Project1
 * Spring 2017
 */

// Include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Create global variables for the command line arguments
int time = 5;
char *msg = "THIS MESSAGE IS ANNOYING";
int enable_int = 0;

/*
 * annoying_message() is the function tied to the SIGALRM signal to display the annoying message
 *
 * sig is the number of the signal that was received 
 */
void annoying_message(int sig) {

	// Print the annoying message
	printf("%s\n", msg);

	// Set the appropriate time for the alarm
	alarm(time);
}

/*
 * main() processes (potential) command line arguments and binds the signals
 *
 * argc is the number of command line arguments read in
 * argv[] is the array of command line arguments
 */
int main(int argc, char *argv[]) {

	// For each command line argument, check if it is a legal oneß
	for (int i = 1; i < argc; i++) {

		// Check for the disable interrupts command line argument
		if (strcmp(argv[i], "+i") == 0) {
			enable_int = 1;
		}

		// Check for the new message command line arguments
		if (strcmp(argv[i], "-m") == 0) {
			msg = argv[i+1];
		}

		// Check for the new time command line argument
		if (strcmp(argv[i], "+t") == 0) {
			time = atoi(argv[i+1]);
		}
	}

	// Bind the annoying_message function to SIGALARM signal
	signal(SIGALRM, annoying_message);

	// Bind the signal ignore function to the SIGINT signal if user did not specify +i argument
	if (enable_int == 0) {
		signal(SIGINT, SIG_IGN);
	}
	
	// Set the appropriate time for the timer and pause the process
	while(1) {
		alarm(time);
		pause();
	}
}