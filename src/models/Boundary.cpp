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

/* Logica:
 *
 * U/L = x
 * L/R = y
 * F/B = z
 */

#include <Boundary.cpp>

Boundary::Boundary(Point &llf, Point &urb) {
	_llf = llf;
	_urb = urb;
}

Boundary::Boundary(const Boundary &b) {
	if (&b != this) {
		_llf = b._llf;
		_urb = b._urb;
	}
}

Boundary::~Boundary() {
	return;
}

const Point Boundary::getLLF() const {
	return _llf;
}

const Point Boundary::getULF() const {
	Point p(_urb.getX(), _llf.getY(), _llf.getZ());
	return p;
}

const Point Boundary::getLRF() const {
	Point p(_llf.getX(), _urb.getY(), _llf.getZ());
	return p;
}

const Point Boundary::getURF() const {
	Point p(_urb.getX(), _urb.getY(), _llf.getZ());
	return p;
}

const Point Boundary::getLLB() const {
	Point p(_llf.getX(), _llf.getY(), _urb.getZ());
	return p;
}

const Point Boundary::getULB() const {
	Point p(_urb.getX(), _llf.getY(), _urb.getZ());
	return p;
}

const Point Boundary::getLRB() const {
	Point p(_llf.getX(), _urb.getY(), _urb.getZ());
	return p;
}

const Point Boundary::getURB() const {
	return _urb;
}
