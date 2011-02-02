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

#ifndef MODEL_H_
#define MODEL_H_

#include <Parameter.h>
#include <Boundary.h>
#include <Field.h>
#include <Grid.h>
#include <DEM.h>
#include <vector>

using namespace std;

template <typename D> class Model {
public:
	Model(char *filename, bool den, Boundary bounds, vector<Parameter> params);
	~Model();
	virtual void clear();
	virtual void run();
	virtual void save();
protected:
	Field _field;
	Grid<D> *_grid;
	DEM _dem;
	vector<Parameter> _params;
};

template <typename D>
Model::Model(Boundary bounds, char *filename, bool den, vector<Parameter> params) :
	_field(bounds), _dem(filename, den, bounds) {
	// Set the grid to null since there is not enough information to create one
	_grid = NULL;

	for (unsigned int i = 0; i < params.size(); i++)
		_params.push_back(params.at(i));
}

template <typename D>
Model::~Model() {
	if (_grid != NULL) {
		delete _grid;
		_grid = NULL;
	}
}

template <typename D>
void Model::clear() {
	return;
}

template <typename D>
void Model::run() {
	return;
}

template <typename D>
void Model::save() {
	return;
}

#endif /* MODEL_H_ */
