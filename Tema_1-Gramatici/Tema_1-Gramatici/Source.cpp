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
	grammar.PrintGrammar();
	//if (grammar.VerifyGrammar())
	//{
	//	//grammar.PrintGrammar();
	//	//grammar.GenerateWord();
	//}
	FiniteAutomaton automat(grammar.GrammarToAutomaton());
	automat.PrintAutomaton();
	//std::cout << automat.VerifyAutomaton();
	//std::cout << automat.CheckWord("1010");
}