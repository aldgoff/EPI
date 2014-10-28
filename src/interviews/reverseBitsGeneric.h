/*
 * reverseBitsGeneric.h
 *
 *  Created on: Oct 25, 2014
 *      Author: aldgoff
 */

#ifndef REVERSEBITSGENERIC_H_
#define REVERSEBITSGENERIC_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace reverse_bits_generic {

static unsigned char lookup[256] = {0};

template <class T>
class Strategy {
public:
//	static unsigned char table[256];
private:
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
	Strategy() {
//		if(table[1] != 0x80) { // Fill table for first time.
//			cout << "Fill Strategy<T> byte lookup table for first time for words of size " << sizeof(T) << " bytes.\n";
//			for(int i=0; i<256; i++) {
//				table[i] = reverseByte(i);
////				printf("%02X = %02X\n", i, table[i]);
//			}
//		}
		if(lookup[1] != 0x80) { // Fill table for first time.
			cout << "Fill byte lookup table for first time.\n";
			for(int i=0; i<256; i++) {
				lookup[i] = reverseByte(i);
//				printf("%02X = %02X\n", i, table[i]);
			}
		}
	}
public:
	virtual ~Strategy() {}
	virtual T algorithm(const T& arg) {
		cout << arg << endl;
		return arg;
	}
};
//template <class T>
//unsigned char Strategy<T>::table[256] = {0};

template <class T>
class S1 : public Strategy<T> {
public:
	T algorithm(const T& x) {
		if(sizeof(T) == 1)
			return lookup[x];

		T reverse = 0;
		short dist = 8*(sizeof(x)-1);
		T mask = 0xFF << dist;
		for(size_t i=0; i<sizeof(x); i++) {
			reverse |= ((T)lookup[(x & mask) >> (dist-8*i)] << 8*i);
			mask >>= 8;
		}
		return reverse;
	}
};
template <class T>
class S2 : public Strategy<T> {
public:
	T algorithm(const T& x) {
		T reverse = 0;
		short dist = 8*(sizeof(x)-1);
		T mask = 0xFF << dist;
		for(size_t i=0; i<sizeof(x); i++) {
			reverse |= ((T)lookup[(x & mask) >> (dist-8*i)] << 8*i);
			mask >>= 8;
		}
		return reverse;
	}
};
template <>
class S2<unsigned char> : public Strategy<unsigned char> {
public:
	unsigned char algorithm(const unsigned char& x) {
		return lookup[x];
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	{
		char tests[] = { 5, 10, 0x7F };
		Strategy<unsigned char>* poly[] = { new S1<unsigned char>, new S2<unsigned char> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%02X - %02X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		short tests[] = { 10, 0xFF, 0x7F00 };
		for(size_t j=0; j<COUNT(tests); j++) {
		Strategy<unsigned short>* poly[] = { new S1<unsigned short>, new S2<unsigned short> };
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%04X - %04X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		int tests[] = { 0xFF, 0x7F00, 0xF5FF00A0 };
		for(size_t j=0; j<COUNT(tests); j++) {
		Strategy<unsigned>* poly[] = { new S1<unsigned>, new S2<unsigned> };
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%08X - %08X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		long tests[] = { 0x7F00, 0xF5FF00A0, 0x7FFFAAAA };
		if(sizeof(long) == 8)
			tests[2] = 0x7FFFAAAA00FE0000;
		for(size_t j=0; j<COUNT(tests); j++) {
		Strategy<unsigned long>* poly[] = { new S1<unsigned long>, new S2<unsigned long> };
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%016lX - %016lX\n", tests[j], poly[i]->algorithm(tests[j]));
			}
//			cout << endl;
		}
	}
}

}

class reverseBitsGeneric : public EPI {
public:
	reverseBitsGeneric() : EPI("reverseBitsGeneric") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		reverse_bits_generic::demo();
	}
};


#endif /* REVERSEBITSGENERIC_H_ */
