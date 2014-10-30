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
	virtual bool algorithm(unsigned test) { return false; }
};
class S1 : public Strategy {
public:
	bool algorithm(unsigned test) { // Brute force solution.
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
	bool algorithm(unsigned test) { // Efficiency & succinctness improvements.
		bool parity = false;
		for(size_t i=0; i<8*sizeof(test); i++) {
			if((test >> i) & 0x01)
				parity = !parity;
		}
		return parity;
	}
};
class S3 : public Strategy {
public:
	bool algorithm(unsigned test) { // Table lookup (single hex digit).
		bool table[] = {
			false, true, true, false, // 0, 1, 2, 3,
			true, false, false, true, // 4, 5, 6, 7,
			true, false, false, true, // 8, 9, A, B,
			false, true, true, false, // C, D, E, F.
		};
		bool parity = false;
		for(size_t i=0; i<sizeof(test)<<3; i+=4) {
			if(table[(test >> i) & 0x0F])
				parity = !parity;
		}
		return parity;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned tests[] = { 1, 2, 7, 0xFF };
	Strategy* poly[] = { new S1, new S2, new S3 };
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
