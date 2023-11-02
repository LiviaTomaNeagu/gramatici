#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

class Grammar
{
private:
	std::vector<char> m_Vn, m_Vt;
	std::vector<std::string, std::string> m_P;
	char m_S;
public:
	Grammar() {};
	bool VerifyGrammar();
	bool IsRegular();
	std::string GenerateWord();
	void PrintGrammar();
	void ReadGrammar();

	
};

