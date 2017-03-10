/*
 * prompt.h provides a class to represent the command-line promp
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

#ifndef PROMPT_H_
#define PROMPT_H_

// Includes
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <unistd.h>
using namespace std;

// Declare Prompt class
class Prompt {

// Method declarations
public:
	Prompt();
	char* get() const;

// Private instance variables
private:
	char* current_directory;
	char buff[PATH_MAX + 1];
};

#endif