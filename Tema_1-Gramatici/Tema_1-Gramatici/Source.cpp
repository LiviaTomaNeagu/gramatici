#include"FiniteAutomaton.h"
#include"Grammar.h"

void PrintMenu()
{
	std::cout << "\nChoose one option:\n";
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

	if (grammar.VerifyGrammar() && grammar.IsRegular())
	{
		std::cout << "This is an accurate and regular grammar.\n";

		//declarations of variables
		char menu;
		int number;
		FiniteAutomaton automat;
		std::string word;
		bool moreOptions = true;

		//Start loop for menu
		while (moreOptions)
		{
			PrintMenu();

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
				automat = grammar.GrammarToAutomaton();
				if (automat.VerifyAutomaton())
				{
					automat.PrintAutomaton();
				}
				else std::cout << "This is not a valid automaton.\n";
				break;

			case 'd':
				//verify whether a word is accepted by the automaton or not
				automat = grammar.GrammarToAutomaton();
				std::cout << "The word to be verified is: ";
				std::cin >> word;
				if (automat.CheckWord(word))
					std::cout << "\nThis word is accepted by the automaton.\n";
				else std::cout << "\nThis word is not accepted by the automaton.\n";
				break;

			case 'e':
				//generate a word in the grammar G and verify if the word is accepted by the automaton
				word = grammar.GenerateWord();
				automat = grammar.GrammarToAutomaton();
				if (automat.CheckWord(word))
					std::cout << "\nThis word is accepted by the automaton.\n";
				else std::cout << "\nThis word is not accepted by the automaton.\n";
				break;

			default:
				std::cout << "Invalid option!";
				break;
			}

			std::cout << "\nDo you want to choose another option?\n";
			std::string option;
			std::cin >> option;
			if (option == "no")
			{
				moreOptions = false;
			}
			std::cout << "\n";
		}
	}
}