#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton()
{
    m_Q = { "q0", "q1", "q2", "q3" };
    m_Sigma = { '0', '1' };
    m_Initial = "q0";
    m_Finals = { "q2" };
    //m_Delta.emplace({ {"qo", '0'}, {"q0"} });
    m_Delta[{"q0", '0'}].push_back("q0");
    m_Delta[{"q0", '1'}].push_back("q0");
    m_Delta[{"q0", '1'}].push_back("q1");
   // m_Delta[{"q1", '0'}].push_back("\0");
    m_Delta[{"q1", '1'}].push_back("q3");
    m_Delta[{"q2", '0'}].push_back("q2");
    m_Delta[{"q2", '1'}].push_back("q3");
    m_Delta[{"q3", '0'}].push_back("q2");
    m_Delta[{"q3", '1'}].push_back("q1");
    m_Delta[{"q3", '1'}].push_back("q2");
}

bool FiniteAutomaton::VerifyAutomaton()
{
    return false;
}

void FiniteAutomaton::PrintAutomaton()
{
}

bool FiniteAutomaton::generate(std::string currentQ, std::string word, std::stack<std::tuple<std::string, std::string, int >>& memoryStack, int index)
{
    while (word.size() > 0) {
        
        auto it = m_Delta.find({ currentQ, word[0] });
        if (it == m_Delta.end())
            return false;
        std::vector<std::string> vectorQ;
        vectorQ = it->second;
        /*if (vectorQ.size() == 0)
            return false;*/
            
        currentQ = vectorQ[index];

        word.erase(word.begin(), word.begin() + 1);
        memoryStack.push({ currentQ, word, 0 });
        index = 0;
    }
    return true;

}

bool FiniteAutomaton::CheckWord(std::string word)
{
    if (IsDeterministic()) {
        std::string currentQ = m_Initial;
        while (word.size() > 0) {
            currentQ = m_Delta.find({ currentQ, word[0] })->second[0];
            word.erase(word.begin(), word.begin() + 1);
        }
        for (auto index : m_Finals)
        {
            if (currentQ == index)
                return true;
        }
        return false;
    }
    else
    {
        bool isFinal = false;
        std::string currentQ = m_Initial;
        std::vector<std::string> vectorQ;
        std::stack<std::tuple<std::string, std::string, int >> memoryStack;
        int index = 0;
        memoryStack.push({ m_Initial, word, 0 });
        generate(currentQ, word, memoryStack, 0);
        while (!isFinal) 
        {
            for (auto index : m_Finals)
            {
                if (std::get<0>(memoryStack.top()) == index && std::get<1>(memoryStack.top()).size() == 0)
                {
                    return true;
                }
            }
            auto it = m_Delta.find(std::make_pair(std::get<0>(memoryStack.top()), std::get<1>(memoryStack.top())[0]));
            if (it == m_Delta.end())
            {
                memoryStack.pop();
                it = m_Delta.find(std::make_pair(std::get<0>(memoryStack.top()), std::get<1>(memoryStack.top())[0]));
            }
            while (it->second.size() - 1 <= std::get<2>(memoryStack.top()))
            {
                   memoryStack.pop();
                   if (memoryStack.empty())
                       return false;
                   it = m_Delta.find(std::make_pair(std::get<0>(memoryStack.top()), std::get<1>(memoryStack.top())[0]));
            }
            std::get<2>(memoryStack.top())++;
            generate(std::get<0>(memoryStack.top()), std::get<1>(memoryStack.top()), memoryStack, std::get<2>(memoryStack.top()));
        } 
        return false;
    }
}

bool FiniteAutomaton::IsDeterministic()
{
    for (const auto& [key, value] : m_Delta)
    {
        if (value.size() != 1)
        {
            return false;
        }
    }
    return true;
}
