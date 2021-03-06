/*
 * KEShell.h is a shell class that simulates a shell program
 *
 * Written by: Ethan Clark (elc3) & Kyuhyun Jeong (kj34)
 * CS 232 - Project 3
 * March 13, 2017
 */

// Include KEShell.h header file
#include "KEShell.h"
using namespace std;

/*
 * run() executes the shell
 * Algorithm:
 *	1. Output the prompt directory
 *	2. Create a CommandLine object to read in the commands from the user
 *	3. If the command was exit -> return from while loop.
 *	4. If the command was cd -> change directory with chdir()
 *	5. If the command was pwd -> output the working directory
 *	6. If the command was invalid (i.e. path.find() returns -1) -> Inform the user command was invalid
 *	7. Otherwise valid command...
 *		a. Create child process
 *		b. Have the child process do the following:
 *			i. Get the index of the path of the command
 *			ii. Get the directory path of the command
 *			iii. Add the command to the end of the path directory
 *			iv. Get the argument Vector and add NULL to the last spot
 *			v. Execute command with execve()
 *			vi. If ampersand was not given -> wait for child to finish before prompting again
 */
void KEShell::run() {

	while (true) {
		cout << prompt.get() << "$ ";
		CommandLine cl = CommandLine(cin);

		if (strcmp(cl.getCommand(), "exit") == 0) {
			cout << "Goodbye" << endl;
			return;
		}

		if (strcmp(cl.getCommand(), "cd") == 0) {
			int return_value = chdir(cl.getArgVector(1));
			if (return_value == -1) {
				cout << "Invalid directory name..." << endl;
			} else {
				prompt = Prompt();
			}
			continue;
		}

		if (strcmp(cl.getCommand(), "pwd") == 0) {
			cout << endl << prompt.get() << endl;
			continue;
		}

		if (path.find(cl.getCommand()) == -1) {
			cout << "Command not found..." << endl;
		} else {
			pid_t child = fork();

			if (child == -1) {
				cout << "Fork failed..." << endl;
			}

			if (child == 0) {
				int index = path.find(cl.getCommand());
				char* temp_char = path.getDirectory(index);
				strcat(temp_char, "/");
				strcat(temp_char, cl.getCommand());

				char ** temp_vec = cl.getArgVector();
				temp_vec[cl.getArgCount()] = NULL;

				execve(temp_char, temp_vec, NULL);

			}

			int status;

			if (cl.noAmpersand()) {
				waitpid(child, &status, 0);
			}

			cout << endl;
		}
	}

}