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

	for (unsigned int i = 0; i < _rows; i++)
		for (unsigned int j = 0; j < _cols; j++)
			n._data[ i * _cols + j] += m._data[ i * _cols + j];

	return n;
}

const Matrix Matrix::operator-(const Matrix &m) const {
	if ( (_rows != m._rows ) || (_cols != m._cols ) )
		return *(new Matrix());

	Matrix n(*this);

	for (unsigned int i = 0; i < _rows; i++)
		for (unsigned int j = 0; j < _cols; j++)
			n._data[ i * _cols + j] -= m._data[ i * _cols + j];

	return n;
}

const Matrix Matrix::operator*(const Matrix &m) const {
	Matrix n(_rows, m._cols);

	for (unsigned int i = 0; i < _rows; i++)
			for (unsigned int j = 0; j < m._cols; j++)
				for (unsigned int k = 0; k < m._rows; k++)
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

	for (unsigned int i = 0; i < _rows; i++)
		for (unsigned int j = 0; j < _cols; j++)
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


double Matrix::det() const {
	// Only for 3x3 matrices, signal non invertible otherwise
	if (_rows != 3 || _cols != 3)
		return 0;

	double det = 0;

	// Follow traditional diagonal algorithm, use direct access
	// in order to avoid method call
	det += _data[0]*_data[4]*_data[8];
	det += _data[1]*_data[5]*_data[6];
	det += _data[2]*_data[3]*_data[7];
	det -= _data[6]*_data[4]*_data[2];
	det -= _data[7]*_data[5]*_data[0];
	det -= _data[8]*_data[3]*_data[1];

	return det;
}

const Matrix Matrix::inv() const {
	Matrix n;
	double d = det();

	if (d == 0)
		return n;

	if (_cols != 3 || _rows != 3)
		return n;

	// Calculate the transpose
	Matrix t = this->transp();
	// Build the matrix of cofactors
	n(0,0) = t(1, 1)*t(2, 2) - t(2, 1)*t(1, 2);
	n(0,1) = t(1, 0)*t(2, 2) - t(2, 0)*t(1, 2);
	n(0,2) = t(1, 0)*t(2, 1) - t(2, 0)*t(1, 1);
	n(1,0) = t(0, 1)*t(2, 2) - t(2, 1)*t(0, 2);
	n(1,1) = t(0, 0)*t(2, 2) - t(2, 0)*t(0, 2);
	n(1,2) = t(0, 0)*t(2, 1) - t(2, 0)*t(0, 1);
	n(2,0) = t(0, 1)*t(1, 2) - t(1, 1)*t(0, 2);
	n(2,1) = t(0, 0)*t(1, 2) - t(1, 0)*t(0, 2);
	n(2,2) = t(0, 0)*t(1, 1) - t(1, 0)*t(0, 1);

	// Multiply by determinant and change sign
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			if ((i + j)% 2 == 0)
				n._data[i * _cols + j] *= 1/d;
			else
				n._data[i * _cols + j] *= -1/d;

	return n;
}

const Matrix Matrix::transp() const {
	// Reuse a copy of itself
	Matrix n(_cols, _rows);

	for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				n._data[j * _rows + i] = _data[i * _cols + j];

	return n;
}
