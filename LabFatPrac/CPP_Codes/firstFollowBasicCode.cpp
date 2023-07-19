/*
    Author: Sai Sreekar
    Created: 2023/07/19 00:04:02
    Last Modified: 2023/07/19 11:38:37
*/

#include <bits/stdc++.h>

using namespace std;

unordered_map<char, vector<string>> productionRules;
unordered_map<char, unordered_set<char>> firstSets;
unordered_map<char, unordered_set<char>> followSets;
void computeFirstSets(char nonTerminal)
{
    vector<string> productions = productionRules[nonTerminal];
    for (int i = 0; i < productions.size(); i++)
    {
        char symbol = productions[i][0];
        if (symbol == nonTerminal)
        {
            continue;
        }
        if (!isupper(symbol))
        {
            firstSets[nonTerminal].insert(symbol);
        }
        else
        {
            computeFirstSets(symbol);
            for (char firstSymbol : firstSets[symbol])
            {
                firstSets[nonTerminal].insert(firstSymbol);
            }
        }
    }
}
void computeFollowSets(char nonTerminal)
{
    for (auto const &rule : productionRules)
    {
        char leftSymbol = rule.first;
        vector<string> productions = rule.second;
        for (string production : productions)
        {
            size_t pos = production.find(nonTerminal);
            if (pos != string::npos)
            {
                if (pos + 1 < production.length())
                {
                    char nextSymbol = production[pos + 1];
                    if (!isupper(nextSymbol))
                    {
                        followSets[nonTerminal].insert(nextSymbol);
                    }
                    else
                    {
                        for (char firstSymbol : firstSets[nextSymbol])
                        {
                            followSets[nonTerminal].insert(firstSymbol);
                        }
                    }
                }

                else
                {
                    if (nonTerminal != leftSymbol)
                    {
                        computeFollowSets(leftSymbol);
                        for (char followSymbol : followSets[leftSymbol])
                        {
                            followSets[nonTerminal].insert(followSymbol);
                        }
                    }
                }
            }
        }
    }
}
bool isLL1Grammar()
{
    for (auto const &rule : productionRules)
    {
        char nonTerminal = rule.first;
        vector<string> productions = rule.second;
        for (size_t i = 0; i < productions.size(); i++)
        {
            string production = productions[i];
            for (size_t j = i + 1; j < productions.size(); j++)
            {
                string nextProduction = productions[j];
                unordered_set<char> firstSet1 = firstSets[nonTerminal];
                unordered_set<char> firstSet2 = firstSets[nextProduction[0]];
                for (char terminal : firstSet1)
                {
                    if (firstSet2.find(terminal) != firstSet2.end())
                    {
                        cout << "Grammar is not LL(1) due to common terminals in First sets." << endl;
                        return false;
                    }
                }
            }
            for (char terminal : followSets[nonTerminal])

            {
                if (firstSets[nonTerminal].find(terminal) != firstSets[nonTerminal].end())
                {
                    cout << "Grammar is not LL(1) due to terminals in Follow sets." << endl;
                    return false;
                }
            }
        }
    }
    cout << "Grammar is LL(1)." << endl;
    return true;
}
int main()
{
    int numProductions;
    cout << "Enter the number of productions: ";
    cin >> numProductions;
    cout << "Enter the grammar productions in the form 'NonTerminal -> Production': " << endl;
    for (int i = 0; i < numProductions; i++)
    {
        char nonTerminal;
        string production;
        cin >> nonTerminal;
        cin >> production;
        productionRules[nonTerminal].push_back(production);
        // cout << nonTerminal << " " << production << "\n";
    }

    for (auto const &rule : productionRules)
    {
        char nonTerminal = rule.first;
        computeFirstSets(nonTerminal);
    }

    followSets['S'].insert('$');

    for (auto const &rule : productionRules)
    {
        char nonTerminal = rule.first;
        computeFollowSets(nonTerminal);
    }

    // print first sets
    cout << "First sets: " << endl;
    for (auto const &rule : productionRules)
    {
        char c = rule.first;
        cout << "First(" << c << ") = { ";
        for (char symbol : firstSets[c])
        {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
    // print follow sets
    cout << "Follow sets: " << endl;
    for (auto const &rule : productionRules)
    {
        char c = rule.first;
        cout << "Follow(" << c << ") = { ";
        for (char symbol : followSets[c])
        {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }

    // bool isLL1 = isLL1Grammar();
    // if (isLL1)

    // {
    //     cout << "The given grammar is LL(1)." << endl;
    // }
    // else
    // {
    //     cout << "The given grammar is not LL(1)." << endl;
    // }
    return 0;
}