/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	randomNumbers.h
 *
 *  Created on: Nov 03, 2014
 *      Author: aldgoff
 *
 * Description:
 * Using just a coin flip, generate a uniform distribution of random numbers within a range.
 */

#ifndef RANDOMNUMBERS_H_
#define RANDOMNUMBERS_H_


#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace random_numbers {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual int algorithm(int hi, int lo=0) {
		return 0;
	}
};
class S1 : public Strategy {
public:
	int algorithm(int hi, int lo=0) {
		// Compute for next highest 2^n, repeat if outside range.
		int rn = 0;
		for(;;) {	// Best case, single pass, worse case probability fail 1/2 per pass.
			int range = hi - lo;
			rn = 0;
			for(int i=0; range; i++) {
				rn += ((rand()%2) << i);
				range >>= 1;
			}
			if(rn <= hi - lo)
				break;
		}
		return rn + lo;
	}
};
class S2 : public Strategy {
public:
	int algorithm(int hi, int lo=0) {
		// Compute for next highest 2^n, repeat if outside range.
		int rn = 0;
		for(int j=0; j<10; j++) {
			int range = hi - lo;
			rn = 0;
			for(int i=0; range; i++) {
				rn += ((rand()%2) << i);
				range >>= 1;
			}
			if(rn <= hi - lo)
				break;
			if(j>0)
				printf("(%d) ", j);
		}
		return rn + lo;
	}
};
class S3 : public Strategy {
public:
	int algorithm(int hi, int lo=0) {
		// Compute for next highest 2^n, repeat if outside range.
		int rn = 0, t = hi - lo;
		for(;;) {
			rn = 0;
			for(int i=0; (1<<i <= t); i++) {
				rn = (rn << 1) | (rand()%2);
			}
			if(rn <= t)
				break;
		}
		return rn + lo;
	}
};

struct Data {
	int	hi;
	int lo;
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	Data tests[] = {
		{ 1, 0 },
		{ 3, 0 },
		{ 7, 0 },
		{ 9, 0 },
		{ 9, 0 },
		{ 9, 7 },
	};
	Strategy* poly[] = { new S1, new S2, new S3 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << tests[j].hi << " " << tests[j].lo << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			for(int k=0; k<20; k++) {
				cout << poly[i]->algorithm(tests[j].hi, tests[j].lo) << " ";
			}
			cout << endl;
		}
	}
}

}

class randomNumbers : public EPI {
public:
	randomNumbers() : EPI("randomNumbers") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		random_numbers::demo();
	}
};


#endif /* RANDOMNUMBERS_H_ */
