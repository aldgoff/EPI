/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	deleteKeyFromArray.h
 *
 *  Created on: Nov 3, 2014
 *      Author: aldgoff
 *
 * Description:
 * Implement a function which accepts an array of integers and a key
 * removes all occurances of that key and stably compacts the array.
 * Return the length of the possibly compacted array.
 * Note, elements past the last valid one are not specified.
 * Ambiguities:
 * 	 Arg order
 * 	 Default args
 * 	 Array type (vector, or C array)
 * 	 Reference or pointer
 * 	 Resize array or not (if vector)
 * 	 Return type (int, long or size_t)
 */

#ifndef DELETEKEYFROMARRAY_H_
#define DELETEKEYFROMARRAY_H_


#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace delete_key_from_array {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual size_t algorithm(vector<int>& v, int key) {
		return 0;
	}
};
class S1 : public Strategy {
public:
	size_t algorithm(vector<int>& v, int key) { // Replace keys with 0, sanity check.
		for(size_t i=0, j=0; j<v.size(); i++, j++) {
			if(v[j] == key)
				v[i] = 0;
		}

		return v.size();
	}
};
class S2 : public Strategy {
public:
	size_t algorithm(vector<int>& v, int key) { // Doesn't preserve order.
		bool resize = false; // Flag to resize if any element was equal to key.
		int j = v.size()-1;
		for(int i=0; i<=j; i++) {
			if(v[i] == key) {
				resize = true;
				while(v[j] == key) {
					j--;
					if(i > j)
						break;
				}
				if(i<j)
					v[i] = v[j--];
			}
			if(i > j)
				break;
		}
		if(resize)
			v.resize(j+1);

		return v.size();
	}
};
class S3 : public Strategy {
public:
	size_t algorithm(vector<int>& v, int key) { // Preserves order, verbose.
		size_t j = 0;
		size_t i = 0;
		for(; j<v.size(); i++, j++) {
			while(v[j] == key) {
				if(++j >= v.size())
					goto exitInnerLoop;	// 'break' would only break out of inner loop.
			}
			if(i != j)
				v[i] = v[j];
		}
		exitInnerLoop:

		if(i != j)
			v.resize(i);	// I like resizing.

		return v.size();
	}
};
class S4 : public Strategy {
public:
	size_t algorithm(vector<int>& v, int key=0) { // Preserves order, consise & efficient.
		size_t i=0;	// Write index.
		for(size_t j=0; j<v.size(); j++) {	// Read index.
			if(v[j] != key)
				v[i++] = v[j];
		}
		return i;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	const int size = 6;
	int tests[][size] = {
		{ 1, 2, 3, 4, 5, 6 },	// No key.
		{ 1, 8, 2, 8, 3, 4 },	// Single keys.
		{ 1, 8, 2, 8, 3, 8 },	// Trailing key.
		{ 1, 8, 8, 8, 2, 3 },	// Repeated keys.
		{ 8, 8, 8, 8, 8, 8 },	// All keys.
	};
	Strategy* poly[] = { new S1, new S2, new S3, new S4 };
	for(size_t j=0; j<COUNT(tests); j++) {
		cout << "\nData: ";
		for(int k=0; k<size; k++)
			cout << tests[j][k];
		cout << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			vector<int> v(tests[j], tests[j]+COUNT(tests[j]));
			size_t len = poly[i]->algorithm(v, 8);
			printf("len: %d: ", len);
			for(size_t k=0; k<len; k++)
				cout << v[k];
			cout << endl;
		}
	}
}

}

class deleteKeyFromArray : public EPI {
public:
	deleteKeyFromArray() : EPI("deleteKeyFromArray") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		delete_key_from_array::demo();
	}
};


#endif /* DELETEKEYFROMARRAY_H_ */
