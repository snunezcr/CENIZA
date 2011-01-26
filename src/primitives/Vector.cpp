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

#include <Constants.h>
#include <Vector.h>
#include <cmath>

Vector::Vector(): _x(0), _y(0), _z(0) {

}

Vector::Vector(double x, double y, double z): _x(x), _y(y), _z(z) {

}

Vector::Vector(const Vector &v) {
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

Vector::~Vector() {

}

double Vector::getX() const {
	return _x;
}
double Vector::getY() const {
	return _y;
}

double Vector::getZ() const {
	return _z;
}

Vector Vector::operator=(const Vector &v) {
	_x = v._x;
	_y = v._y;
	_z = v._z;

	return *this;
}

const Vector Vector::operator+(const Vector &v) const {
	Vector w(_x + v._x, _y + v._y, _z + v._z);
	return w;
}

const Vector Vector::operator-(const Vector &v) const {
	Vector w(_x - v._x, _y - v._y, _z - v._z);
	return w;
}

double Vector::operator*(const Vector &v) const {
	return _x * v._x + _y * v._y + _z - v._z;
}

const Vector Vector::operator^(const Vector &v) const {
	Vector w(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x);
	return w;
}

const Vector Vector::operator*(double w) const {
	Vector v(_x * w, _y * w, _z * w);
	return v;
}

bool Vector::operator==(const Vector &v) const {
	if (_x == v._x && _y == v._y && _z == v._z)
		return true;
	else
		return false;
}

const Vector Vector::normalize() const {
	// The vector 0, 0, 0 cannot be normalized with the inverse of its modulo
	double invnorm;
	if (polarMag() == 0) {
		invnorm = 1;
	} else {
		invnorm = 1.0 / polarMag();
	}
		Vector v = *this * invnorm;
	return v;
}

double Vector::polarMag() const {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

double Vector::polarPhi() const {
	// Catch the case of 0, y, z
	if (_x == 0)
		return PI/2;
	else
		return atan(_y / _x);
}

double Vector::polarPsi() const {
	// Catch the case of 0, 0 ,0
	if (polarMag() == 0)
		return 0;
	else
		return acos(_z / polarMag());
}
