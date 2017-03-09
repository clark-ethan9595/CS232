/*
 * KEShell.h is a shell class that simulates a shell program
 *
 * Written by: Ethan Clark & Kyuhyun Jeong
 * CS 232 - Project 3
 * March 6, 2017
 */

// Include KEShell.h header file
#include "KEShell.h"
#include <sys/wait.h>
using namespace std;

/*
 * KEShell() is a constructor for the KEShell class
 */
KEShell::KEShell() { }

/*
 * run() executes the shell
 */
void KEShell::run() {

	while (true) {
		cout << prompt.get() << "$ ";
		CommandLine cl = CommandLine(cin);

		if (cl.getCommand() == "exit") {
			return;
		}

		pid_t child = fork();

		if (child == 0) {
			int index = path.find(cl.getCommand());
			char * temp_char = path.getDirectory(index);
			strcat(temp_char, "/");
			strcat(temp_char, cl.getCommand());
			cout << temp_char;
			execv(temp_char, cl.getArgVector());
		}

		int status;

		if (cl.noAmpersand()) {
			waitpid(child, &status, 0);
		}

		cout << endl;
	}

}