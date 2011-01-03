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

Point::Point(): _x(0), _y(0), _z(0) {

}

Point::Point(double x, double y, double z): _x(x), _y(y), _z(z) {

}

Point::Point(const Point &p) {
	_x = p._x;
	_y = p._y;
	_z = p._z;
}

Point::~Point() {

}

double Point::getX() const {
	return _x;
}
double Point::getY() const {
	return _y;
}

double Point::getZ() const {
	return _z;
}

Point Point::operator=(const Point &p) {
	_x = p._x;
	_y = p._y;
	_z = p._z;

	return *this;
}

const Point Point::operator+(const Point &p) const {
	Point q(_x + p._x, _y + p._y, _z + p._z);
	return q;
}

const Point Point::operator-(const Point &p) const {
	Point q(_x - p._x, _y - p._y, _z - p._z);
	return q;
}

double Point::operator*(const Point &p) const {
	return _x * p._x + _y * p._y + _z - p._z;
}

const Point Point::operator*(double w) const {
	Point q(_x * w, _y * w, _z * w);
	return q;
}

const Point Point::operator+(const Vector &v) const {
	Point q(_x + v._x, _y + v._y, _z + v._z);
	return q;
}

const Point Point::operator-(const Vector &v) const {
	Point q(_x + v._x, _y + v._y, _z + v._z);
	return q;
}
