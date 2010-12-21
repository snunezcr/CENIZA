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

#ifndef POLYGON_H_
#define POLYGON_H_

#include <Point.h>
#include <Vector.h>
#include <Line.h>
#include <vector>

class Polygon {
public:
	Polygon();
	Polygon(const Polygon &g);
	~Polygon();
	Polygon& add(const Line &l);
	Polygon operator^(const Polygon &g) const;		// Intersection
	Polygon operator+(const Polygon &g) const;		// Union
	Polygon operator-(const Polygon &g) const;		// Difference
	Point interpolate(double x, double y) const;	// Calculate height at x, y
private:
	vector<Line> _lines;
	unsigned int _elements;
};

#endif /* POLYGON_H_ */
