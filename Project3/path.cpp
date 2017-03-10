/*
 * path.cpp is a class that represents the directories in which our shell program searches
 *		for executable programs
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

// Include header file path.h
#include "path.h"
using namespace std;

/*
 * Path constructor
 * gets PATH environment variable and stores each directory in a vector
 *		by splitting (strtok) by the ":"
 */ 
Path::Path() {

	pPath = getenv("PATH");

	char* pch;
	pch = strtok (pPath, ":");
	while (pch != NULL)
	{
		directories.push_back(pch);
		pch = strtok (NULL, ":");
	}
}

/*
 * find(const string& program) finds the directory that
 *		program is stored
 */
int Path::find(const string& program) const {
	int index = -1;
	DIR *dir;
	struct dirent *ent;
	for (unsigned i = 0; i < directories.size(); i++) {
		if ((dir = opendir(directories[i])) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (ent->d_name == program) {
					index = i;
				}
			}
			closedir(dir);
		}
	}
	return index;
}

/*
 * getDirectory(int i) returns the directory found
 *		at a particular index in the vector
 */
char* Path::getDirectory(int i) const {
	if (i > directories.size()) {
		throw range_error("Invalid index");
	}
	char* temp_directory = directories[i];
	return temp_directory;
}