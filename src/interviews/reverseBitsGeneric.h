/*
 * reverseBitsGeneric.h
 *
 *  Created on: Oct 25, 2014
 *      Author: aldgoff
 */

#ifndef REVERSEBITSGENERIC_H_
#define REVERSEBITSGENERIC_H_


#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace reverse_bits_generic {

static unsigned char lookup[256] = {0};

class LookUp {	// Doesn't seem to avoid memory allocation of 256 byte table.
	static unsigned char table[256];
	unsigned char reverseByte(unsigned char byte) {
		static char table[] = {
			0,	// 00b => 00b.
			2,	// 01b => 10b.
			1,	// 10b => 01b.
			3	// 11b => 11b.
		};
		return (table[(byte >> 6) & 0x03] << 0)
		     | (table[(byte >> 4) & 0x03] << 2)
		     | (table[(byte >> 2) & 0x03] << 4)
		     | (table[(byte >> 0) & 0x03] << 6);	// 0x05 <=> 0xA0.
	}
public:
	LookUp() {
		if(lookup[1] != 0x80) { // Fill table for first time.
			cout << "Fill byte lookup table for first time.\n";
			for(int i=0; i<256; i++) {
				table[i] = reverseByte(i);
//				printf("%02X = %02X\n", i, table[i]);
			}
		}
	}
};
unsigned char LookUp::table[256] = {0};

template <class T>
class Strategy : public LookUp {
	unsigned char reverseByte(unsigned char byte) {
		static char table[] = {
			0,	// 00b => 00b.
			2,	// 01b => 10b.
			1,	// 10b => 01b.
			3	// 11b => 11b.
		};
		return (table[(byte&0xC0) >> 6] << 0)
		     | (table[(byte&0x30) >> 4] << 2)
		     | (table[(byte&0x0C) >> 2] << 4)
		     | (table[(byte&0x03) >> 0] << 6);	// 0x05 <=> 0xA0.
	}
public:
	Strategy() {
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
//		cout << arg << endl;
		return arg;
	}
};
template <class T>
class S1 : public Strategy<T> {
public:
	T algorithm(const T& x) {
		if(sizeof(T) == 1)
			return lookup[(unsigned char)x];

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
template <class T>	// Uses template specialization to avoid the run time check for 1 byte size types.
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
template <>
class S2<char> : public Strategy<char> {
public:
	char algorithm(const char& x) {
		return lookup[(unsigned char)x];
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
		Strategy<unsigned short>* poly[] = { new S1<unsigned short>, new S2<unsigned short> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%04X - %04X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		int tests[] = { 0xFF, 0x7F00, 0xF5FF00A0 };
		Strategy<unsigned int>* poly[] = { new S1<unsigned int>, new S2<unsigned int> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%08X - %08X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		long tests[] = { 0x7F00, 0xF5FF00A0, 0x7FFFAAAA };
		char format[] = "%016lX - %016lX\n";
		if(sizeof(long) == 8) {
			tests[2] = 0x7FFFAAAA00FE0000;
			}
		else {
			strcpy(format, "  %08X - %08X\n");
		}
		Strategy<unsigned long>* poly[] = { new S1<unsigned long>, new S2<unsigned long> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf(format, tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	cout << endl;
	{
		char tests[] = { 5, 10, 0x7F };
		Strategy<char>* poly[] = { new S1<char>, new S2<char> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%02X - %02X\n", tests[j], (unsigned char)poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		short tests[] = { 0x0A, 0xFF, 0x7F00 };
		Strategy<short>* poly[] = { new S1<short>, new S2<short> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%04X - %04X\n", tests[j], (unsigned short)poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		int tests[] = { 0xFF, 0x7F00, 0xF5FF00A0 };
		Strategy<int>* poly[] = { new S1<int>, new S2<int> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%08X - %08X\n", tests[j], poly[i]->algorithm(tests[j]));
			}
		}
	}
	{
		long tests[] = { 0x7F00, 0xF5FF00A0, 0x7FFFAAAA00FE0000 };
		Strategy<long>* poly[] = { new S1<long>, new S2<long> };
		for(size_t j=0; j<COUNT(tests); j++) {
			for(size_t i=0; i<COUNT(poly); i++) {
				printf("%016lX - %016lX\n", tests[j], poly[i]->algorithm(tests[j]));
			}
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
