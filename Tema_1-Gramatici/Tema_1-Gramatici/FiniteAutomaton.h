#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<tuple>
#include<stack>

class FiniteAutomaton
{
private:
	std::vector<std::string> m_Q;
	std::vector<char> m_Sigma;
	std::map<std::pair<std::string, char>, std::vector<std::string>> m_Delta;
	std::string m_Initial;
	std::vector<std::string> m_Finals;

public:
	FiniteAutomaton();
	bool VerifyAutomaton();
	void PrintAutomaton();
	bool CheckWord(std::string word);
	bool IsDeterministic();
	bool generate(std::string, std::string, std::stack<std::tuple<std::string, std::string, int >>&, int);
	
	//setteri
	void SetInitial(const std::string&);
	void SetQ(const std::vector<std::string>&);
	void SetDelta(const std::pair<std::string, char>&, const std::string&);

	//getteri

};

