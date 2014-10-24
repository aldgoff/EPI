/*
 * EPI.h
 *
 *  Created on: Oct 24, 2014
 *      Author: aldgoff
 */

#ifndef EPI_H_
#define EPI_H_


#define COUNT(x) (sizeof(x)/sizeof(*x))


class EPI {	// Base class for each interview problem. Supports open/closed principle.
public:
	string	name;
public:
	EPI(const string& name="EPIBaseClass") : name(name) {}
	virtual ~EPI() {}
public:
	virtual void run(int i) {
		cout << "EPI.run(" << name << ").\n";
	}
};


#endif /* EPI_H_ */
