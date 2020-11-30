#pragma once

#include <string>

using namespace std;

enum TYPE {
	boolean,
	real,
	inte,
	chara
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
	Variable(string n, bool v) : Variable(TYPE::boolean, n, v) {};
	Variable(string n, int v) : Variable(TYPE::inte, n, v) {};
	Variable(string n, char v) : Variable(TYPE::chara, n, v) {};
	Variable(string n, double r) : Variable(TYPE::real, n, 0, r) {};

	TYPE getType() {
		return type;
	}

	string getName() {
		return name;
	}

	int getValue() {
		if (type == boolean)
			return (val != 0);
		else {
			return val;
		}
	}

	double getRVal() {
		return rVal;
	}
};

