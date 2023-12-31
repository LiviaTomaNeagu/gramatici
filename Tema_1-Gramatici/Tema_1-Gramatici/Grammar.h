#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<fstream>
#include<string>
#include"FiniteAutomaton.h"

class Grammar
{
private:
	std::vector<char> m_Vn, m_Vt;
	std::vector<std::pair<char, std::string>> m_P;
	char m_S;
public:
	Grammar() {};
	void ReadGrammar();
	void PrintGrammar();
	bool VerifyGrammar();
	bool IsRegular();
	std::string GenerateWord();
	void GenerateNWords(int n);
	FiniteAutomaton GrammarToAutomaton();
private:
	void RemoveAppearances(std::string& str, char toFind);
	void FindProd(std::vector<int>& vectProd, std::string myWord);
	int Random(const int& size);
	bool ReplaceString(std::string& myWord, const char& from, const std::string& to);
	bool AllTerminate(const std::string& myWord) const;
	std::string GenerateT();
	bool IsLamda();
};

