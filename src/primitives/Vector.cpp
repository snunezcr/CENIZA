/*
 * CENIZA: A multi-model ash dispersion simulation package
 *
 * Copyright (C) Red Ciudadana de Estaciones Meteorologicas 2010
 * Author: Santiago Nunez Corrales <snunezcr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

const Vector Vector::operator*(double w) const {
	Vector v(_x * w, _y * w, _z * w);
	return v;
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
