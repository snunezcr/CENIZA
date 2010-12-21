/*
 * OutOfBoundsException.h
 *
 *  Created on: Dec 21, 2010
 *      Author: snunez
 */

#ifndef OUTOFBOUNDSEXCEPTION_H_
#define OUTOFBOUNDSEXCEPTION_H_

#include <exception>

using std::exception;

class OutOfBoundsException : public exception {
public:
	OutOfBoundsException() : exception () {}
};

#endif /* OUTOFBOUNDSEXCEPTION_H_ */
