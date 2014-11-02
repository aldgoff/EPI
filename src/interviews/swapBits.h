/*
 * Project: EPI (Elements of Programming Interviews.
 * File:	swap.h
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 *
 * Description:
 * Swap two bits in a 64 bit word.
 */

#ifndef SWAP_BITS_H_
#define SWAP_BITS_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace swap_bits {

typedef long type64bit;

class Strategy {
public:
	virtual ~Strategy() {}
	virtual type64bit algorithm(type64bit x, short i, short j) {
		return 0L;
	}
};
class S1 : public Strategy {
public:
	type64bit algorithm(type64bit x, short i, short j) {
		type64bit hiMask, loMask, hiValue, loValue;
		short dist = i - j;
		if(dist>0) {
			hiMask = 1 << i;
			loMask = 1 << j;
			}
		else if(dist<0) {
			hiMask = 1 << j;
			loMask = 1 << i;
			dist = -dist;
			}
		else {
			return x;
		}
		hiValue = x & hiMask;
		loValue = x & loMask;

		hiValue >>= dist;
		if(hiValue == loValue)
			return x;
		loValue <<= dist;

		x &= ~hiMask;
		x &= ~loMask;

		x |= loValue;
		x |= hiValue;

		return x;
	}
};
class S2 : public Strategy {
public:
	type64bit algorithm(type64bit x, short i, short j) {
		if(i<j) {						// Canonical form: i > j.
			short t = i;
			i = j;
			j = t;
			}
		else if(i==j) {					// Indexes the same.
			return x;
		}
		type64bit hiValue = x & (1 << i);
		type64bit loValue = x & (1 << j);
		if((  hiValue && loValue)		// Bits the same.
		|| (!(hiValue || loValue)))
			return x;
		else { 							// Bits different.
			short dist = i - j;
			if(hiValue) {
				x -= hiValue;
				x += (hiValue >> dist);
				}
			else {
				x -= loValue;
				x += (loValue << dist);
			}
		}

		return x;
	}
};
class S3 : public Strategy {
public:
	type64bit algorithm(type64bit x, short i, short j) {
		if(i==j) return x;
		type64bit hiValue = x & (1 << i);
		type64bit loValue = x & (1 << j);
		if((  hiValue && loValue)		// Bits the same.
		|| (!(hiValue || loValue)))
			return x;
		else {
			x ^= ((1 << i) | (1 << j));
		}

		return x;
	}
};
class S4 : public Strategy {
public:
	type64bit algorithm(type64bit x, short i, short j) {
		if((x>>i & 0x1) != (x>>j & 0x1))
			x ^= ((1L << i) | (1L << j));

		return x;
	}
};

struct Data {
	type64bit	x;
	short		i;
	short		j;
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	Data tests[] = {
		{ 0x80, 3, 3 },	// 0x80 => 0x80.
		{ 0x88, 7, 3 },	// 0x88 => 0x88.
		{ 0x80, 7, 0 },	// 0x80 => 0x01.
		{ 0x80, 0, 7 },	// 0x80 => 0x01.
		{ 0xF0, 2, 4 },	// 0xF0 => 0xE4.
	};
	char fmt[80+1] = "";
	sprintf(fmt, "\nData %%d: 0x%%0%ldlX %%2d %%2d\n", 2*sizeof(type64bit));
	Strategy* poly[] = { new S1, new S2, new S3, new S4 };
	for(int j=0; j<COUNT(tests); j++) {
		printf(fmt, j+1, tests[j].x, tests[j].i, tests[j].j);
		for(size_t i=0; i<COUNT(poly); i++) {
			type64bit swapped = poly[i]->algorithm(tests[j].x, tests[j].i, tests[j].j);
			printf("%016lX\n", swapped);
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
