#include"FiniteAutomaton.h"
#include"Grammar.h"


void PrintMenu()
{
	std::cout << "Choose one option:\n\n";
	std::cout << "(a) print grammar G";
}

int main()
{
	Grammar grammar;
	grammar.ReadGrammar();
	if(grammar.VerifyGrammar())
		grammar.PrintGrammar();
}