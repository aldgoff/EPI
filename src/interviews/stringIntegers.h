/*
 * Project: EPI (Elements of Programming Interviews).
 * File:	stringIntegers.h
 *
 *  Created on: Nov 11, 2014
 *      Author: aldgoff
 *
 * Description:
 *  Write routines to convert strings to ints and vice-a-versa.
 */

#ifndef STRINGINTEGERS_H_
#define STRINGINTEGERS_H_


#include <cstdio>
#include <iostream>
using namespace std;

#include "../EPI.h"

namespace string_integers {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual string algorithm(int n) {
		return string("0");
	}
	virtual int algorithm(const string& s) {
		return 0;
	}
};
class S1 : public Strategy {
public:
	virtual string algorithm(int n) {
		if(n == 0)
			return string("0");

		string str("");
		char sign = '+';
		if(n < 0) {
			sign = '-';
			n = -n;
		}
		while(n > 0) {
			int digit = n%10;
			str.insert(0, 1, digit + '0');
			n = n/10;
		}
		if(sign == '-')
			str.insert(0, 1, sign);

		return str;
	}
	virtual int algorithm(const string& s) {
		char sign = s[0];
		if('0'<=sign && sign<='9')
			sign = '+';
		if(sign != '-' && sign != '+')
			throw "Not a number";

		long long n = 0;
		size_t i = (sign == '-') ? 1 : 0;
		for(; i<s.length(); i++) {
			int digit = s[i] - '0';
			if(digit<0 || 9<digit)
				throw "Not a number";
			n = 10*n + digit;
			if(n > INT_MAX)
				cout << "Too Big" << endl;
		}

		return (sign == '-') ? -n : n;
	}
};
class S2 : public Strategy {
public:
	virtual string algorithm(int n) {
		if(n == 0)
			return string("0");

		string str("");
		short start = 0;
		if(n < 0) {
			str.insert(start, 1, '-');
			start = 1;
			n = -n;
		}
		for(; n>0; n/=10) {
			unsigned short digit = n%10 + '0';
			str.insert(start, 1, digit);
		}

		return str;
	}
	virtual int algorithm(const string& s) {
		cout << "Strategy 2 of string to integer interview problem.\n";
		return 0;
	}
};

void demo() {	// Run through 2D matrix: test cases versus strategies.
	int intToS[] = { 0, 1, 15, -8, 223 };
	string StoInt[] = {
		string("0"), string("1"), string("15"),
		string("-8"), string("223"), string("9876543210")
	};
	Strategy* poly[] = { new S1, new S2 };

	for(size_t j=0; j<COUNT(intToS); j++) {
		cout << "\nData " << intToS[j] << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			string str = poly[i]->algorithm(intToS[j]);
			cout << str << endl;
		}
	}

	for(size_t j=0; j<COUNT(StoInt); j++) {
		cout << "\nData \"" << StoInt[j] << "\"" << endl;
		for(size_t i=0; i<COUNT(poly); i++) {
			int n = poly[i]->algorithm(StoInt[j]);
			printf("%d\n", n);
		}
	}
}

}

class stringIntegers : public EPI {
public:
	stringIntegers() : EPI("stringIntegers") {}
public:
	void run(int i) {
		cout << "Interview problem " << i << ": " << name << ".\n";
		string_integers::demo();
	}
};


#endif /* STRINGINTEGERS_H_ */
