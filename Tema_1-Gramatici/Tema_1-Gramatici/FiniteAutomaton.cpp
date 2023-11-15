#include "FiniteAutomaton.h"

bool FiniteAutomaton::VerifyAutomaton()
{
    return false;
}

void FiniteAutomaton::PrintAutomaton()
{
}

bool FiniteAutomaton::CheckWord()
{
    return false;
}

bool FiniteAutomaton::IsDeterministic()
{
    for (auto& [key, value] : m_Delta)
    {
        if (value.size() != 1)
        {
            return false;
        }
    }
    return true;
}
