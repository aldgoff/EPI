/*
 * parity.h
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 */

#ifndef PARITY_H
#define PARITY_H


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace parity_compute {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual unsigned algorithm(unsigned test) { return 0; }
};
class S1 : public Strategy {
public:
	unsigned algorithm(unsigned test) { // Brute force solution.
		cout << "Strategy 1 of parity interview problem.\n";
		short len = 8*sizeof(test);
		unsigned char mask = 0x01;
		short count = 0;
		for(int i=0; i<len; i++) {
			if((test >> i) & mask)
				count++;
		}
		return count%2;
	}
};
class S2 : public Strategy {
public:
	unsigned algorithm(unsigned test) {
		cout << "Strategy 2 of parity interview problem.\n";
		return 0;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned tests[] = { 1, 2, 7, 0xFF };
	Strategy* poly[] = { new S1, new S2 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << tests[j] << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			cout << poly[i]->algorithm(tests[j]) << endl;
		}
	}
}

}

class parity : public EPI {
public:
	parity() : EPI("parity") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		parity_compute::demo();
	}
};


#endif /* PARITY_H */
