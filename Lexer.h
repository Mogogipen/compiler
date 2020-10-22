#pragma once

#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

enum charType {
	LETTER,
	DIGIT
};

enum tokenType {
	COMMENT,
	ID,
	NUMBER,
	OP,
	ASSIGNMENT,
	STRING,
	KEYWORD,
	END
};

class Lexer
{
private:

	unordered_map<char, charType> alphabet;
	unordered_map<string, tokenType> specialTokens = {
		{"#", COMMENT},
		{"=", ASSIGNMENT},
		{";", END}
	};
	unordered_map<string, string> KEYWORDS = {
		{"int", "Integer value"},
		{"char", "Character value"},
		{"real", "Real value (otherwise floating point)"},
		{"bool", "Boolean value"},
		{"true", "True boolean value"},
		{"false", "False boolean value"},
		{"const", "Constant declaration"},
		{"while", "While loop statement"},
		{"do", "Do while loop statement"},
		{"if", "If statement"},
		{"elif", "Else-if statement"},
		{"else", "Else statement"},
		{"print", "Print statement"},
		{"start", "Special function to mark execution beginning"},
		{"return", "Return statement"},
		{"break", "Jumps to the end of the loop"},
		{"continue", "Jumps to the beginning of the loop"},
		{"new", "Declares a new variable"}
	};

public:

	Lexer() {
		
		// Open input alphabet file
		string alphabetFileName = "alphabets.txt";
		ifstream alphaIn(alphabetFileName, ifstream::in);
		if (!alphaIn) {
			cout << "Invalid alphabet file";
			return;
		}

		// Hash the alphabet from the file
		char b;
		while (b = alphaIn.get()) {
			if (b == '\n')
				break;
			alphabet[b] = LETTER;
		}
		while (b = alphaIn.get()) {
			if (b == '\n')
				break;
			alphabet[b] = DIGIT;
		}

		// Hash the operator tokens frome the file
		while (b = alphaIn.get()) {
			if (b == '\n' || alphaIn.eof())
				break;
			string s(1, b);
			specialTokens[s] = OP;
		}

		alphaIn.close();

		// Hash the key word tokens
		vector<pair<string, string>> keywords;
		copy(KEYWORDS.begin(), KEYWORDS.end(), back_inserter(keywords));
		for (int i = 0; i < keywords.size(); i++) {
			specialTokens[keywords[i].first] = KEYWORD;
		}
	}

	void lex(string filename) {
		vector<pair<string, tokenType>> tokens;
		
	}

};

