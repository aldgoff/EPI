/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	problemInterview.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 *
 */

#ifndef INTERVIEWPROBLEMN_H_
#define INTERVIEWPROBLEMN_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace interview_problem_N {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual void algorithm() {
		return ;
	}
};
class S1 : public Strategy {
public:
	void algorithm() {
		cout << "Strategy 1 of new interview problem.\n";
		return ;
	}
};
class S2 : public Strategy {
public:
	void algorithm() {
		cout << "Strategy 2 of new interview problem.\n";
		return ;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned tests[] = { 1, 2 };
	Strategy* poly[] = { new S1, new S2 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << j+1 << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			poly[i]->algorithm();
		}
	}
}

}

class interviewProblemN : public EPI {
public:
	interviewProblemN() : EPI("interviewProblemN") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		interview_problem_N::demo();
	}
};


#endif /* INTERVIEWPROBLEMN_H_ */
