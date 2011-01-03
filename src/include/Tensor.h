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
