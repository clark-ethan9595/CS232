/*
 * CommandLine.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: kj34
 */

#include "CommandLine.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <sstream>
using namespace std;


CommandLine::CommandLine() {
	// TODO Auto-generated constructor stub
	argc = 0;
}

CommandLine::CommandLine(istream& in) {
	// TODO Auto-generated constructor stub

	argc = 0;

	string argString;
	getline(in, argString);
	istringstream argStream (argString);

	string temp;
	while (argStream >> temp) {
		myArgv.push_back(temp);
		argc++;
	}

	argv = new char*[myArgv.size()];

	for (size_t i = 0; i < myArgv.size(); i++) {
		argv[i] = new char[myArgv[i].size() + 1];
		strcpy(argv[i], myArgv[i].c_str());
	}

}

char* CommandLine::getCommand() const{
	return argv[0];
}

int CommandLine::getArgCount() const{
	return argc;
}

char** CommandLine::getArgVector() const{
	return argv;
}

char* CommandLine::getArgVector(int i) const{
	return argv[i];
}

bool CommandLine::noAmpersand() const{
	for(int i=0; i<argc; i++){
		if (*argv[i] == '&') return false;
	}
	return true;
}

CommandLine::~CommandLine() {
	// TODO Auto-generated destructor stub
	for (size_t i = 0; i < myArgv.size(); i++) {
		delete[] argv[i];
	}

	delete[] argv;

}

