//============================================================================
// Name        : EPI.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Novatia Labs 2014
// Description : Study for SWE interviews following "Elements of Programming Interviews" (EPI).
//============================================================================

/* File structure
 * A main program (EPI.cpp) that executes individual interview questions via command line.
 * No args produces list of arguments understood by program.
 * (And a list of include files, to simplify the seam points of adding more interview questions.)
 * The files meta.h/cpp contain the basic control logic, a Strategy design pattern;
 * the base class is EPI.
 * Each of the header files uses namespaces and the Strategy pattern to highlight
 * testing and iterative refinement.
 */
//============================================================================

#include <iostream>
using namespace std;

#include "meta.h"

int main(int argc, char* argv[]) {
	cout << "Hello EPI.\n" << endl;

	if(argc == 1) {					// What commands EPI understands.
		cout << "  No args, so here is the list of them.\n" << endl;
		meta("");
	}

	for(int i=1; i<argc; i++)		// Process the args (requests).
		meta(string(argv[i]));

	cout << "Aloha EPI.\n" << endl;

	return 0;
}
