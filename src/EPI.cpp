//============================================================================
// Name        : EPI.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#include "meta.h"

int main(int argc, char* argv[]) {
	cout << "Hello EPI.\n" << endl;

	cout << argv[0] << "\n\n";		// Where the executable is located.

	if(argc == 1) {					// What commands EPI understands.
		cout << "  No args, so here is the list of them.\n" << endl;
		meta("");
	}

	for(int i=1; i<argc; i++)		// Process the args (requests).
		meta(string(argv[i]));

	cout << "Aloha EPI.\n" << endl;

	return 0;
}
