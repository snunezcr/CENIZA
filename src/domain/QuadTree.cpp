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

#include <QuadTree.h>
#include <cstdlib>

template <class T, class S>
	QuadTree<T,S>::QuadTreeNode::QuadTreeNode(Boundary bounds) {
	_data = NULL;
	_bounds = bounds;
	_halfX = (_bounds.getURB().getX() - _bounds.getLLF().getX()) / 2;
	_halfY = (_bounds.getURB().getY() - _bounds.getLLF().getY()) / 2;
	_expanded = false;
	_lowerLeft = NULL;
	_lowerRight = NULL;
	_upperLeft = NULL;
	_upperRight = NULL;
}

template <class T, class S> QuadTree<T,S>::QuadTreeNode::~QuadTreeNode() {
	if (_lowerLeft != NULL) {
		delete _lowerLeft;
		_lowerLeft = NULL;
	}
	if (_lowerRight != NULL) {
		delete _lowerRight;
		_lowerRight = NULL;
	}
	if (_upperLeft != NULL) {
		delete _upperLeft;
		_upperLeft = NULL;
	}
	if (_upperRight != NULL) {
		delete _upperRight;
		_upperRight = NULL;
	}
	if (_data != NULL) {
		delete _data;
		_data = NULL;
	}
}

template <class T, class S>
void QuadTree<T,S>::QuadTreeNode::add(T element, Boundary bounds) {
	// First case: we are at the insertion point
	// Status: (not expanded, _data == NULL)
	// Action: copy incoming data to node
	if ( (! _expanded) && (_data == NULL)) {
		_data = new T(element);
		return;
	}
}

template <class T, class S> QuadTree<T,S>::QuadTree(Boundary bounds) {
	_elements = 0;
	_root = new QuadTreeNode(bounds);
	_bounds = bounds;
}

template <class T, class S> QuadTree<T,S>::~QuadTree() {
	if (_root != NULL) {
		delete _root;
		_root = NULL;
	}
}

template <class T, class S> void QuadTree<T,S>::add(T element, Boundary objBounds) {
	_root.add(element, objBounds);
}

template <class T, class S> Boundary QuadTree<T,S>::getBounds() const {
	return _bounds;
}

template <class T, class S> S QuadTree<T,S>::interpolate(double x, double y) const {
	return _root.interpolate(x, y);
}
