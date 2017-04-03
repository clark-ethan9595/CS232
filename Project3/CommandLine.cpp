/*
 * CommandLine.cpp is a class to read a command-line and construct a vector from the arguments
 *
 *  Created on: Mar 7, 2017
 *      Author: Kyuhyun Jeong (kj34)
 *		Partner: Ethan Clark (elc3)
 * CS 232 - Project 3
 */

#include "CommandLine.h"
using namespace std;

/*
 * CommandLine() default constructor
 */
CommandLine::CommandLine() {
	argc = 0;
}

/*
 * CommandLine() explicit constructor
 * Parameter: istream& in
 *		Used to read in the commands from the user
 * Set the noAmpersand bool variable to false if there is an ampersand in the command-line
 */
CommandLine::CommandLine(istream& in) {
	argc = 0;

	noAmpersand_var = true;

	string argString;
	getline(in, argString);
	istringstream argStream (argString);

	string temp;
	while (argStream >> temp) {
		if (strcmp(temp.c_str(), "&") == 0) {
			noAmpersand_var = false;
		} else {
			myArgv.push_back(temp);
			argc++;
		}
	}

	argv = new char*[myArgv.size()];

	for (size_t i = 0; i < myArgv.size(); i++) {
		argv[i] = new char[myArgv[i].size() + 1];
		strcpy(argv[i], myArgv[i].c_str());
	}
}

/*
 * getCommand()
 * Returns the command portion of the command-line
 */
char* CommandLine::getCommand() const{
	return argv[0];
}

/*
 * getArgCount()
 * Returns the number of arguments from the command-line
 */
int CommandLine::getArgCount() const{
	return argc;
}

/*
 * getArgVector()
 * Returns the arguments for the command from the command-line
 *		Accomplished by incrementing the char** array pointer to the 2nd element
 */
char** CommandLine::getArgVector() const{
	return argv;
}

/*
 * getArgVector(int i)
 * Returns the argument from the vector at the given index
 */
char* CommandLine::getArgVector(int i) const{
	return argv[i];
}

/*
 * noAmpersand()
 * Returns true if there was no ampersand given in the command-line
 * Returns false if there was an ampersand given in the command-line
 */
bool CommandLine::noAmpersand() const{
	return noAmpersand_var;
}

/*
 * ~CommandLine()
 * Destructor for the CommandLine class
 * Reclaims memory from each element in argv as well as argv itself
 */
CommandLine::~CommandLine() {
	for (size_t i = 0; i < myArgv.size(); i++) {
		delete[] argv[i];
	}

	delete[] argv;

}

