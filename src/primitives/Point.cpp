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

#include <Point.h>
#include <cmath>

Point::Point() {
	_data[COORD_X] = 0;
	_data[COORD_Y] = 0;
	_data[COORD_Z] = 0;
}

Point::Point(double x, double y, double z) {
	_data[COORD_X] = x;
	_data[COORD_Y] = y;
	_data[COORD_Z] = z;
}

Point::Point(const Point &p) {
	_data[COORD_X] = p._data[COORD_X];
	_data[COORD_Y] = p._data[COORD_Y];
	_data[COORD_Z] = p._data[COORD_Z];
}

Point::~Point() {

}

double Point::getX() const {
	return _data[COORD_X];
}
double Point::getY() const {
	return _data[COORD_Y];
}

double Point::getZ() const {
	return _data[COORD_Z];
}

const double *Point::getVector() const {
	return _data;
}

Point &Point::operator=(const Point &p) {
	if (&p != this) {
		_data[COORD_X] = p._data[COORD_X];
		_data[COORD_Y] = p._data[COORD_Y];
		_data[COORD_Z] = p._data[COORD_Z];
	}

	return *this;
}

const Point Point::operator+(const Point &p) const {
	Point q(_data[COORD_X] + p._data[COORD_X],
			_data[COORD_Y] + p._data[COORD_Y],
			_data[COORD_Z] + p._data[COORD_Z]);
	return q;
}

const Point Point::operator-(const Point &p) const {
	Point q(_data[COORD_X] - p._data[COORD_X],
			_data[COORD_Y] - p._data[COORD_Y],
			_data[COORD_Z] - p._data[COORD_Z]);
	return q;
}

double Point::operator*(const Point &p) const {
	return _data[COORD_X] * p._data[COORD_X] +
			_data[COORD_Y] * p._data[COORD_Y] +
			_data[COORD_Z] - p._data[COORD_Z];
}

const Point Point::operator^(const Point &p) const {
	Point q(_data[COORD_Y] * p._data[COORD_Z] - _data[COORD_Z] * p._data[COORD_Y],
			_data[COORD_Z] * p._data[COORD_X] - _data[COORD_X] * p._data[COORD_Z],
			_data[COORD_X] * p._data[COORD_Y] - _data[COORD_Y] * p._data[COORD_X]);
	return q;
}

bool Point::operator==(const Point &p) const {
	if (_data[COORD_X] == p._data[COORD_X] &&
			_data[COORD_Y] == p._data[COORD_Y] &&
			_data[COORD_Z] == p._data[COORD_Z])
		return true;
	else
		return false;
}

const Point Point::operator*(double w) const {
	Point q(_data[COORD_X] * w, _data[COORD_Y] * w, _data[COORD_Z] * w);
	return q;
}

double Point::distance(const Point &p) const {
	double dist = 0;

	dist += pow(_data[COORD_X] - p._data[COORD_X], 2);
	dist += pow(_data[COORD_Y] - p._data[COORD_Y], 2);
	dist += pow(_data[COORD_Z] - p._data[COORD_Z], 2);
	dist = sqrt(dist);

	return dist;
}

