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
