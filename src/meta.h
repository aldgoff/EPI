/*
 * meta.h
 *
 *  Created on: Oct 23, 2014
 *      Author: aldgoff
 */

#ifndef META_H_
#define META_H_


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
	long tests[] = { 5, 10, 0xFF, 0x7FFF0000L };
	Strategy* poly[] = { new BitWise, new ByteLookup };
	for(size_t j=0; j<sizeof(tests)/sizeof(*tests); j++) {
		for(size_t i=0; i<sizeof(poly)/sizeof(*poly); i++) {
			printf("%08X - %08X\n", (unsigned)tests[j], (unsigned)poly[i]->bits(tests[j]));
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
