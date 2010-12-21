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

#ifndef TENSOR_H_
#define TENSOR_H_

#include <Point.h>
#include <Vector.h>
#include <Matrix.h>

class Tensor {
public:
	Tensor();
	Tensor(unsigned int dims, unsigned int *lens);
	Tensor(const Tensor &t);
	~Tensor();
	Tensor operator=(const Tensor &m);
	const Tensor operator+(const Tensor &m) const;
	const Tensor operator-(const Tensor &m) const;
	const Tensor operator*(const Tensor &m) const;
	const Tensor operator*(const Matrix &m) const;
	const Tensor operator*(double d) const;
	const Tensor normalize();
	double& operator() (unsigned int index, ...);
	double operator() (unsigned int index, ...) const;
private:
	unsigned int _dims;
	unsigned int *_lens;
	double *_data;
};

#endif /* TENSOR_H_ */
