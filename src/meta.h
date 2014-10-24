/*
 * meta.h
 *
 *  Created on: Oct 23, 2014
 *      Author: aldgoff
 */

#ifndef META_H_
#define META_H_

#ifdef FileStructure

EPI.h
#define COUNT(x) (sizeof(x)/sizeof(*x))
class EPI {
	//...
};

EPI.cpp
#include "meta.h"
int main() {
	//...
}

meta.h
void meta(const string& arg);

meta.cpp
#include "interview1.h"
#include "interview2.h"
// Seam point - so program knows of the interview classes.
void meta(const string& arg) {
	EPI* routines[] = {
		new interview1,
		new interview2,
		// Seam point - so program can respond to arg.
	};
	//...
}

interviewProblem1.h
#include "../EPI.h"
namespace interview_problem_1 {
class Strategy {};
class S1 : public Strategy {};
class S2 : public Strategy {};
void demo() {
	// Run through 2D matrix: test cases versus strategies.
}
}
class interviewProblem1 : public EPI {
public: void run() { interview_problem_1::demo(); }
};

interview2.h
// Ditto.

// Seam point - a new file for each interview problem.

#endif

void meta(const string& arg);


#endif /* META_H_ */
