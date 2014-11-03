/*
 * Project: EPI (Elements of Programming Interviews.
 * File:	palindromeInteger.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 * Determine if a decimal integer is a palindrome.
 * 0, 1, 7 - yes.
 * 12, 255 - no.
 * 33, 424 - yes.
 */

#ifndef PALINDROME_INTEGER_H_
#define PALINDROME_INTEGER_H_


#include <cstdio>
#include <cassert>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace palindrome_integer {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual bool algorithm(int x) {
		return false;
	}
};
class S1 : public Strategy {
public:
	bool algorithm(int x) {
		char integer[10+1];
		sprintf(integer, "%d", x);
		short len = strlen(integer);
		if(len == 0)
			return false;

		char* p = &integer[0];
		char* q = &integer[len-1];

		while(p <= q) {
			if(*p++ != *q--)
				return false;
		}

		return true;
	}
};
class S2 : public Strategy {
public:
	bool algorithm(int x) {
		char integer[10+1] = "";
		sprintf(integer, "%d", x);
		short len = strlen(integer);
		short i = 0;
		short j = len-1;

		while(i <= j)
			if(integer[i++] != integer[j--])
				return false;

		return true;
	}
};
class S3 : public Strategy {
public:
	bool algorithm(int x) {
		assert(sizeof(x) << 13);
		const short digits = 10*sizeof(x)/4;
		char integer[1+digits+1] = "";	// Sign, digits, \n.
		sprintf(integer, "%d", x);

		for(int i=0, j=strlen(integer)-1; i<=j; i++,j--)
			if(integer[i] != integer[j])
				return false;

		return true;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	int tests[] = { 0,1,7, -1,12,255, 33,424 };
	Strategy* poly[] = { new S1, new S2, new S3 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << tests[j] << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			cout << poly[i]->algorithm(tests[j]) << endl;
		}
	}
}

}

class palindromeInteger : public EPI {
public:
	palindromeInteger() : EPI("palindromeInteger") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		palindrome_integer::demo();
	}
};


#endif /* PALINDROME_INTEGER_H_ */
