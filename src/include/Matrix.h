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

#ifndef MATRIX_H_
#define MATRIX_H_

#include <Point.h>
#include <Vector.h>

class Matrix {
public:
	Matrix();
	Matrix(unsigned int r, unsigned int c);
	Matrix(const Matrix &m);
	~Matrix();
	Matrix& operator=(const Matrix &m);
	const Matrix operator+(const Matrix &m) const;
	const Matrix operator-(const Matrix &m) const;
	const Matrix operator*(const Matrix &m) const;
	const Point operator*(const Point &m) const;
	const Vector operator*(const Vector &m) const;
	const Matrix operator*(double d) const;
	const Matrix normalize();
	double& operator() (unsigned int row, unsigned int col);
	double operator() (unsigned int row, unsigned int col) const;
private:
	unsigned int _rows;
	unsigned int _cols;
	double _data;
};

#endif /* MATRIX_H_ */
