/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	randomNumbers.h
 *
 *  Created on: Nov 03, 2014
 *      Author: aldgoff
 *
 * Description:
 * Using just a coin flip, generate a uniform distribution of random numbers within a range.
 */

#ifndef RANDOMNUMBERS_H_
#define RANDOMNUMBERS_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace random_numbers {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual int algorithm(int hi, int lo=0) {
		return 0;
	}
};
class S1 : public Strategy {
public:
	int algorithm(int hi, int lo=0) {
		cout << "Strategy 1 of random numbers interview problem.\n";
		return 0;
}
};
class S2 : public Strategy {
public:
	int algorithm(int hi, int lo=0) {
		cout << "Strategy 2 of random numbers interview problem.\n";
		return 0;
	}
};

struct Data {
	int	hi;
	int lo;
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	Data tests[] = {
		{ 5, 0 },
	};
	Strategy* poly[] = { new S1, new S2 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << j+1 << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			cout << poly[i]->algorithm(tests[j].hi, tests[j].lo) << endl;
		}
	}
}

}

class randomNumbers : public EPI {
public:
	randomNumbers() : EPI("randomNumbers") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		random_numbers::demo();
	}
};


#endif /* RANDOMNUMBERS_H_ */
