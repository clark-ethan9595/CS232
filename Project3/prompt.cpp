/*
 * prompt.cpp provides a class to represent the command-line promp
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

#include "prompt.h"
using namespace std;

Prompt::Prompt() {

	current_directory = getcwd(buff, PATH_MAX + 1);
}

char* Prompt::get() const {

	return current_directory;
}