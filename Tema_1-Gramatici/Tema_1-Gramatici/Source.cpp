#include"FiniteAutomaton.h"
#include"Grammar.h"


void PrintMenu()
{
	std::cout << "Choose one option:\n\n";
	std::cout << "(a) print grammar G.\n";
	std::cout << "(b) generate N words in the grammar G.\n";
	std::cout << "(c) get the automaton from the grammar G.\n";
	std::cout << "(d) verify whether a word is accepted by the automaton or not.\n";
	std::cout << "(e) generate a word in the grammar G and verify if the word is accepted by the automaton.\n";
}

int main()
{
	Grammar grammar;
	grammar.ReadGrammar();
	//grammar.PrintGrammar();
	if (grammar.VerifyGrammar() && grammar.IsRegular())
	{
		std::cout << "This is an accurate and regular grammar.\n";
		PrintMenu();

		//declarations of variables
		char menu;
		int number;
		FiniteAutomaton automat(grammar.GrammarToAutomaton());
		std::string word;

		//Menu start
		std::cin >> menu;
		switch (menu)
		{
		case 'a':
			//print grammar G
			grammar.PrintGrammar();
			break;
		case 'b':
			//generate N words in the grammar G
			std::cout << "The number of generated words is: ";
			std::cin >> number;
			grammar.GenerateNWords(number);
			break;
		case 'c':
			//get the automaton from the grammar G
			automat.PrintAutomaton();
			break;
		case 'd':
			//verify whether a word is accepted by the automaton or not
			std::cout << "The word to be verified is: ";
			std::cin >> word;
			if (automat.CheckWord(word))
				std::cout << "\nThis word is accepted by the automaton.\n";
			else std::cout << "\nThis word is not accepted by the automaton.\n";
			break;
		case 'e':
			//generate a word in the grammar G and verify if the word is accepted by the automaton
			word = grammar.GenerateWord();
			if (automat.CheckWord(word))
				std::cout << "\nThis word is accepted by the automaton.\n";
			else std::cout << "\nThis word is not accepted by the automaton.\n";
			break;
		default:
			std::cout << "Invalid option!";
			break;
		}
	}


	//de verificat un cuvant fals
	//de verificat automatul? unde? 
	
}