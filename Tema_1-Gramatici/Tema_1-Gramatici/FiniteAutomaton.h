#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

class FiniteAutomaton
{
private:
	std::vector<std::string> m_Q;
	std::vector<char> m_Sigma;
	std::map<std::pair<std::string, char>, std::vector<std::string>> m_Delta;
	std::string m_Initial;
	std::vector<std::string> m_Finals;

public:
	FiniteAutomaton() {};
	bool VerifyAutomaton();
	void PrintAutomaton();
	bool CheckWord();
	bool IsDeterministic();

};

