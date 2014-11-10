/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	dutchFlag.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 *
 */

#ifndef DUTCHFLAG_H_
#define DUTCHFLAG_H_


#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace dutch_flag {

struct Data {
	int pivot;
	int	list[10];
public:
	void print() {
		printf("(%d) ", pivot);
		for(int i=0; i<10; i++) {
			cout << list[i] << " ";
		}
		cout << endl;
	}
};

class Strategy {
protected:
	void swap(int& a, int& b) {
		int t = a;
		a = b;
		b = t;
	}
public:
	virtual ~Strategy() {}
	virtual void algorithm(Data& x, vector<int>& y, int pivot) {}
};
class S1 : public Strategy {
public:
	// 1 1 5 5 x x x x 9 9.
	//     l   s       m
	// 4 5 5 1
	//   l   s
	void algorithm(Data& x, vector<int>& y, int pivot) {
		int less = 0;
		int same = 0;
		int more = 9;
		while(same <= more) {
			if(x.list[same] > x.pivot) {
				swap(x.list[same], x.list[more--]);
				}
			else if(x.list[same] == x.pivot) {
				same++;
				}
			else { // list[same] < pivot.
				swap(x.list[same++], x.list[less++]);
			}
		}
	}
};
class S2 : public Strategy {
public:
	void algorithm(Data& x, vector<int>& y, int pivot) {
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	Data tests[] = {
		{ 5, { 8, 8, 5, 0, 2, 5, 4, 5, 1, 9 } },
		{ 5, { 5, 4, 5, 1, 9, 8, 8, 5, 0, 2 } },
	};
	Strategy* poly[] = { new S1, new S2 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData:  ";	tests[j].print();
		for(size_t i=0; i<COUNT(poly); i++) {
			Data morph = tests[j];
			vector<int> v(10);
			for(int k=0; k<10; k++) v[k] = tests[j].list[k];
			poly[i]->algorithm(morph, v, tests[j].pivot);
			morph.print();
		}
	}
}

}

class dutchFlag : public EPI {
public:
	dutchFlag() : EPI("dutchFlag") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		dutch_flag::demo();
	}
};


#endif /* DUTCHFLAG_H_ */
