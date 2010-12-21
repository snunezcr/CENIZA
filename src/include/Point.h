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

#ifndef POINT_H_
#define POINT_H_

#include <Vector.h>
#include <string>

class Point {
	friend class Vector;
public:
	Point();
	Point(double x, double y, double z);
	Point(const Point &p);
	double getX() const;
	double getY() const;
	double getZ() const;
	~Point();
	Point operator=(const Point &p);
	const Point operator+(const Point &p) const;
	const Point operator-(const Point &p) const;
	double operator*(const Point &p) const;
	const Point operator*(double w) const;
	const Point operator+(const Vector &v) const;
	const Point operator-(const Vector &v) const;
private:
	double _x;
	double _y;
	double _z;
};

#endif /* POINT_H_ */
