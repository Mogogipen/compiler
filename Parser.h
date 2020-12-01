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

	unordered_map<string, vector<tokenType>> expectations {
		{"int", {ID}},
		{"char", {ID}},
		{"real", {ID}},
		{"bool", {ID}},
		{"string", {ID}},
		{"true", {}},
		{"false", {}},
		{"const", {KEYWORD}},
		{"while", {OPENP, EXP, CLOSEP}},
		{"do", {}},
		{"if", {OPENP, EXP, CLOSEP}},
		{"elif", {OPENP, EXP, CLOSEP}},
		{"else", {}},
		{"print", {EXP}},
		{"start", {OPENP}},
		{"return", {}},
		{"break", {END}},
		{"continue", {END}}
	};

	unordered_map<string, Variable> vars;
	Lexer l;
	bool inBody;

	// Declare a variable
	void decVar(vector<pair<string, tokenType>>& line, TYPE t) {
		
	}

	void parseLine(vector<pair<string, tokenType>>& line) {
		
	}

	void parse() {
		vector<pair<string, tokenType>> line;

		for (int i = 0; i < l.lexemes.size(); i++) {
			pair<string, tokenType>& lexeme = l.lexemes[i];
			// If the first lexeme is a keyword:
			if (lexeme.second == KEYWORD) {

			}
			// elif statement parsing
			// else statement parsing
			// while statement parsing
			// print parsing
			// return, break, continue parsing
			// declaration parsing

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

