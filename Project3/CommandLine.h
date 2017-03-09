/*
 * CommandLine.h
 *
 *  Created on: Mar 7, 2017
 *      Author: kj34
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_
#include <iostream>
#include <vector>
using namespace std;

class CommandLine {
public:
	CommandLine();
	CommandLine(istream& in);
	char* getCommand() const;
	int getArgCount() const;
	char** getArgVector() const;
	char* getArgVector(int i) const;
	bool noAmpersand() const;
	virtual ~CommandLine();
private:
	int argc;
	char** argv;
	vector<string> myArgv;
};

#endif /* COMMANDLINE_H_ */
