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
	QuadTree(Boundary &bounds, int maxSize);
	~QuadTree();
	// This is ugly, but required in order to preserve a homogeneous
	// interface for the programmer regardless of class definitions
	void add(const T element);
	Boundary getBounds() const;
	int size() const;
	S interpolate(double x, double y) const;
	S closest(double x, double y, double z) const;
private:
	// An inner class will handle the quadtree structure
	class QuadTreeNode {
	public:
		QuadTreeNode(Boundary &bounds, int maxSize);
		~QuadTreeNode();
		bool add(const T element);
		S interpolate(double x, double y) const;
		S closest(double x, double y, double z) const;
	private:
		// Node data
		vector<T> _data;
		Boundary _bounds;
		double _halfX;
		double _halfY;
		bool _expanded;
		unsigned int _maxSize;
		// Pointers to children nodes
		QuadTreeNode *_lowerLeft;
		QuadTreeNode *_lowerRight;
		QuadTreeNode *_upperLeft;
		QuadTreeNode *_upperRight;
		// Helper function for adding in bounds
		bool addInBounds(const T element);
		bool addSingleBound(const T element, const Point &p);
	};


	QuadTreeNode *_root;
	Boundary _bounds;
	int _elements;
	unsigned  int _maxSize;
};

template <class T, class S>
QuadTree<T,S>::QuadTreeNode::QuadTreeNode(Boundary &bounds, int maxSize) {
	_bounds = bounds;
	_halfX = (_bounds.getURB().getX() - _bounds.getLLF().getX()) / 2;
	_halfY = (_bounds.getURB().getY() - _bounds.getLLF().getY()) / 2;
	_expanded = false;
	_lowerLeft = NULL;
	_lowerRight = NULL;
	_upperLeft = NULL;
	_upperRight = NULL;
	_maxSize = maxSize;
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
	if (_data.size() != 0) {
		_data.clear();
	}
}

template <class T, class S>
bool QuadTree<T,S>::QuadTreeNode::add(const T element) {
	if (_data.size() < _maxSize) {
		// First case: we are at the insertion point
		// Status: (not expanded, _data with space)
		// Action: copy incoming data to node

		// Do not allow duplicates
		for (unsigned int i = 0; i < _maxSize; i++) {
			if (_data.at(i) == element)
				return false;
		}

		_data.push_back(element);
		return true;
	} else if ((_data.size() == _maxSize) && (! _expanded)) {
		// Second case: we are at an insertion point but it is occupied and not expanded
		// Status: no child available, not expanded
		// Action: make all four, relocate current element (possibly more than one node)
		//         and insert new one.

		// Calculate all bounds
		Point midLeft(_bounds.getLLF().getX(), _halfY, 0);
		Point midRight(_bounds.getURF().getX(), _halfY, 0);
		Point midUpper(_halfX, _bounds.getURF().getY(), 0);
		Point midLower(_halfX, _bounds.getLRF().getY(), 0);
		Point midSpace(_halfX, _halfY, 0);
		Point upRight = _bounds.getURF();
		Point lowLeft = _bounds.getLLF();

		Boundary ur(midSpace, upRight);
		Boundary ul(midLeft, midUpper);
		Boundary lr(midLower, midRight);
		Boundary ll(lowLeft, midSpace);

		// Create new nodes
		_upperRight = new QuadTreeNode(ur, _maxSize);
		_upperLeft = new QuadTreeNode(ul, _maxSize);
		_lowerRight = new QuadTreeNode(lr, _maxSize);
		_lowerLeft = new QuadTreeNode(ll, _maxSize);

		// For each existing object, remove from current vector
		// and reinsert in corresponding places
		for (unsigned int i = 0; i < _maxSize; i++)
			addInBounds(_data.at(i));

		// Empty current data
		_data.clear();

		// Expand node
		_expanded = true;

		// Finally, add the element
		return addInBounds(element);
	} else {
		// Third case: we are at the insertion point
		// Status: (expanded)
		// Action: find nodes where bounds belong
		return addInBounds(element);
	}
}

template <class T, class S>
bool QuadTree<T,S>::QuadTreeNode::addInBounds(const T element) {
	Boundary region = element.bound();
	bool added = false;

	// For each point in the boundary of the object, add element
	added |= addSingleBounds(element, region.getURB());
	added |= addSingleBounds(element, region.getULB());
	added |= addSingleBounds(element, region.getLRB());
	added |= addSingleBounds(element, region.getLLB());

	return added;
}

template <class T, class S>
bool QuadTree<T,S>::QuadTreeNode::addSingleBound(const T element, const Point &p) {
	if (p.getX() > _halfX && p.getY() > _halfY)
		return _upperRight->add(element, element.bound());
	else if (p.getX() <= _halfX && p.getY() > _halfY)
		return _upperLeft->add(element, element.bound());
	else if (p.getX() > _halfX && p.getY() <= _halfY)
		return _lowerRight->add(element, element.bound());
	else
		return _lowerLeft->add(element, element.bound());
}

template <class T, class S>
QuadTree<T,S>::QuadTree(Boundary &bounds, int maxSize) {
	_elements = 0;
	_root = new QuadTreeNode(bounds, maxSize);
	_bounds = bounds;
	_maxSize = maxSize;
}

template <class T, class S>
QuadTree<T,S>::~QuadTree() {
	if (_root != NULL) {
		delete _root;
		_root = NULL;
	}
}

template <class T, class S>
void QuadTree<T,S>::add(const T element) {
	if (_root->add(element))
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
