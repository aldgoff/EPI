/*
 * swap.h
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 */

#ifndef SWAP_BITS_H_
#define SWAP_BITS_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace swap_bits {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual void algorithm() {}
};
class S1 : public Strategy {
public:
	void algorithm() { cout << "Strategy 1 of swap bits problem.\n"; }
};
class S2 : public Strategy {
public:
	void algorithm() { cout << "Strategy 2 of swap bits problem.\n"; }
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

class swapBits : public EPI {
public:
	swapBits() : EPI("swapBits") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		swap_bits::demo();
	}
};


#endif /* SWAP_BITS_H_ */
