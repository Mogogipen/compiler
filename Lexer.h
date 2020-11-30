#pragma once

#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

enum tokenType {
	UT,
	STRING,
	NUMBER,
	ID,
	OP,
	KEYWORD,
	ASSIGNMENT,
	OPENP,
	CLOSEP,
	OPENCP,
	CLOSECP,
	END
};

class Lexer
{
private:

	enum charType {
		UC,
		LETTER,
		DIGIT,
		OTHER
	};

public:

	unordered_map<char, charType> alphabet;
	unordered_map<string, tokenType> specialTokens = { // Will also contain operators and keywords
		{"=", ASSIGNMENT},
		{"++", OP},
		{"--", OP},
		{"(", OPENP},
		{")", CLOSEP},
		{"{", OPENCP},
		{"}", CLOSECP},
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
		{"continue", "Jumps to the beginning of the loop"}
	};

	vector<pair<string, tokenType>> lexemes;

private:

	vector<string> unrecognizedSymbols = {};

	// Primary method for identifying "all other tokens"
	pair<bool, tokenType> matchTokenType(string s) {
		pair<bool, tokenType> result = {false, UT};
		// Special tokens check
		if ((result.second = specialTokens[s]) != UC) {
			result.first = true;
		}
		// ID tokens check
		else if (alphabet[s[0]] == LETTER) {
			bool valid = true;
			for (char c : s) {
				if (alphabet[c] == UC) {
					valid = false;
					break;
				}
			}
			if (valid)
				result = {true, ID};
		}
		// NUMBER tokens check
		else if (alphabet[s[0]] == DIGIT) {
			bool valid = true;
			for (char c : s) {
				if (alphabet[c] != DIGIT) {
					valid = false;
					break;
				}
			}
			if (valid)
				result = { true, NUMBER };
		}
		else if (s.size() == 1) {
			for (string t : unrecognizedSymbols) {
				if (s == t)
					return result;
			}
			unrecognizedSymbols.push_back(s);
		}
		return result;
	}

	bool isWhiteSpace(char c) {
		return (c == ' ' || c == '\t' || c == '\n');
	}

public:

	bool lex(string filename) {

		// Load file
		ifstream inf(filename, ifstream::in);
		if (!inf) {
			cout << "Invalid input file";
			return NULL;
		}

		//
		// Parse file
		//
		char old = 0;
		while (!inf.eof()) {
			char next;
			if (old == 0) {
				next = inf.get();
			}
			else {
				next = old;
				old = 0;
			}
			string currentLex;
			// If a "#" is encountered, skip to next line
			if (next == '#') {
				while (inf.get() != '\n' && !inf.eof()) {

				}
			}
			// If whitespace is encountered, skip it
			else if (isWhiteSpace(next));
			// If a "\"" is encountered, add everything to a string type until another "\"" is encountered
			else if (next == '"') {
				next = inf.get();
				while (next != '"' && !inf.eof()) {
					if (next == '\t');
					else
						currentLex.append(1, next);
					next = inf.get();
				}
				lexemes.push_back({ currentLex, STRING });
			}
			// Every other token
			else {
				string oldLex;
				pair<bool, tokenType> match = { false, UT };
				do {
					oldLex = currentLex;
					if (inf.eof()) {
						break;
					}
					currentLex += next;
					match = matchTokenType(currentLex);
					if (match.first || (!match.first && currentLex.size() == 1))
						next = inf.get();
				} while (match.first);
				old = next;
				match = matchTokenType(oldLex);
				if (match.first)
					lexemes.push_back({ oldLex, match.second });
			}
		}
		//
		//
		//

		// Output error for unrecognized symbols
		if (unrecognizedSymbols.size() > 0) {
			cerr << "Unrecognized Symbol: " << unrecognizedSymbols[0];
			return false;
		}
		// Return symbol table if no errors encountered
		else {
			return true;
		}
	}

	void printLexTable() {
		for (pair<string, tokenType> t : lexemes) {
			cout << "Lexeme: " << t.first << "\t\t";
			cout << "Token: " << tokenTypeAsString(t.second);
			if (t.second == KEYWORD)
				cout << " | " << "Description: " << KEYWORDS[t.first];
			cout << '\n';
		}
	}

	string tokenTypeAsString(tokenType t) {
		if (t == STRING) return "STRING";
		if (t == NUMBER) return "NUMBER";
		if (t == ID) return "ID";
		if (t == OP) return "OP";
		if (t == KEYWORD) return "KEYWORD";
		if (t == ASSIGNMENT) return "ASSIGNMENT";
		if (t == OPENP) return "OPENP";
		if (t == CLOSEP) return "CLOSEP";
		if (t == OPENCP) return "OPENCP";
		if (t == CLOSECP) return "CLOSECP";
		if (t == END) return "END";
		return "ERROR";
	}

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
		alphabet['_'] = OTHER;

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

};

