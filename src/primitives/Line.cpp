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

#include <Line.h>

Line::Line(const Point &start, const Point &end) {
	_start  = start;
	_end = end;
}

Line::Line(const Line &l) {
	if (&l == this)
		return;

	_start = l._start;
	_end = l._end;
}

Line::~Line() {
}

bool operator==(const Line &l) const {
	if (_start == l._start && _end == l._end)
		return true;
	else
		return false;
}

Line Line::operator=(const Line &l) {
	if (&l != this) {
		_start = l._start;
		_end = l._end;
	}

	return *this;
}

const Line Line::operator+(const Point &p) const {
	Line m(_start, _end);
	m._start = _start + p;
	m._end = _end + p;
	return m;
}

const Line Line::operator-(const Point &p) const {
	Line m(_start, _end);
	m._start = _start - p;
	m._end = _end - p;
	return m;
}

const Line Line::operator*(double w) const {
	Line m(_start, _end);
	m._start = _start * w;
	m._end = _end * w;
	return m;
}

bool Line::hasPoint(const Point &p) const {
	if (_start == p || _end == p)
		return true;
	else {
		if (1) {

		} else {
			return false;
		}
	}
}
