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

#include <DEM.h>

DEM::DEM(const char *filename, bool enabled, Boundary bounds) :
	_triangles(bounds) {
	_filename = filename;
	_enabled  = enabled;
}


DEM::~DEM() {
	delete [] _filename;
}

void DEM::load() {
	if (! _enabled)
		return;

	// TODO: Load a DEM file with appropriate format in Polygon Objects
}

bool DEM::enabled() const {
	return _enabled;
}

Boundary DEM::getBounds() const {
	return _bounds;
}

int DEM::size () const {
	return _triangles.size();
}

Point DEM::sample(Point location) const {
	Point interpolated;

	if (! _enabled)
		return *(new Point(location.getX(), location.getY(), 0));

	// Todo: interpolate with quadtree
	return interpolated;
}

vector<Point> DEM::sample(vector<Point> locations) const {
	vector<Point> points;

	for (unsigned int i = 0; i < locations.size(); i++)
		points.push_back(sample(locations.at(i)));

	return points;
}
