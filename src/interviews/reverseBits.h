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
	virtual long bits(const long& x) {
		return x;
	}
};
class BitWise : public Strategy {
public:
	long bits(const long& x) {
		long reversed = 0;
		short leftIndex = 8*sizeof(x)-1;
		short rightIndex = 0;
		short dist = leftIndex - rightIndex;
		while((dist = leftIndex - rightIndex) > 0) {
			unsigned leftMask = 1 << leftIndex;
			unsigned leftValue = x & leftMask;
			unsigned rightMask = 1 << rightIndex;
			unsigned rightValue = x & rightMask;
//			printf("%08X(%2d) ", (unsigned)(leftMask | rightMask), dist);
			leftIndex--;
			rightIndex++;
			reversed |= (leftValue >> dist);
			reversed |= (rightValue << dist);
		}
		return reversed;
	}
};
class ByteLookup : public Strategy {

};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned tests[] = { 5, 10, 0xFF, 0x7FFF0000L };
	Strategy* poly[] = { new BitWise, new ByteLookup };
	for(size_t j=0; j<COUNT(tests); j++) {
		for(size_t i=0; i<COUNT(poly); i++) {
			printf("%08X - %08X\n", tests[j], (unsigned)poly[i]->bits(tests[j]));
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
