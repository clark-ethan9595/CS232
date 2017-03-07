/*
 * path.hcppis a class that represents the directories in which our shell program searches
 *		for executable programs
 *
 * Written by: Ethan Clark
 * CS 232 - Project 3
 * Partner: Kyuhyun Jeong
 * March 6, 2017
 */

#include "path.h"
using namespace std;

Path::Path() {

	pPath = getenv("PATH");

	char* pch;
	pch = strtok (pPath, ":");
	while (pch != NULL)
	{
		directories.push_back(pch);
		pch = strtok (NULL, ":");
	}

	/*
	for (unsigned i = 0; i < directories.size(); i++) {
		char* temp = directories[i];
		cout << temp << endl;
	}
	*/

}

int Path::find(const string& program) const {
	int index;
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

char* Path::getDirectory(int i) const {
	if (i > directories.size()) {
		throw range_error("Invalid index");
	}
	char* temp_directory = directories[i];
	return temp_directory;
}