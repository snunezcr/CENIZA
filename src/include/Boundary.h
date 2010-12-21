/*
 * CENIZA: A multi-model ash dispersion simulation package
 *
 * Copyright (C) Red de Estaciones Meteorologicas 2010
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

#ifndef BOUNDARY_H_
#define BOUNDARY_H_

#include <Point.h>

/*
 * A boundary assumes only two points defining a box. The lower, front left
 * one and the upper, right back one. Directions follow usual right hand rules
 * of Cartesian coordinates.
 */

class Boundary {
public:
	Boundary(Point &llf, Point &urb);
	Boundary(const Boundary &b);
	~Boundary();
	const Point getLLF() const;
	const Point getULF() const;
	const Point getLRF() const;
	const Point getURF() const;
	const Point getLLB() const;
	const Point getULB() const;
	const Point getLRB() const;
	const Point getURB() const;
private:
	Point _llf;			// Lower left front
	Point _urb			// Upper right back
};

#endif /* BOUNDARY_H_ */
