/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	firstMissing.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 *  Find the least positive integer not in an array of length N;
 *  the array need not be preserved.
 */

#ifndef FIRSTMISSING_H_
#define FIRSTMISSING_H_


#include <cstdio>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#include "../EPI.h"

namespace first_missing {

class Strategy {
protected:
	void swap(int& a, int& b) {
		int t = a;
		a = b;
		b = t;
	}
public:
	virtual ~Strategy() {}
	virtual int algorithm(vector<int>& v) {
		return 1;
	}
};
class S1 : public Strategy {
public:
	int algorithm(vector<int>& v) {
		int leastPos = v.size() + 1;
		vector<int> index(v.size(), 0);
		for(size_t i=0; i<v.size(); i++) {
			if(0<v[i] && v[i]<=(int)v.size())
				index[v[i]-1] = v[i];
		}
		for(size_t i=0; i<index.size(); i++) {
			if(index[i] != (int)i + 1) {
				leastPos = i + 1;
				break;
			}
		}

		return leastPos;
	}
};
class S2 : public Strategy {
public:
	int algorithm(vector<int>& v) {
		vector<int> index(v.size(), 0);
		for(size_t i=0; i<v.size(); i++) {
			if(0<v[i] && v[i]<=(int)v.size())
				index[v[i]-1] = v[i];
		}
		for(size_t i=0; i<index.size(); i++) {
			if(index[i] == 0)
				return(i + 1);
		}

		return v.size() + 1;
	}
};
class S3 : public Strategy { // Book answer, but isn't quite correct.
public:
	int algorithm(vector<int>& v) {
		for(size_t i=0; i<v.size(); i++) {
			if(0<v[i] && v[i]<=(int)v.size() && v[i] != v[v[i]-1])
				swap(v[i], v[v[i]-1]);
			else
				i++;
		}

		for(int i=0; i<(int)v.size(); i++) {
			if(v[i] != i + 1)
				return(i + 1);
		}

		return v.size() + 1;
	}
};
class S4 : public Strategy { // Hits infinite loop on test case 7.
public:
	int algorithm(vector<int>& v) {
		for(int i=0; i<(int)v.size(); i++) {
			if(v[i] == i+1)
				continue;
			for(;;) {
				int n = v[i];	// 6 3 5 2 1.
//				printf("%d", n); fflush(stdout);
				if(n == i+1)
					break;
				if(n<=0 || (int)v.size()<n) {
					v[i] = 0;
					break;
				}
				int t  = v[n-1];// 3
				v[n-1] = n;		//
				v[i]   = t;		//
			}
//			cout << endl;
		}
//		for(size_t i=0; i<v.size(); i++) {
//			cout << v[i];
//		}
//		cout << endl;

		for(size_t i=0; i<v.size(); i++) {
			if(v[i] == 0)
				return(i + 1);
		}

		return v.size() + 1;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	const int size = 6;
	int tests[][size] = {
		{ 1, 2, 3, 4, 5, 6 },	// Simple integers (7).
		{ 6, 1, 5, 4, 2, 3 },	// Randomized (7).
		{ 9, 8, 5, 8, 3, 8 },	// Different answer (1).
		{ 1, 8, 8, -8, 2, 3 },	// With negative numbers (4).
		{ -9,-9,-9,-9,-9,-9 },	// All negative (1).
		{ 1, 9, 2, 4, 5, 6 },	// Missing n (3).
		{ 3, 3, 1, 2, 5, 5 }	// Dups (4) - S4 produces infinite loop.
	};
	Strategy* poly[] = { new S1, new S2, new S3 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData: ";
		for(int k=0; k<size; k++)
			cout << tests[j][k];
		cout << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			vector<int> v(tests[j], tests[j]+COUNT(tests[j]));
			int leastPos = poly[i]->algorithm(v);
			printf("len: %d\n", leastPos); fflush(stdout);
		}
	}
}

}

class firstMissing : public EPI {
public:
	firstMissing() : EPI("firstMissing") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		first_missing::demo();
	}
};


#endif /* FIRSTMISSING_H_ */
