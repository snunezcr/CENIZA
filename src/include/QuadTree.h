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

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <Boundary.h>
#include <vector>
#include <cstdlib>

using namespace std;

template <class T, class S> class QuadTree {
public:
	QuadTree(Boundary &bounds);
	~QuadTree();
	// This is ugly, but required in order to preserve a homogeneous
	// interface for the programmer regardless of class definitions
	void add(T element, Boundary objBounds);
	Boundary getBounds() const;
	int size() const;
	S interpolate(double x, double y) const;
	S closest(double x, double y, double z) const;
private:
	// An inner class will handle the quadtree structure
	class QuadTreeNode {
	public:
		QuadTreeNode(Boundary &bounds);
		~QuadTreeNode();
		bool add(T element, Boundary bounds);
		S interpolate(double x, double y) const;
		S closest(double x, double y, double z) const;
	private:
		// Node data
		T *_data;
		Boundary _bounds;
		double _halfX;
		double _halfY;
		bool _expanded;		// We need to keep track of node expansion
		// Pointers to children nodes
		QuadTreeNode *_lowerLeft;
		QuadTreeNode *_lowerRight;
		QuadTreeNode *_upperLeft;
		QuadTreeNode *_upperRight;
	};


	QuadTreeNode *_root;
	Boundary _bounds;
	int _elements;
};

template <class T, class S>
QuadTree<T,S>::QuadTreeNode::QuadTreeNode(Boundary &bounds) {
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

template <class T, class S>
QuadTree<T,S>::QuadTreeNode::~QuadTreeNode() {
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
bool QuadTree<T,S>::QuadTreeNode::add(T element, Boundary bounds) {
	// First case: we are at the insertion point
	// Status: (not expanded, _data == NULL)
	// Action: copy incoming data to node
	if ( (! _expanded) && (_data == NULL)) {
		_data = new T(element);
		return true;
	}
	// Second case: we are at an insertion point but it is occupied and not expanded
	// Status: no child available, not expanded
	// Action: make all four, relocate current element (possibly more than one node)
	//         and insert new one.
	// TODO
	return false;
}

template <class T, class S>
QuadTree<T,S>::QuadTree(Boundary &bounds) {
	_elements = 0;
	_root = new QuadTreeNode(bounds);
	_bounds = bounds;
}

template <class T, class S>
QuadTree<T,S>::~QuadTree() {
	if (_root != NULL) {
		delete _root;
		_root = NULL;
	}
}

template <class T, class S>
void QuadTree<T,S>::add(T element, Boundary objBounds) {
	if (_root->add(element, objBounds))
		_elements++;

	return;
}

template <class T, class S>
Boundary QuadTree<T,S>::getBounds() const {
	return _bounds;
}

template <class T, class S>
int QuadTree<T,S>::size() const {
	return _elements;
}

template <class T, class S>
S QuadTree<T,S>::interpolate(double x, double y) const {
	return _root->interpolate(x, y);
}

template <class T, class S>
S QuadTree<T,S>::closest(double x, double y, double z) const {
	return _root->closest(x, y, z);
}

#endif /* QUADTREE_H_ */
