/*
 * CommandLine.h is a class to read a command-line and construct a vector from the arguments
 *
 *  Created on: Mar 7, 2017
 *      Author: Kyuhyun Jeong
 *		Parthner: Ethan Clark
 * CS 232 - Project 3
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

// Includes
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
using namespace std;

// Declare CommandLine class
class CommandLine {

// Public methods
public:
	CommandLine();
	CommandLine(istream& in);
	char* getCommand() const;
	int getArgCount() const;
	char** getArgVector() const;
	char* getArgVector(int i) const;
	bool noAmpersand() const;
	virtual ~CommandLine();

// Private instance variables
private:
	int argc;
	char** argv;
	vector<string> myArgv;
};

#endif /* COMMANDLINE_H_ */
