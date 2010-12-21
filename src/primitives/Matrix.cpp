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

#include <Matrix.h>
#include <OutOfBoundsException.h>
#include <cstring>

Matrix::Matrix() {
	// By default we create a 3x3 zero matrix
	_rows = 3;
	_cols = 3;
	_data = new double[_rows * _cols];

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_data[ i * _cols + j] = 0;
}

Matrix::Matrix(unsigned int r, unsigned int c) {
	if (r == 0 || c == 0) {
		_rows = 3;
		_cols = 3;
	} else {
		_rows = r;
		_cols = c;
	}
	_data = new double[_rows * _cols];

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			_data[ i * _cols + j] = 0;
}

Matrix::Matrix(const Matrix &m) {
	_rows = m._rows;
	_cols = m._cols;

	_data = new double[_rows * _cols];
	memcpy(_data, m._data, _rows * _cols * sizeof(double));
}

Matrix::~Matrix() {
	if (_data != NULL)
		delete _data;

	_data == NULL;
}

Matrix Matrix::operator=(const Matrix &m) {
	_rows = m._rows;
	_cols = m._cols;

	if (_data != NULL)
		delete _data;

	_data = new double[_rows * _cols];
	memcpy(_data, m._data, _rows * _cols * sizeof(double));
}

const Matrix Matrix::operator+(const Matrix &m) const {
	if ( (_rows != m._rows ) || (_cols != m._cols ) )
		return *(new Matrix());

	Matrix n(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			n._data[ i * _cols + j] += m._data[ i * _cols + j];

	return n;
}

const Matrix Matrix::operator-(const Matrix &m) const {
	if ( (_rows != m._rows ) || (_cols != m._cols ) )
		return *(new Matrix());

	Matrix n(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			n._data[ i * _cols + j] -= m._data[ i * _cols + j];

	return n;
}

const Matrix Matrix::operator*(const Matrix &m) const {
	Matrix n(_rows, m._cols);

	for (int i = 0; i < _rows; i++)
			for (int j = 0; j < m._cols; j++)
				for (int k = 0; k < m._rows; k++)
					n._data[ i * _cols + j] +=
							_data[ i * _cols + k] * m._data[ k * _cols + j];

	return n;
}

const Point Matrix::operator*(const Point &p) const {
	// This operation assumes a 3x3 matrix
	if ( (_rows != 3 ) || (_cols != 3 ) )
		return *(new Point(0, 0, 0));

	Point p1 (_data[0], _data[1], _data[2]);
	Point p2 (_data[3], _data[4], _data[5]);
	Point p3 (_data[6], _data[7], _data[8]);

	Point q(p1 * p, p2 * p, p3 * p);

	return q;
}

const Vector Matrix::operator*(const Vector &v) const {
	// This operation assumes a 3x3 matrix
	if ( (_rows != 3 ) || (_cols != 3 ) )
		return *(new Vector(0, 0, 0));

	Vector v1 (_data[0], _data[1], _data[2]);
	Vector v2 (_data[3], _data[4], _data[5]);
	Vector v3 (_data[6], _data[7], _data[8]);

	Vector w(v1 * v, v2 * v, v3 * v);

	return w;
}

const Matrix Matrix::operator*(double d) const {
	Matrix n(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			n._data[i * _cols + j] *= d;

	return n;
}

double& Matrix::operator() (unsigned int row, unsigned int col) {
	if ( (row >= _rows) || (col >= _cols) )
		throw OutOfBoundsException();

	return _data[row * _cols + col];
}

double Matrix::operator() (unsigned int row, unsigned int col) const {
	if ( (row >= _rows) || (col >= _cols) )
		throw OutOfBoundsException();

	return _data[row * _cols + col];
}
