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

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
	friend class Point;
public:
	Vector();
	Vector(double x, double y, double z);
	Vector(const Vector &v);
	~Vector();
	double getX() const;
	double getY() const;
	double getZ() const;
	Vector operator=(const Vector &v);
	const Vector operator+(const Vector &v) const;
	const Vector operator-(const Vector &v) const;
	double operator*(const Vector &v) const;
	const Vector operator*(double w) const;
	const Vector normalize() const;
	double polarMag() const;
	double polarPhi() const;
	double polarPsi() const;
private:
	double _x;
	double _y;
	double _z;
};

#endif /* VECTOR_H_ */
