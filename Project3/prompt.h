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

#include <string>
#include <limits.h>
#include <unistd.h>
using namespace std;

class Prompt {
public:
	Prompt();
	char* get() const;
private:
	char* current_directory;
	char buff[PATH_MAX + 1];
};

#endif