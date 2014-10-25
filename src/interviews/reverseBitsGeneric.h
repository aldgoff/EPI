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

template <class T>
void method(const T& arg) {
	printf("%lu.\n", sizeof(arg));
}

template <class T>
class Strategy {
public:
	virtual ~Strategy() {}
	virtual void algorithm(const T& arg) {
		printf("%lu.\n", sizeof(arg));
	}
};
template <class T>
class S1 : public Strategy<T> {
public:
	void algorithm(const T& arg) {
		cout << "Strategy 1 of new interview problem.\n";
		printf("%lu.\n", sizeof(arg));
	}
};
template <class T>
class S2 : public Strategy<T> {
public:
	void algorithm(const T& arg) {
		cout << "Strategy 2 of new interview problem.\n";
		printf("%lu.\n", sizeof(arg));
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	Strategy<char>* poly[] = { new S1<char>, new S2<char> };
	for(size_t i=0; i<COUNT(poly); i++) {
		poly[i]->algorithm(0x05);
	}
	method('x');
	method((short)2);
	method((int)3);
	method((long)4);
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
