/*
 * reverseBits.h
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 */

#ifndef REVERSEBITS_H_
#define REVERSEBITS_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace reverse_bits {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual long algorithm(const long& x) {
		return x;
	}
};
class Incremental : public Strategy {
public:
	long algorithm(const long& x) {
		long reversed = 0;
		unsigned long leftMask = (1L << (8*sizeof(x)-1));
		unsigned long rightMask = 1;
		for(int dist=8*sizeof(x)-1; dist>0; dist-=2) {
			printf("%016lX(%2d) ", (unsigned long)(leftMask | rightMask), dist);
			leftMask >>= 1;
			rightMask <<= 1;
		}
		return reversed;
	}
};
class BitWise : public Strategy {
public:
	long algorithm(const long& x) {
		long reversed = 0;
		short dist = 8*sizeof(x) - 1;
		unsigned long leftMask = (1L << dist);
		unsigned long rightMask = 1;
		for(; dist>0; dist-=2) {
			unsigned long leftValue = x & leftMask;
			unsigned long rightValue = x & rightMask;
			reversed |= (leftValue >> dist);
			reversed |= (rightValue << dist);
			leftMask >>= 1;
			rightMask <<= 1;
		}
		return reversed;
	}
};
class ByteLookup : public Strategy {

};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned long tests[] = { 5, 10, 0xFF, 0xFFFF0000 , 0x7FFFAAAA00000000 };
	Strategy* poly[] = { new Incremental, new BitWise, new ByteLookup };
	for(size_t j=0; j<COUNT(tests); j++) {
		for(size_t i=0; i<COUNT(poly); i++) {
			printf("%016lX - %016lX\n", tests[j], (unsigned long)poly[i]->algorithm(tests[j]));
		}
		cout << endl;
	}
}

}

class reverseBits : public EPI {
public:
	reverseBits() : EPI("reverseBits") {}
public:
	void run(int i=0) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		reverse_bits::demo();
	}
};


#endif /* REVERSEBITS_H_ */
