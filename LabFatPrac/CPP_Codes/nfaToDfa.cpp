#include <bits/stdc++.h>
using namespace std;

int main()
{
    int noOfStates, noOfSymbols;
    cout << "Enter the number of states: ";
    cin >> noOfStates;
    cout << "Enter the number of symbols: ";
    cin >> noOfSymbols;
    vector<vector<vector<char>>> nfa(noOfStates, vector<vector<char>>(noOfSymbols));
    cout << "Enter the NFA: \n";
    for (int i = 0; i < noOfStates; i++)
    {
        for (int j = 0; j < noOfSymbols; j++)
        {
            int c = 0;
            cout << "Enter the number of states for " << (char)('A' + i) << " on " << (char)('a' + j) << " : ";
            cin >> c;
            cout << "Enter the states: ";
            for (int k = 0; k < c; k++)
            {
                char temp;
                cin >> temp;
                nfa[i][j].push_back(temp);
            }
        }
    }

    // cout << "The NFA is: \n";
    // for (int i = 0; i < noOfStates; i++)
    // {
    //     for (int j = 0; j < noOfSymbols; j++)
    //     {
    //         cout << "State " << i << " on " << j << " : ";
    //         for (int k = 0; k < nfa[i][j].size(); k++)
    //         {
    //             cout << nfa[i][j][k] << " ";
    //         }
    //         cout << "\n";
    //     }
    // }

    // nfa to dfa
    vector<string> dfaStates;
    vector<vector<vector<char>>> dfa;
    dfaStates.push_back("A");
    dfa.push_back(nfa[0]);

    for (int i = 0; i < dfa.size(); i++)
    {
        for (int j = 0; j < noOfSymbols; j++)
        {
            sort(dfa[i][j].begin(), dfa[i][j].end());
            string temp = "";
            for (int k = 0; k < dfa[i][j].size(); k++)
            {
                temp += dfa[i][j][k];
            }
            if (find(dfaStates.begin(), dfaStates.end(), temp) == dfaStates.end())
            {
                dfaStates.push_back(temp);
                vector<vector<char>> temp2;
                for (int k = 0; k < noOfSymbols; k++)
                {
                    vector<char> temp3;
                    for (int l = 0; l < temp.size(); l++)
                    {
                        int index = temp[l] - 'A';
                        for (int m = 0; m < nfa[index][k].size(); m++)
                        {
                            if (find(temp3.begin(), temp3.end(), nfa[index][k][m]) == temp3.end())
                            {
                                temp3.push_back(nfa[index][k][m]);
                            }
                        }
                    }
                    temp2.push_back(temp3);
                }
                dfa.push_back(temp2);
            }
        }
    }

    cout << "The DFA is: \n";
    for (int i = 0; i < dfa.size(); i++)
    {
        for (int j = 0; j < noOfSymbols; j++)
        {
            cout << "State " << i << " on " << j << " : ";
            for (int k = 0; k < dfa[i][j].size(); k++)
            {
                cout << dfa[i][j][k] << " ";
            }
            cout << "\n";
        }
    }
}
