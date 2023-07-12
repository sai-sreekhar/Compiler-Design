#include <bits/stdc++.h>
using namespace std;

int n = 0;
void follow(char c, vector<vector<char>> &follows);
void first(char c, vector<vector<char>> &firsts);
vector<char> terminals;
vector<char> nonTerminals;
vector<vector<vector<char>>> productions;
vector<vector<char>> firsts;
vector<vector<char>> follows;

int main()
{
    int i, z;
    char c, ch;
    cout << "Enter the no of productions:\n";
    cin >> n;
    cout << "Enter the productions:\n";
    for (i = 0; i < n; i++)
    {
        char ch;
        // cout << "Enter the Terminal: ";
        cin >> ch;
        if (find(nonTerminals.begin(), nonTerminals.end(), ch) == nonTerminals.end())
        {
            nonTerminals.push_back(ch);
        }
        int c1 = 0;
        // cout << "Enter the number of productions for " << ch << " : ";
        cin >> c1;
        vector<vector<char>> temp1;
        for (int j = 0; j < c1; j++)
        {
            int c2 = 0;
            // cout << "Enter the number of symbols for production " << j + 1 << " : ";
            cin >> c2;
            vector<char> temp2;
            for (int j = 0; j < c2; j++)
            {
                char ch;
                // cout << "Enter the symbol: ";
                cin >> ch;
                temp2.push_back(ch);
                if (ch < 'A' || ch > 'Z')
                {
                    if (find(terminals.begin(), terminals.end(), ch) == terminals.end())
                    {
                        terminals.push_back(ch);
                    }
                }
            }
            temp1.push_back(temp2);
        }
        productions.push_back(temp1);
    }

    // for (int i = 0; i < nonTerminals.size(); i++)
    // {
    //     first(nonTerminals[i]);
    // }

    // for (int i = 0; i < firsts.size(); i++)
    // {
    //     cout << "First(" << nonTerminals[i] << ") = {";
    //     for (int j = 0; j < firsts[i].size(); j++)
    //     {
    //         cout << firsts[i][j] << " ";
    //     }
    //     cout << "}\n";
    // }

    for (int i = 0; i < terminals.size(); i++)
    {
        cout << terminals[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < nonTerminals.size(); i++)
    {
        cout << nonTerminals[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < productions.size(); i++)
    {
        cout << nonTerminals[i] << " -> ";
        for (int j = 0; j < productions[i].size(); j++)
        {
            for (int k = 0; k < productions[i][j].size(); k++)
            {
                cout << productions[i][j][k];
            }
            cout << " | ";
        }
        cout << "\n";
    }

    firsts.resize(nonTerminals.size());
    for (int i = 0; i < nonTerminals.size(); i++)
    {
        first(nonTerminals[i], firsts);
    }
    for (int i = 0; i < firsts.size(); i++)
    {
        cout << "First(" << nonTerminals[i] << ") = {";
        for (int j = 0; j < firsts[i].size(); j++)
        {
            cout << firsts[i][j] << " ";
        }
        cout << "}\n";
    }
    follows.resize(nonTerminals.size());
    follows[0].push_back('$');
    for (int i = 0; i < nonTerminals.size(); i++)
    {
        follow(nonTerminals[i], follows);
    }

    for (int i = 0; i < follows.size(); i++)
    {
        cout << "Follow(" << nonTerminals[i] << ") = {";
        for (int j = 0; j < follows[i].size(); j++)
        {
            cout << follows[i][j] << " ";
        }
        cout << "}\n";
    }
}

void first(char c, vector<vector<char>> &firsts)
{
    int prodIdx = find(nonTerminals.begin(), nonTerminals.end(), c) - nonTerminals.begin();
    if (firsts[prodIdx].size() > 0)
    {
        return;
    }

    vector<vector<char>> curProd = productions[prodIdx];
    for (int i = 0; i < curProd.size(); i++)
    {
        if (curProd[i][0] >= 'A' && curProd[i][0] <= 'Z')
        {
            first(curProd[i][0], firsts);
            int curProdIdx = find(nonTerminals.begin(), nonTerminals.end(), curProd[i][0]) - nonTerminals.begin();
            vector<char> temp = firsts[curProdIdx];
            int k = 0;
            while (find(temp.begin(), temp.end(), '#') != temp.end())
            {
                temp.erase(find(temp.begin(), temp.end(), '#'));
                k++;
                if (k >= curProd.size())
                {
                    break;
                }
                curProdIdx = find(nonTerminals.begin(), nonTerminals.end(), curProd[i][k]) - nonTerminals.begin();
                first(curProd[i][k], firsts);
                temp.insert(temp.end(), firsts[curProdIdx].begin(), firsts[curProdIdx].end());
            }

            for (int j = 0; j < temp.size(); j++)
            {
                if (find(firsts[prodIdx].begin(), firsts[prodIdx].end(), temp[j]) == firsts[prodIdx].end())
                {
                    firsts[prodIdx].push_back(temp[j]);
                }
            }
        }
        else
        {
            if (find(firsts[prodIdx].begin(), firsts[prodIdx].end(), curProd[i][0]) == firsts[prodIdx].end())
            {
                firsts[prodIdx].push_back(curProd[i][0]);
            }
        }
    }
}

void follow(char c, vector<vector<char>> &follows)
{
    int toFindIdx = find(nonTerminals.begin(), nonTerminals.end(), c) - nonTerminals.begin();

    if (follows[toFindIdx].size() > 0 && toFindIdx != 0)
    {
        return;
    }

    if (toFindIdx == 0 && follows[toFindIdx].size() > 1)
    {
        return;
    }

    for (int i = 0; i < productions.size(); i++)
    {
        for (int j = 0; j < productions[i].size(); i++)
        {
            for (int k = 0; k < productions[i][j].size(); k++)
            {
                if (productions[i][j][k] == c)
                {
                    if (k == productions[i][j].size() - 1)
                    {
                        if (nonTerminals[i] != c)
                        {
                            follow(nonTerminals[i], follows);

                            for (int l = 0; l < follows[i].size(); l++)
                            {
                                if (find(follows[toFindIdx].begin(), follows[toFindIdx].end(), follows[i][l]) == follows[toFindIdx].end())
                                {
                                    follows[toFindIdx].push_back(follows[i][l]);
                                }
                            }
                        }
                    }
                    else
                    {
                        if (find(nonTerminals.begin(), nonTerminals.end(), productions[i][j][k + 1]) == nonTerminals.end())
                        {
                            follows[toFindIdx].push_back(productions[i][j][k + 1]);
                        }
                        else
                        {
                            int curProdIdx = find(nonTerminals.begin(), nonTerminals.end(), productions[i][j][k + 1]) - nonTerminals.begin();
                            vector<char> temp = firsts[curProdIdx];
                            int l = 0;
                            while (find(temp.begin(), temp.end(), '#') != temp.end())
                            {
                                temp.erase(find(temp.begin(), temp.end(), '#'));
                                l++;
                                if (k + 1 + l >= productions[i][j].size())
                                {
                                    follow(nonTerminals[i], follows);
                                    for (int z = 0; z < follows[i].size(); z++)
                                    {
                                        if (find(follows[toFindIdx].begin(), follows[toFindIdx].end(), follows[i][z]) == follows[toFindIdx].end())
                                        {
                                            follows[toFindIdx].push_back(follows[i][z]);
                                        }
                                    }
                                    break;
                                }
                                curProdIdx = find(nonTerminals.begin(), nonTerminals.end(), productions[i][j][k + l]) - nonTerminals.begin();
                                temp.insert(temp.end(), firsts[curProdIdx].begin(), firsts[curProdIdx].end());
                            }

                            for (int m = 0; m < temp.size(); m++)
                            {
                                if (find(follows[toFindIdx].begin(), follows[toFindIdx].end(), temp[m]) == follows[toFindIdx].end())
                                {
                                    follows[toFindIdx].push_back(temp[m]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
