/*
 * prompt.cpp provides a class to represent the command-line promp
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

// Include prompt class header file
#include "prompt.h"
using namespace std;

/*
 * constructor Prompt()
 * gets current working directory (getcwd)
 */
Prompt::Prompt() {

	current_directory = getcwd(buff, PATH_MAX + 1);
	strcat(current_directory, "/KEShell");
}

/*
 * get() accessor method
 * returns the current_directory variable
 */
char* Prompt::get() const {

	return current_directory;
}