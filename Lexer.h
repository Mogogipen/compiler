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

		unsigned char b;
		while (b = alphaIn.get()) {
			if (alphaIn.eof())
				break;
			if (b == '\n')
				break;
		}

	}
};

