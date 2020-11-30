#pragma once

#include <unordered_map>
#include "Variable.cpp"

class Parser {
private:

	unordered_map<string, TYPE> variableTypes;
	unordered_map<string, bool> booleanVars;
	//TODO list:
	//	Implement variable assignment
	//	Implement variable altering
	//	Implement expression handling (boolean, int, and real)
};

