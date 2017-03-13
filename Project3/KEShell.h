/*
 * KEShell.h is a shell class that simulates a shell program
 *
 * Written by: Ethan Clark (elc3) & Kyuhyun Jeong (kj34)
 * CS 232 - Project 3
 * March 13, 2017
 */

#ifndef KESHELL_H_
#define KESHELL_H_

// Includes
#include <iostream>
#include <sys/wait.h>
#include "path.h"
#include "prompt.h"
#include "CommandLine.h"
using namespace std;

// Declare KEShell class
class KEShell {

// Public section of KEShell class
public:
	// KEShell constructor
	KEShell() { };
	void run();

// Private instance variables
private:
	Prompt prompt;
	Path path;
	
};

#endif