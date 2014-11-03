/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	doors.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 * Every ith person toggles every ith door (initially closed). Is door n open?
 */

#ifndef DOORS_H_
#define DOORS_H_


#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace doors_open {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual bool algorithm(int door) {
		return false;
	}
};
class S1 : public Strategy {
public:
	bool algorithm(int door) {
		return floor(sqrt(door)) * floor(sqrt(door)) == door;
	}
};
class S2 : public Strategy {
public:
	bool algorithm(int door) {
		int sqrtFloor = floor(sqrt(door));
		return sqrtFloor*sqrtFloor == door;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	unsigned tests[] = { 4, 5,6,7,8, 9, 10,11 };
	Strategy* poly[] = { new S1, new S2 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData " << tests[j] << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			cout << poly[i]->algorithm(tests[j]) << endl;
		}
	}
}

}

class doors : public EPI {
public:
	doors() : EPI("doors") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		doors_open::demo();
	}
};


#endif /* DOORS_H_ */
