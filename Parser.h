#pragma once

#include <unordered_map>
#include "Variable.cpp"
#include "Lexer.cpp"

using namespace std;

//TODO list:
//	Implement variable assignment
//	Implement variable altering
//	Implement expression handling (boolean, int, and real)

class Parser {
private:

	unordered_map<string, Variable> vars;
	Lexer l;

	//
	// Evaluations
	//

	// Declare a variable
	void decVar(vector<pair<string, tokenType>>& line, TYPE t) {
		if (t == BOOL);
			//bool val = evalBool(vector<pair<string, string>>(line.begin(), line.end()));
	}

	void parseLine(vector<pair<string, tokenType>>& line) {
		
	}

	void parse() {
		vector<pair<string, tokenType>> line;

		for (pair<string, tokenType> lexeme : l.lexemes) {
			// If the current lex is the end of the line, parse the line
			if (lexeme.second == END || OPENCP) {
				parseLine(line);
				line.clear();
			}

			// If no other catches are made, add the lexeme to the current line
			else {
				line.push_back(lexeme);
			}
		}
	}

public:

	Parser(Lexer &lex) {
		l = lex;
	};
};

