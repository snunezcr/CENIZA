/*
 * InputParser.h
 *
 *  Created on: Jan 25, 2011
 *      Author: snunez
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

typedef std::map<String,String> VariableSet;
typedef std::set<String> StringsSet;

class InputParser {
public:
	InputParser();
	InputParser(const string &file);
	~InputParser();
	bool loadBool(const string &name, bool defval) const;
	double loadDouble(const string &name, double defval) const;
	const string &loadString(const string &name, const String &defval) const;
	long loadInt(const string &name, long defval) const;
	Vector loadVector(const string &name, const Vector &defval) const;
	Punto loadPoint(const string &name, const Point &defval) const;
	int setSection(const string &s);
private:
	void *vars;
	void *sects;
	string _fileName;
	string _localSection;
	bool _loaded;
	string preprocess(fstream &input);
	bool preload(fstream &input);
};

#endif /* INPUTPARSER_H_ */
