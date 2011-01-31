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

template <class T, class S> class QuadTree {
public:
	QuadTree(Boundary bounds);
	~QuadTree();
	void add(vector<T> elements);
	// This is ugly, but required in order to preserve a homogeneous
	// interface for the programmer regardless of class definitions
	void add(T element, Boundary objBounds);
	Boundary getBounds() const;
	S interpolate(double x, double y) const;
private:
	// An inner class will handle the quadtree structure
	class QuadTreeNode {
	public:
		QuadTreeNode(Boundary bounds);
		~QuadTreeNode();
		void add(T element, Boundary bounds);
		S interpolate(double x, double y) const;
	private:
		// Node data
		T *_data;
		Boundary _bounds;
		double _halfX;
		double _halfY;
		bool _expanded;		// We need to keep track of node expansion
		// Pointers to children nodes
		QuadTreeNode *lowerLeft;
		QuadTreeNode *lowerRight;
		QuadTreeNode *upperLeft;
		QuadTreeNode *upperRight;
	};


	QuadTreeNode *_root;
	Boundary _bounds;
	int _elements;
};

#endif /* QUADTREE_H_ */
