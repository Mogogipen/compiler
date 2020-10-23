#pragma once

#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Lexer
{
private:

	vector<string> charTypes {
		"LETTER",
		"DIGIT",
		"OTHER"
	};

	vector<string> tokenTypes {
		"STRING",
		"NUMBER",
		"ID",
		"OP",
		"KEYWORD",
		"ASSIGNMENT",
		"OPENP",
		"CLOSEP",
		"OPENCP",
		"CLOSECP",
		"END"
	};

	unordered_map<char, string> alphabet;
	unordered_map<string, string> specialTokens = { // Will also contain operators and keywords
		{"=", "ASSIGNMENT"},
		{"(", "OPENP"},
		{")", "CLOSEP"},
		{"{", "OPENCP"},
		{"}", "CLOSECP"},
		{";", "END"}
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

public:

	pair<bool, string> matchTokenType(string s) {
		pair<bool, string> result = {false, ""};
		// Check for spaces
		if (s.find(' ') >= 0 || s.find('\n') >= 0 || s.find('\t') >= 0)
			cout << "Parse error";
		// Special tokens check
		else if ((result.second = specialTokens[s]) != "") {
			result.first = true;
		}
		// ID tokens check
		else if (alphabet[s[0]] == "LETTER") {
			bool valid = true;
			for (char c : s) {
				if (alphabet[c] == "") {
					valid = false;
					break;
				}
			}
			if (valid)
				result = {true, "ID"};
		}
		// NUMBER tokens check
		else if (alphabet[s[0]] == "DIGIT") {
			bool valid = true;
			for (char c : s) {
				if (alphabet[c] != "DIGIT") {
					valid = false;
					break;
				}
			}
			if (valid)
				result = { true, "NUMBER" };
		}
		return result;
	}

	void lex(string filename) {
		vector<pair<string, string>> lexemes;

		// Load file
		ifstream inf(filename, ifstream::in);
		if (!inf) {
			cout << "Invalid input file";
			return;
		}

		//
		// Parse file
		//
		while (!inf.eof()) {
			char next = inf.get();
			string currentLex;
			// If a "#" is encountered, skip to next line
			if (next == '#') {
				while (inf.get() != '\n') {

				}
			}
			// If whitespace is encountered, skip it
			else if (next == ' ' || next == '\n' || next == '\t');
			// If a "\"" is encountered, add everything to a string type until another "\"" is encountered
			else if (next == '"') {
				next = inf.get();
				while (next != '"' && !inf.eof()) {
					if (next == '\t');
					else
						currentLex.append(1, next);
					next = inf.get();
				}
				lexemes.push_back({ currentLex, "STRING" });
			}
			// Every other token
			else {
				string oldLex = currentLex;
				currentLex.append(1, next);
				pair<bool, string> matches = matchTokenType(currentLex);
			}
		}
		//
		//
		//

		// Output lexemes to command line
		for (pair<string, string> t : lexemes) {
			cout << "Lexeme: " << t.first << "\t\t";
			cout << "Token: " << t.second;
			if (t.second == "KEYWORD")
				cout << " | " << "Description: " << KEYWORDS[t.first];
			cout << '\n';
		}
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
			alphabet[b] = "LETTER";
		}
		while (b = alphaIn.get()) {
			if (b == '\n')
				break;
			alphabet[b] = "DIGIT";
		}
		alphabet['_'] = "OTHER";

		// Hash the operator tokens frome the file
		while (b = alphaIn.get()) {
			if (b == '\n' || alphaIn.eof())
				break;
			string s(1, b);
			specialTokens[s] = "OP";
		}

		alphaIn.close();

		// Hash the key word tokens
		vector<pair<string, string>> keywords;
		copy(KEYWORDS.begin(), KEYWORDS.end(), back_inserter(keywords));
		for (int i = 0; i < keywords.size(); i++) {
			specialTokens[keywords[i].first] = "KEYWORD";
		}
	}

};

