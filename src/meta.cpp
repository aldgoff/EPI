/*
 * meta.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#include "interviews/reverseBits.h"
#include "interviews/reverseBitsGeneric.h"
#include "interviews/parity.h"
#include "interviews/swapBits.h"
#include "interviews/palindromeInteger.h"
#include "interviews/randomNumbers.h"
#include "interviews/doors.h"
#include "interviews/dutchFlag.h"
#include "interviews/deleteKeyFromArray.h"
#include "interviews/interviewProblemN.h"
// Seam point - so program knows of the interview classes.

void meta(const string& arg) {
	EPI* routines[] = {
		new parity,
		new swapBits,
		new reverseBits,
		new reverseBitsGeneric,
		new palindromeInteger,
		new randomNumbers,
		new doors,
		new dutchFlag,
		new deleteKeyFromArray,
		new interviewProblemN,
		// Seam point - so program can respond to arg.
	};

	if(arg == "") {	// Auto generate to avoid 2 more seam points.
		for(size_t i=0; i<COUNT(routines); i++) {	// List for Run Configurations...
			cout << routines[i]->name << endl;
		}
		cout << endl;
		for(size_t i=0; i<COUNT(routines); i++) {	// Include list (#include "EPI.h").
			cout << "#include \"interviews/" << routines[i]->name << ".h\"\n";
		}
		cout << endl;
		}
	else {
		bool goodArg = false;
		for(size_t i=0; i<COUNT(routines); i++) {
			if(arg == routines[i]->name) {
				routines[i]->run(i+1);
				cout << "\n";
				goodArg = true;
				break;
			}
		}
		if(!goodArg)
			cout << "Unknown interview problem: " << arg << ".\n";
	}

	return;
}
