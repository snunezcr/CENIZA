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

#ifndef INPUTPARSER_H_
#define INPUTPARSER_H_

#include <fstream>
#include <map>
#include <set>
#include <Point.h>
#include <Vector.h>
#include <string>

using namespace std;

typedef std::map<string,string> VariableSet;
typedef std::set<string> StringSet;

class InputParser {
public:
	InputParser();
	InputParser(const string &file);
	~InputParser();
	bool loadBool(const string &name, bool defval) const;
	double loadDouble(const string &name, double defval) const;
	const string &loadString(const string &name, const string &defval) const;
	long loadInt(const string &name, long defval) const;
	Vector loadVector(const string &name, const Vector &defval) const;
	Point loadPoint(const string &name, const Point &defval) const;
	int setSection(const string &s);
private:
	void *vars;
	void *secs;
	string _fileName;
	string _localSection;
	bool _loaded;
	string preprocess(fstream &input);
	bool preload(fstream &input);
};

#endif /* INPUTPARSER_H_ */
