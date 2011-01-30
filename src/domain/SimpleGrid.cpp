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

#include <SimpleGrid.h>


// Precondition:
//
// _m, _n > 2
template <typename D> SimpleGrid<D>::SimpleGrid(Boundary bounds, DEM *elevations,
		int m, int n) : Grid<D>(bounds, elevations) {
	_m = m;
	_n = n;
	_deltaX = (Grid<D>::_bounds.getURB().getX() -
				Grid<D>::_bounds.getLLF().getX()) / (_m - 1);
	_deltaY = (Grid<D>::_bounds.getURB().getY() -
					Grid<D>::_bounds.getLLF().getY()) / (_m - 1);
}

template <typename D> SimpleGrid<D>::~SimpleGrid() {

}

template <typename D> bool SimpleGrid<D>::empty() const {
	return _locations.empty();
}

template <typename D> bool SimpleGrid<D>::member(Location<D> location) const {
	for (unsigned int i = 0; i < _locations.size(); i++)
		if (_locations.at(i) == location)
			return true;

	return false;
}

template <typename D> int SimpleGrid<D>::size() const {
	return _locations.size();
}

template <typename D> void SimpleGrid<D>::add(Location<D> location) {
	if (! member(location))
		_locations.push_back(location);

	return;
}

template <typename D> void SimpleGrid<D>::add(vector< Location<D> > locations) {
	for (unsigned int i = 0; i < locations.size(); i++)
		add(locations.at(i));

	return;
}

template <typename D> Location<D> & SimpleGrid<D>::next() const {
	int curr = _current;
	_current = (_current + 1) % _locations.size();

	if (! _locations.empty())
		return _locations.at(curr);
	else
		return *(new Location<D>());
}

template <typename D> void SimpleGrid<D>::refine() {
	// The simplest for of grid will not have refinement
	return;
}

template <typename D> bool SimpleGrid<D>::changed() const {
	// The simplest form of grid never changes
	return false;
}
