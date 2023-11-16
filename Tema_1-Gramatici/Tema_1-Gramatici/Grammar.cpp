#include "Grammar.h"

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
				nFound = true;
		}
		if (!nFound)
		{
			std::cout << "Invalid productions!\n";
			return false;
		}
	}

	//Rule 4: At least one prod. has the start as the left member
	bool isStart = false;
	for (auto i : m_P)
	{
		if (i.first == m_S)
			isStart = true;
	}
	if (!isStart)
	{
		std::cout << "There is no production that has only S as a left member.\n";
		return false;
	}

	//Rule 5: Each production contains onyl elements from Vn and Vt.
	char aux ;
	std::string aux2;
	for (int i=0;i<m_P.size();i++)
	{
		aux = m_P[i].first;
		aux2 = m_P[i].second;
		for (auto j : m_Vn)
		{
			if (aux == j)
				aux= '\0';
			RemoveAppearances(aux2, j);
		}
		for (auto j : m_Vt)
		{
			RemoveAppearances(aux2, j);
		}
		if (aux != '\0' ||  !aux2.empty())
		{
			std::cout << "The productions contain invalid elements!\n";
			return false;
		}
	}

	//std::cout << "Everything ok!\n";
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
			std::cout << "Not regular. Too many/few characters.";
			return false;
		}

		if (find(m_Vt.begin(), m_Vt.end(), rightSide[0]) == m_Vt.end())
		{
			std::cout << "Not regular. First character is not in VT!";
			return false;
		}

		if (rightSide.size() == 2 && find(m_Vn.begin(), m_Vn.end(), rightSide[1]) == m_Vn.end())
		{
			std::cout << "Not regular. Second character is not in VN!";
			return false;
		}
	}
	std::cout << "The grammar is regular.\n";
	return true;
}



std::string Grammar::GenerateWord()
{
	std::string myWord;
	myWord.push_back(m_S);
	std::vector<int> prodVector;
	findProd(prodVector, myWord);
	replaceStr(myWord, m_S, m_P[random(prodVector.size())].second);
	std::cout << m_S << " -> " << myWord;
	while (!AllTerminate(myWord))
	{
		prodVector.clear();
		findProd(prodVector, myWord);
		if (prodVector.size() == 0)
		{
			std::cout << "\nNo rules to apply in this situation!\n\n";
			return "";
		}
		int randomPosition = random(prodVector.size());
		replaceStr(myWord, m_P[prodVector[randomPosition]].first, m_P[prodVector[randomPosition]].second);
		std::cout << " -> " << myWord;
	}
	return myWord;
	return std::string();
}

void Grammar::RemoveAppearances(std::string& str, char toFind)
{
	for (int i = 0; i < str.size(); i++)
		if (str[i] == toFind)
			str.erase(str.begin() + i, str.begin() + i + 1);
}

void Grammar::findProd(std::vector<int>& vectProd, std::string myWord)
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

int Grammar::random(const int& size)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	return distr(eng);
}

bool Grammar::replaceStr(std::string& myWord, const char& from, const std::string& to)
{
	std::vector<int> positions;
	for (int i = 0; i < myWord.size(); i++)
	{
		if (myWord[i] == from)
		{
			positions.push_back(i);
		}
	}
	int pos = positions[random(positions.size())];
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

std::string Grammar::generateT()
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
	std::string T = generateT();

	std::string auxString;
	std::vector<std::string> auxVector;

	automaton.SetInitial(std::string(1, m_S));

	for (char character : m_Vn)
	{
		auxVector.push_back(std::string(1, character));
	}
	automaton.SetQ(auxVector);

	automaton.addFinal(T);

	if (IsLamda())
		automaton.addFinal(std::string(1, m_S));


	for (auto [net, word] : m_P)
	{
		if (word.size() == 1)
			automaton.SetDelta({ std::string(1,net), word[0] }, T);
		else automaton.SetDelta({ std::string(1, net), word[0] }, std::string(1,word[1]));
	}


}

bool Grammar::IsLamda()
{
	return !(find(m_Vt.begin(), m_Vt.end(), '#') == m_Vt.end());
}
