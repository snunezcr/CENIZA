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

#ifndef GRID_H_
#define GRID_H_

#include <Boundary.h>
#include <Location.h>
#include <DEM.h>
#include <vector>

enum {
	GRID_SIMPLE,
	GRID_QUAD,
	GRID_OCTA,
	GRID_NONE
};

using namespace std;

template <typename D> class Grid {
public:
	Grid(Boundary bounds, DEM *elevations);
	~Grid();
	virtual bool empty() const;
	virtual bool member(Location<D> location) const;
	virtual int size() const;
	virtual int type() const;
	virtual void add(Location<D> location);
	virtual void add(vector< Location<D> > locations);
	virtual Location<D> & next() const;
	virtual void refine();
	virtual bool changed() const;
protected:
	bool _changed;
	int _type;
	Boundary _bounds;
	DEM *_elevations;
};

template <typename D>
Grid<D>::Grid(Boundary bounds, DEM *elevations) {
	_changed = false;
	_bounds = bounds;
	_elevations = elevations;
	_type = GRID_NONE;
}

template <typename D>
Grid<D>::~Grid() {

}

template <typename D>
bool Grid<D>::empty() const {
	return true;
}

template <typename D>
bool Grid<D>::member(Location<D> location) const {
	return false;
}

template <typename D>
int Grid<D>::size() const {
	return 0;
}

template <typename D>
int Grid<D>::type() const {
	return _type;
}

template <typename D>
void Grid<D>::add(Location<D> location) {

}

template <typename D>
void Grid<D>::add(vector< Location<D> > locations) {

}

template <typename D>
Location<D> & Grid<D>::next() const {
	return *(new Location<D>());
}

template <typename D> void Grid<D>::refine() {

}

template <typename D> bool Grid<D>::changed() const {
	return false;
}

#endif /* GRID_H_ */
