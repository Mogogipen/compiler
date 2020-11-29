// compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Lexer.cpp"
#include "Parser.cpp"

using namespace std;

int main()
{
    Lexer l;
    bool proceed = l.lex("sampleCode.txt");
	
	// Uncomment to print the lexeme table
	//if (proceed) {
	//	for (pair<string, string> t : l.lexemes) {
	//		cout << "Lexeme: " << t.first << "\t\t";
	//		cout << "Token: " << t.second;
	//		if (t.second == "KEYWORD")
	//			cout << " | " << "Description: " << l.KEYWORDS[t.first];
	//		cout << '\n';
	//	}
	//}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
