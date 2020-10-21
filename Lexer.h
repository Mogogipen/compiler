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
	DIGIT,
	SYMBOL
};

enum tokenType {
	ID,
	NUMBER,
	OP,
	STRING,
	KEYWORD,
	END
};

class Lexer
{
private:
	unordered_map<char, charType> alphabet;
public:

	Lexer() {
		
		// Input alphabet file
		string alphabetFileName = "alphabets.txt";
		ifstream alphaIn(alphabetFileName, ifstream::in);
		if (!alphaIn) {
			cout << "Invalid alphabet file";
			return;
		}

		// Build the alphabet
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
		while (b = alphaIn.get()) {
			if (b == '\n' || alphaIn.eof())
				break;
			alphabet[b] = SYMBOL;
		}

		unordered_map<char, charType>::iterator it;
		while (it != alphabet.end()) {
			cout << it->first;
			it++;
		}

	}
};

