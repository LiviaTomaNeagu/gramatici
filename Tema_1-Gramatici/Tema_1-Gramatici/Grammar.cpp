﻿#include "Grammar.h"

void Grammar::ReadGrammar()
{
	std::ifstream file("file.in");
	if (!file.is_open())
	{
		std::cout << "FILE DID NOT OPEN CORRECTLY!";
		return;
	}
	int nr_Vn, nr_Vt, nr_P;
	file >> nr_Vn;
	m_Vn.resize(nr_Vn);
	for (int i = 0; i < nr_Vn; i++)
	{
		file >> m_Vn[i];
	}
	file >> nr_Vt;
	m_Vt.resize(nr_Vt);
	for (int i = 0; i < nr_Vt; i++)
	{
		file >> m_Vt[i];
	}
	file >> m_S;
	file >> nr_P;
	m_P.resize(nr_P);
	for (int i = 0; i < nr_P; i++)
	{
		file >> m_P[i].first >> m_P[i].second;
	}
	file.close();
}

void Grammar::PrintGrammar()
{
	std::cout << "G = ({";
	for (auto i : m_Vn)
	{
		std::cout << " " << i;
		if (i != m_Vn[m_Vn.size() - 1])
			std::cout << ",";
	}
	std::cout << " }, {";
	for (auto i : m_Vt)
	{
		std::cout << " " << i;
		if (i != m_Vt[m_Vt.size() - 1])
			std::cout << ",";
	}
	std::cout << " }, " << m_S << ", P), where P is:\n";
	for (int i = 0; i < m_P.size(); i++)
	{
		std::cout << i + 1 << ". " << m_P[i].first << " -> " << m_P[i].second << "\n";
	}
}

bool Grammar::VerifyGrammar()
{
	//Rule 1: Intersection needs to be empty.
	std::vector<char> intersection;
	std::sort(m_Vn.begin(), m_Vn.end());
	std::sort(m_Vt.begin(), m_Vt.end());
	std::set_intersection(m_Vn.begin(), m_Vn.begin() + m_Vn.size(), m_Vt.begin(), m_Vt.begin() + m_Vt.size(), std::back_inserter(intersection));
	if (!intersection.empty())
	{
		std::cout << "The intersection is not an empty set!\n";
		return false;
	}

	//Rule 2: Start needs to be an element of Vn.
	if (std::find(m_Vn.begin(), m_Vn.end(), m_S) == m_Vn.end())
	{
		std::cout << "Start is not a member of Vn!\n";
		return false;
	}

	//Rule 3: Left members of the productions need to have at least one element from Vn!
	for (auto i : m_P)
	{
		bool nFound = false;
		for (auto j : m_Vn)
		{
			if (i.first == j)
			{
				nFound = true;
			}
		}
		if (!nFound)
		{
			std::cout << "Invalid productions!\n";
			return false;
		}
	}

	//Rule 4: At least one production has the start as the left member
	bool isStart = false;
	for (auto i : m_P)
	{
		if (i.first == m_S)
		{
			isStart = true;
		}
	}
	if (!isStart)
	{
		std::cout << "There is no production that has only S as a left member.\n";
		return false;
	}

	//Rule 5: Each production contains only elements from Vn and Vt.
	char aux ;
	std::string aux2;
	for (int i = 0; i < m_P.size(); i++)
	{
		aux = m_P[i].first;
		aux2 = m_P[i].second;
		for (auto j : m_Vn)
		{
			if (aux == j)
			{
				aux = '\0';
			}
			RemoveAppearances(aux2, j);
		}
		for (auto j : m_Vt)
		{
			RemoveAppearances(aux2, j);
		}
		if (aux != '\0')
		{
			std::cout << "The productions contain invalid elements!\n";
			return false;
		}
		if (!aux2.empty())
		{
			if (aux2.find('#') != std::string::npos)
			{
				if (m_P[i].second.size() != 1)
				{
					std::cout << "The productions contain invalid elements!\n";
					return false;
				}
			}
			else
			{
				std::cout << "The productions contain invalid elements!\n";
				return false;
			}
		}
	}

	return true;
}


bool Grammar::IsRegular()
{
	for (auto production : m_P)
	{
		char leftSymbol = production.first;
		std::string rightSide = production.second;

		if (rightSide.size() < 1 || rightSide.size() > 2)
		{
			std::cout << "Not regular. Too many/few characters.\n";
			return false;
		}

		if (find(m_Vt.begin(), m_Vt.end(), rightSide[0]) == m_Vt.end())
		{
			std::cout << "Not regular. First character is not in Vt!\n";
			return false;
		}

		if (rightSide.size() == 2 && find(m_Vn.begin(), m_Vn.end(), rightSide[1]) == m_Vn.end())
		{
			std::cout << "Not regular. Second character is not in Vn!\n";
			return false;
		}
	}
	//std::cout << "The grammar is regular.\n";
	return true;
}



