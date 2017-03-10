#include "prompt.h"
#include "path.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdexcept>
using namespace std;

int main() {
	Prompt prompt;

	char* directory = prompt.get();
	cout << directory << endl;

	Path path;

	try {
		char* temp_directory = path.getDirectory(1);
		cout << temp_directory << endl;
	} catch (range_error&) {
		cout << "Invalid index" << endl;
	}

	int index = path.find("man");
	cout << index << endl;

	int index2 = path.find("firefox");
	cout << index2 << endl;

	int index3 = path.find("less");
	cout << index3 << endl;

	int index4 = path.find("ethan");
	cout << index4 << endl;

	return 0;
}