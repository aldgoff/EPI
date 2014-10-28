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

namespace overloading { // C++ can't auto cast overloaded functions.
void sam(long x) {} // This one works.
void iam(char x) {}
void seuss() {
	sam(1l);
	sam('x');
	cout << "Successful call.\n";
}

class Dr { // This one works (with and without virtual).
public:
	virtual ~Dr() {}
	virtual void sam(const long& x) {}
	virtual void iam(const char& x) {}
	void seuss() {
		sam(1l);
		sam('x');
		cout << "Successful call.\n";
	}
};

class Poly {
public:
	virtual ~Poly() {}
	virtual void sam(const long& x) {}
	virtual void iam(const char& x) {}
	void seuss() {
		sam(1l);
		sam('x');
		cout << "Successful call.\n";
	}
};
class Thing1 : public Poly {
	void sam(const long& x) {}
	void iam(const char& x) {}
};
class Thing2 : public Poly {
	void sam(const long& x) {}
	void iam(const char& x) {}
};

void demo() {
	seuss();
	Dr().seuss();
	Poly* pol = new Thing1;
	pol->seuss();
	pol->sam(1);
	pol->sam('x');
}
}

namespace reverse_bits {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual long algorithm(const long& x) {
		return x;
	}
	virtual char algorithm(const char& x) {
		char reversed = x;
		return reversed;
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
	static unsigned char table[256];
	unsigned char reverseByte(unsigned char byte) {
		static char table2x2[] = {
			0,	// 00b => 00b.
			2,	// 01b => 10b.
			1,	// 10b => 01b.
			3	// 11b => 11b.
		};
		return (table2x2[(byte&0xC0) >> 6] << 0)
		     | (table2x2[(byte&0x30) >> 4] << 2)
		     | (table2x2[(byte&0x0C) >> 2] << 4)
		     | (table2x2[(byte&0x03) >> 0] << 6);	// 0x05 <=> 0xA0.
	}
public:
	ByteLookup() {
		if(table[1] != 0x80) { // Fill table for first time.
			cout << "Fill byte lookup table for first time.\n";
			for(int i=0; i<256; i++) {
				table[i] = reverseByte(i);
//				printf("%02X = %02X\n", i, table[i]);
			}
		}
	}
public:
	long algorithm(const long& x) {
//		return variation1(x);
		return variation2(x);
	}
	long variation2(const long& x) {	// Should work if long is 32 bits.
		unsigned long reverse = 0;
		short dist = 8*(sizeof(x)-1);
		unsigned long mask = 0xFF << dist;
		for(size_t i=0; i<sizeof(x); i++) {
//			printf("%2d - %016lX\n", dist-8*i, mask);
			reverse |= ((unsigned long)table[(x & mask) >> (dist-8*i)] << 8*i);
			mask >>= 8;
		}
		return reverse;
	}
	long variation1(const long& x) {	// Only works if long is 64 bits.
		return ((unsigned long)table[(x&0xFF00000000000000) >> 56] <<  0)
		     | ((unsigned long)table[(x&0x00FF000000000000) >> 48] <<  8)
		     | ((unsigned long)table[(x&0x0000FF0000000000) >> 40] << 16)
		     | ((unsigned long)table[(x&0x000000FF00000000) >> 32] << 24)
		     | ((unsigned long)table[(x&0x00000000FF000000) >> 24] << 32)
		     | ((unsigned long)table[(x&0x0000000000FF0000) >> 16] << 40)
		     | ((unsigned long)table[(x&0x000000000000FF00) >>  8] << 48)
		     | ((unsigned long)table[(x&0x00000000000000FF) >>  0] << 56)
		     ;	// 7FFFAAAA00000000 <=> 000000005555FFFE.
	}
};
unsigned char ByteLookup::table[256] = {0};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	long tests[] = { 5, 10, 0xFF, 0xFFFF0000 , 0x7FFFAAAA00FE0000 };
	Strategy* poly[] = { new Incremental, new BitWise, new ByteLookup, new ByteLookup };
	for(size_t j=0; j<COUNT(tests); j++) {
		for(size_t i=0; i<COUNT(poly); i++) {
			printf("%016lX - %016lX\n", tests[j], poly[i]->algorithm(tests[j]));
		}
		cout << endl;
	}
//	overloading::demo();
//	printf("%02X\n", (unsigned char)ByteReverse().algorith(0x05));
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