std::string Grammar::GenerateWord()
{
	std::string myWord;
	myWord.push_back(m_S);
	std::vector<int> prodVector;
	FindProd(prodVector, myWord);
	ReplaceString(myWord, m_S, m_P[Random(prodVector.size())].second);
	std::cout << m_S << " -> " << myWord;
	while (!AllTerminate(myWord))
	{
		prodVector.clear();
		FindProd(prodVector, myWord);
		if (prodVector.size() == 0)
		{
			std::cout << "\nNo rules to apply in this situation!\n\n";
			return "";
		}
		int randomPosition = Random(prodVector.size());
		ReplaceString(myWord, m_P[prodVector[randomPosition]].first, m_P[prodVector[randomPosition]].second);
		std::cout << " -> " << myWord;
	}
	return myWord;
	return std::string();
}

void Grammar::GenerateNWords(int number)
{
	std::vector <std::string> generatedWordsVector;
	std::string word;
	int generatedWords = 0;
	while (generatedWords != number)
	{
		word = GenerateWord();
		if (word.size() != 0 && (find(generatedWordsVector.begin(), generatedWordsVector.end(), word) == generatedWordsVector.end()))
		{
			std::cout << "\nThe generated word is " << word << ".\n";
			generatedWordsVector.push_back(word);
			generatedWords++;
		}
	}
}

void Grammar::RemoveAppearances(std::string& str, char toFind)
{
	for (int i = 0; i < str.size(); i++)
		if (str[i] == toFind)
			str.erase(str.begin() + i, str.begin() + i + 1);
}

void Grammar::FindProd(std::vector<int>& vectProd, std::string myWord)
{
	//vectProd has the position of the rules that can be applied for myWord.
	for (int i = 0; i < m_P.size(); i++)
	{
		bool canUseRule = false;
		for (int j = 0; j < myWord.size(); j++)
		{
			if (myWord[j] == m_P[i].first)
			{
				canUseRule = true;
			}
		}
		if (canUseRule)
		{
			vectProd.push_back(i);
		}
	}
}

int Grammar::Random(const int& size)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	return distr(eng);
}

bool Grammar::ReplaceString(std::string& myWord, const char& from, const std::string& to)
{
	std::vector<int> positions;
	for (int i = 0; i < myWord.size(); i++)
	{
		if (myWord[i] == from)
		{
			positions.push_back(i);
		}
	}
	int pos = positions[Random(positions.size())];
	myWord.replace(pos, 1, to);
	/*std::string aux = myWord.substr(pos + 1, myWord.size() - pos - 1);
	myWord.erase
	myWord*/
	return false;
}

bool Grammar::AllTerminate(const std::string& myWord) const
{
	for (auto i : myWord)
	{
		if (find(m_Vt.begin(), m_Vt.end(), i) == m_Vt.end())
		{
			return false;
		}
	}
	return true;
}

std::string Grammar::GenerateT()
{
	char T('t');
	while (find(m_Vn.begin(), m_Vn.end(), T) != m_Vn.end())
	{
		T++;
	}
	return std::string(1,T);
}


FiniteAutomaton Grammar::GrammarToAutomaton()
{
	FiniteAutomaton automaton;
	if (!IsRegular())
		return FiniteAutomaton();
	std::string T = GenerateT();

	std::string auxString;
	std::vector<std::string> auxVector;

	automaton.SetInitial(std::string(1, m_S));
	

	for (char character : m_Vn)
	{
		auxVector.push_back(std::string(1, character));
	}
	automaton.SetQ(auxVector);

	std::vector<char> vectorAux;
	for (char character : m_Vt)
	{
		vectorAux.push_back(character);
	}
	automaton.SetSigma(vectorAux);

	automaton.AddFinal(T);

	if (IsLamda())
	{
		automaton.AddFinal(std::string(1, m_S));
	}

	for (auto [net, word] : m_P)
	{
		if (word.size() == 1)
			automaton.SetDelta({ std::string(1,net), word[0] }, T);
		else automaton.SetDelta({ std::string(1, net), word[0] }, std::string(1,word[1]));
	}

	return automaton;

}

bool Grammar::IsLamda()
{
	return !(find(m_Vt.begin(), m_Vt.end(), '#') == m_Vt.end());
}
