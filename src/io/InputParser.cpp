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

#include <cmath>
#include <stdlib.h>
#include <InputParser.h>

using namespace std;

InputParser::InputParser(const string &file) : vars(NULL), secs(NULL),
	_fileName(file), _loaded(false) {
}

InputParser::~InputParser() {
	if (vars != NULL)
		delete static_cast<VariableSet *>(vars);

	if (secs != NULL)
		delete static_cast<StringSet *>(secs);
}

string InputParser::preprocess(fstream &input) {
	string tmp;
	string line;

	while (getline(input, line, '\n')) {
		line = line.substr(0, line.find("//"));

		for (string::iterator i = line.begin(); i != line.end(); i++) {
			switch (*i) {
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				break;
			default:
				tmp.append(*i);
			}
		}
	}

	return tmp;
}

bool InputParser::precargar(fstream &input) {
	static string buffer;
	string tmp;
	int scope = 0;
	tmp = preprocess(input);
	iterador i = tmp.inicio();
	string tempName;
	string tempVal;
	string currSection;

find_name:
	if (i == tmp.final())
		goto end;

	switch (*i) {
		case '{':
			if ((static_cast<StringSet *>(secs))->insert(tempName).second == false) {
				(static_cast<StringSet *>(secs))->clear();
				(static_cast<VariableSet *>(vars))->clear();
				return false;
			}
			currSection = tempName;
			tempName.resize(0);
			goto in_section;
		break;
		default:
		tempName.append(&*i, 1);
	}
	i++;
	goto find_name;

in_section:
	if (i == tmp.final()) {
		(static_cast<StringSet *>(secs))->clear();
		(static_cast<VariableSet *>(vars))->clear();
		return false;
	}
	switch(*i) {
		case '{':
			scope++;
			break;
		case '}':
			scope--;
			if (scope == 0) {
				i++;
				currSection.resize(0);
				goto find_name;
			}
			break;
		default:
			goto var_name;
	}
	i++;
	goto in_section;

var_name:
	if (i == tmp.final()) {
		(static_cast<StringSet *>(secs))->clear();
		(static_cast<VariableSet *>(vars))->clear();
		return false;
	}
	switch(*i) {
		case '{':
			goto in_section;
		case '}':
			(static_cast<StringSet *>(secs))->clear();
			(static_cast<VariableSet *>(vars))->clear();
			return false;
		case '=':
			if (tempName.vacia()) {
				(static_cast<StringSet *>(secs))->clear();
				(static_cast<VariableSet *>(vars))->clear();
			return false;
			}
			i++;
			goto var_value;
		default:
			tempName.append(&*i, 1);
		break;
	}
	i++;
	goto var_name;

var_value:
	if (i == tmp.final()) {
		(static_cast<StringSet *>(secs))->clear();
		(static_cast<VariableSet *>(vars))->clear();
		return false;
	}
	switch(*i) {
		case '{':
			(static_cast<StringSet *>(secs))->clear();
			(static_cast<VariableSet *>(vars))->clear();
			return false;
		case '}':
			(static_cast<StringSet *>(secs))->clear();
			(static_cast<VariableSet *>(vars))->clear();
			return false;
		case ';':
			if (tempName.vacia()) {
				(static_cast<StringSet *>(secs))->clear();
				(static_cast<VariableSet *>(vars))->clear();
				return false;
			}
			buffer.assign(currSection);
			buffer.append('/');
			buffer.append(tempName);
			(static_cast<VariableSet *>(vars))->insert(VariableSet::value_type(buffer, tempVal));
			tempName.resize(0);
			tempVal.resize(0);
			i++;
			goto in_section;
		default:
		tempVal.append(i, 1);
		break;
	}
	i++;
	goto var_value;
end:
	return true;
}

bool InputParser::loadBool(const string &name, bool defval) const {
	static string nombreBool;
	nombreBool.assign(_localSection).append(name);
	VariableSet::const_iterator i =
			static_cast<VariableSet *>((VariableSet *)vars)->find(nombreBool);

	if (i != ((VariableSet *)vars)->end())
		return (*i).second.compare("true") == 0;
	else
		return defval;
}

double InputParser::loadDouble(const string &name, double defval) const {
	static string floatName;
	floatName.assign(_localSection).append(name);
	VariableSet::const_iterator i =
			static_cast<VariableSet *>((VariableSet *)vars)->find(floatName);

	if (i != ((VariableSet *)vars)->end())
		return atof((*i).second.cString());
	else
		return defval;
}

const string & InputParser::loadString(const string &name, const string &defval) const {
	static string stringName;
	stringName.assign(_localSection).append(name);
	VariableSet::const_iterator i =
		static_cast<VariableSet *>((VariableSet *)vars)->find(stringName);

	if (i != ((VariableSet *)vars)->end())
		return (*i).second;
	else
		return defval;
}

long InputParser::loadInt(const string &name, long defval) const {
	static string longName;
	longName.assign(_localSection).append(name);
	VariableSet::const_iterator i =
			static_cast<VariableSet *>((VariableSet *)vars)->find(longName);

	if (i != ((VariableSet *)vars)->end())
		return atol((*i).second.cString());
	else
		return defval;
}

Vector InputParser::loadVector(const string &name, const Vector &defval) const {
	Vector v;
	static string vectorName;
	vectorName.assign(_localSection).append(name);
	VariableSet::const_iterator i =
			static_cast<VariableSet *>((VariableSet *)vars)->find(vectorName);
	if (i != ((VariableSet *)vars)->end()) {
		int readup = sscanf(i->second.cString(), "%f, %f, %f", &v.x, &v.y, &v.z);

		if (readup != 3)
		return defval;

		return v;
	} else {
		return defval;
	}
}

Point InputParser::loadPoint(const string &name, const Point &defval) const {
	Point p;
	static string pointName;
	pointName.assign(_localSection).append(name);
	VariableSet::const_iterator i =
	static_cast<VariableSet *>((VariableSet *)vars)->find(pointName);
	if (i != ((VariableSet *)vars)->end()) {
		int readup = sscanf(i->second.cString(), "%f, %f, %f", &p.x, &p.y, &p.z);

		if (readup != 3)
			return defval;

		return p;
	} else {
		return defval;
	}
}

int InputParser::setSection(const string &s) {
	if (! _loaded) {
		_loaded = true;
		vars = new VariableSet();
		secs = new StringSet;
		fstream input;
		bool result;

		input.open(_fileName.cString(), ios::in);

		if (input.is_open() == 0) {
			result = false;
		} else {
			result = precargar(input);
			input.close();
		}

		if (! result) {
			delete static_cast<VariableSet *>(vars);
			vars = NULL;

			delete static_cast<StringSet *>(secs);
			secs = NULL;

			return -1;
		}
	}

	if (vars == NULL)
	return -1;

	StringSet::const_iterator i = ((StringSet *) secs)->find(s);

	if (i != ((StringSet *) secs)->end()) {
		_localSection.assign(s).append('/');
		return 0;
	} else {
		_localSection.resize(0);
		return -1;
	}
}

