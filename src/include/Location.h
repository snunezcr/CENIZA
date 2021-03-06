/*
 * CENIZA: A multi-model ash dispersion simulation package
 *
 * $BSD License start$
 *
 * Copyright (c) 2011, Red de Ciudadana de Estaciones Meteorologicas Costa Rica
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $BSD License end$
 *
 * Author: Santiago Nunez Corrales <snunezcr@gmail.com>
 *
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include <Point.h>

template <typename D> class Location {
public:
	Location();
	Location(Point &p, D &attributes);
	Location(const Location<D> &location);
	~Location();
	bool operator==(Location<D> location);
	bool processed() const;
	Point &getPoint() const;
	D &getAttributes() const;
	void process();
private:
	bool _processed;
	Point _coords;
	D _attributes;
};

template <typename D>
Location<D>::Location() {

}

template <typename D>
Location<D>::Location(Point &p, D &attributes) {
	_coords = p;
	_attributes = attributes;
}

template <typename D>
Location<D>::Location(const Location<D> &location) {
	if (&location != this) {
		_coords = location._coords;
		_attributes = location._attributes;
	}
}

template <typename D>
Location<D>::~Location() {

}

template <typename D>
bool Location<D>::operator==(Location<D> location) {
	return _coords == location._coords;
}

template <typename D>
bool Location<D>::processed() const {
	return _processed;
}

template <typename D>
void Location<D>::processed() const {
	_processed = true;
}

template <typename D>
Point & Location<D>::getPoint() const {
	return _coords;
}

template <typename D>
D & Location<D>::getAttributes() const {
	return _attributes;
}

#endif /* LOCATION_H_ */
