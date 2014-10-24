/*
 * meta.h
 *
 *  Created on: Oct 23, 2014
 *      Author: aldgoff
 */

#ifndef META_H_
#define META_H_

#ifdef FileStructure

EPI.h
#define COUNT(x) (sizeof(x)/sizeof(*x))
class EPI {};

EPI.cpp	// main()
#include "meta.h"

meta.h
#include "EPI.h"
void meta(const string& arg);

meta.cpp
#include "interviews.h"	// Contains source code, can only be included in one file.
#include "meta.h"
void meta(const string& arg) {
	EPI* routines[] = {
		new interview1,
		new interview2,
		// Seam point - so program can respond to arg.
	};
	//...
}

interviews.h
#include "interview1.h"
#include "interview2.h"
// Seam point - so program knows of the interview classes.

interview1.h
#include "EPI.h"
namespace interview1 {
class Strategy {};
class S1 : public Strategy {};
class S2 : public Strategy {};
void demo() {
	// Run through 2D matrix: test cases versus strategies.
}
}
class interview1_S1 : public EPI {
public: void run() { interview1::demo(); }
};

interview2.h
// Ditto.

// Seam point - a new file for each interview question.

#endif

void meta(const string& arg);

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace reverse {

class Strategy {
public:
	virtual ~Strategy() {}
	virtual long bits(const long& x) {
		return x;
	}
};
class BitWise : public Strategy {
public:
	long bits(const long& x) {
		long reversed = 0;
		short leftIndex = 8*sizeof(x)-1;
		short rightIndex = 0;
		short dist = leftIndex - rightIndex;
		while((dist = leftIndex - rightIndex) > 0) {
			unsigned leftMask = 1 << leftIndex;
			unsigned leftValue = x & leftMask;
			unsigned rightMask = 1 << rightIndex;
			unsigned rightValue = x & rightMask;
//			printf("%08X(%2d) ", (unsigned)(leftMask | rightMask), dist);
			leftIndex--;
			rightIndex++;
			reversed |= (leftValue >> dist);
			reversed |= (rightValue << dist);
		}
		return reversed;
	}
};
class ByteLookup : public Strategy {};

void demo() {
	unsigned tests[] = { 5, 10, 0xFF, 0x7FFF0000L };
	Strategy* poly[] = { new BitWise, new ByteLookup };
	for(size_t j=0; j<COUNT(tests); j++) {
		for(size_t i=0; i<COUNT(poly); i++) {
			printf("%08X - %08X\n", tests[j], (unsigned)poly[i]->bits(tests[j]));
		}
		cout << endl;
	}
}

}

class EPI {
public:
	string	name;
public:
	EPI(const string& name) : name(name) {}
	virtual ~EPI() {}
public:
	virtual void run(int i) {
		cout << "EPI.run(" << name << ").\n";
	}
};
class reverseBits : public EPI {
public:
	reverseBits() : EPI("reverseBits") {}
public:
	void run(int i=0) {
		cout << "EPI*->run(" << name << ").\n";
		reverse::demo();
	}
};
class something : public EPI {
public:
	something() : EPI("something") {}
public:
	void run(int i=0) {
		cout << "EPI*->run(" << name << ").\n";
	}
};

void meta(const string& arg) {
	EPI* routines[] = {
		new reverseBits,
		new something,
	};

	if(arg == "") {	// Auto generate to avoid 2 more seam points.
		for(size_t i=0; i<COUNT(routines); i++) {	// List for Run Configurations...
			cout << routines[i]->name << endl;
		}
		cout << endl;
		for(size_t i=0; i<COUNT(routines); i++) {	// Include list (#include "EPI.h").
			cout << "#include \"" << routines[i]->name << ".h\"\n";
		}
		cout << endl;
	}

	for(size_t i=0; i<COUNT(routines); i++) {
		if(arg == routines[i]->name) {
			routines[i]->run(i);
			cout << "\n";
			break;
		}
	}
};


#endif /* META_H_ */
