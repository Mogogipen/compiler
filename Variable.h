#pragma once

#include <string>

using namespace std;

enum TYPE {
	BOOL,
	REAL,
	INT,
	CHAR
};

class Variable
{
private:
	TYPE type;
	string name;
	int val;
	double rVal;

public:
	Variable(TYPE t, string n, int v = 0, double r = 0.0) : type(t), name(n), val(v), rVal(r) {};
	Variable(string n, bool v) : Variable(TYPE::BOOL, n, v) {};
	Variable(string n, int v) : Variable(TYPE::INT, n, v) {};
	Variable(string n, char v) : Variable(TYPE::CHAR, n, v) {};
	Variable(string n, double r) : Variable(TYPE::REAL, n, 0, r) {};

	TYPE getType() {
		return type;
	}

	string getName() {
		return name;
	}

	int getValue() {
		if (type == BOOL)
			return (val != 0);
		else {
			return val;
		}
	}

	double getRVal() {
		return rVal;
	}
};

