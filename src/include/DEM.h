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

#ifndef DEM_H_
#define DEM_H_

#include <Boundary.h>

class DEM {
public:
	DEM(const char *filename);
	~DEM();
	void load();
	Boundary getBounds() const;
private:
	char *_filename;
};

#endif /* DEM_H_ */
