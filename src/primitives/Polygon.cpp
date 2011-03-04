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

inline double maxCoord(double a, double b, double c) {
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

inline double minCoord(double a, double b, double c) {
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

#include <Polygon.h>
#include <Matrix.h>

// In this class, we use the idea of polygon as

Polygon::Polygon() {
	_elements = 0;
}

Polygon::Polygon(const Polygon &g) {
	if (&g != this) {
		_lines = g._lines;
		_elements = _elements;
	}
}

Polygon::~Polygon() {
}

Polygon& Polygon::add(const Line &l) {
	// Check we have not already added the line
	for (unsigned int i = 0; i < _lines.size(); i++) {
		if (((Line)_lines[i]) == l) {
			continue;
		} else {
			_lines.push_back(l);
		}
	}

	return *this;
}

const Point Polygon::interpolateHeight(double x, double y) const {
	Point s1(x, y, 1);
	Point s0(x, y, 0);
	Point s(x, y, -1);		// -1 represents an error

	// We will always assume that points in a polygon make a triangle
	// and are connected in sequence.
	int numLines = 3;
	Point p[numLines];

	// Test in case we are in a vertex and fill them while testing
	for (int i = 0; i < numLines; i++) {
		p[i] = ((Line)_lines.at(i)).getStart();
		if ( p[i].getX() == x && p[i].getY() == y)
			return p[i];
	}

	// Otherwise, compute the intersection with the plane and test
	Point a = s0 - p[0];
	Point c0 = s0 - s1;
	Point c1 = p[1] - p[0];
	Point c2 = p[2] - p[0];
	Matrix m;

	m(0,0) = c0.getX(); m(1,0) = c0.getY(); m(2,0) = c0.getZ();
	m(0,1) = c1.getX(); m(1,1) = c1.getY(); m(2,1) = c1.getZ();
	m(0,2) = c2.getX(); m(1,2) = c2.getY(); m(2,2) = c2.getZ();

	// Solve the system M^-1 A - S, test invertibility first
	if (m.det() == 0)
		return s;

	// From the matrix operation, a vector representing an orientation of
	// lengths is found and analyzed
	Point factors = (m.inv()) * a;

	// Test if we are in the triangular region
	if ((factors.getY() < 0) || (factors.getZ() < 0) ||
		(factors.getY() > 1) || (factors.getZ() > 1) ||
		((factors.getY() + factors.getZ()) > 1))
		return s;

	s = s0 + ((s1 - s0) * factors.getX());

	return s;
}

Boundary Polygon::bound() const {
	Point llf(minCoord(_lines.at(0).getStart().getX(),
					_lines.at(1).getStart().getX(),
					_lines.at(2).getStart().getX()),
			minCoord(_lines.at(0).getStart().getY(),
					_lines.at(1).getStart().getY(),
					_lines.at(2).getStart().getY()),
			minCoord(_lines.at(0).getStart().getZ(),
					_lines.at(1).getStart().getZ(),
					_lines.at(2).getStart().getZ()));
	Point urb(maxCoord(_lines.at(0).getStart().getX(),
					_lines.at(1).getStart().getX(),
					_lines.at(2).getStart().getX()),
			maxCoord(_lines.at(0).getStart().getY(),
					_lines.at(1).getStart().getY(),
					_lines.at(2).getStart().getY()),
			maxCoord(_lines.at(0).getStart().getZ(),
					_lines.at(1).getStart().getZ(),
					_lines.at(2).getStart().getZ()));

	Boundary bounds(llf, urb);

	return bounds;
}
