/*
 * path.h is a class that represents the directories in which our shell program searches
 *		for executable programs
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <dirent.h>
using namespace std;

class Path {
public:
	Path();
	int find(const string& program) const;
	char* getDirectory(int i) const;

private:
	char* pPath;
	vector<char*> directories;
};

#endif
