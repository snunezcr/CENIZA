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

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
	friend class Point;
public:
	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector &v);
	~Vector();
	double getX() const;
	double getY() const;
	double getZ() const;
	Vector operator=(const Vector &v);
	const Vector operator+(const Vector &v) const;
	const Vector operator-(const Vector &v) const;
	double operator*(const Vector &v) const;
	const Vector operator*(double w) const;
	const Vector normalize() const;
	double polarMag() const;
	double polarPhi() const;
	double polarPsi() const;
private:
	double _x;
	double _y;
	double _z;
};

#endif /* VECTOR_H_ */
