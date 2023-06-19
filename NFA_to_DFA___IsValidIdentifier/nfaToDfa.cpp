#include <bits/stdc++.h>
#include <math.h>
#include <vector>
using namespace std;
int main()
{
    int noofstates, differentway;
    cin >> noofstates >> differentway;

    char matri[noofstates][differentway][noofstates];
    map<int, string> arr;
    map<char, int> arr1;
    map<int, string> epsilon;
    int starting = 0;
    char ch;

    for (int i = 0; i < noofstates; i++)
    {
        cin >> ch;
        arr[starting] = ch;
        arr1[ch] = starting;
        starting++;
    }
    for (int i = 0; i < noofstates; i++)
    {
        for (int j = 0; j < differentway; j++)
        {
            for (int k = 0; k < noofstates; k++)
            {
                cin >> matri[i][j][k];
            }
        }
    }
    cout << "    E-NFA table" << endl;
    for (int i = 0; i < noofstates; i++)
    {
        for (int j = 0; j < differentway; j++)
        {
            for (int k = 0; k < noofstates; k++)
            {
                cout << matri[i][j][k] << " ";
            }
            cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < noofstates; i++)
    {
        epsilon[i] = arr[i];
        for (int j = 0; j < noofstates; j++)
        {
            if (matri[i][differentway - 1][j] != '0' && epsilon[i] != to_string(matri[i][differentway - 1][j]))
            {
                epsilon[i] += matri[i][differentway - 1][j];
            }
        }
    }

    for (int i = 0; i < noofstates; i++)
    {
        for (int j = 1; j < epsilon[i].length(); j++)
        {
            if (epsilon[arr1[epsilon[i][j]]].length() > 1)
            {
                for (int k = 1; k < epsilon[arr1[epsilon[i][j]]].length(); k++)
                {
                    if (epsilon[i].find(epsilon[arr1[epsilon[i][j]]][k]) == string::npos)
                    {
                        epsilon[i] += epsilon[arr1[epsilon[i][j]]][k];
                    }
                }
            }
        }
    }

    cout << " Epsilons" << endl;
    for (int i = 0; i < noofstates; i++)
    {
        cout << arr[i] << " ---> " << epsilon[i] << endl;
    }

    map<int, map<int, string>> newstatematric;

    int power = pow(2, noofstates);
    string arrofnewstates[power];
    arrofnewstates[0] = epsilon[0];

    map<string, int> newstates;
    newstates[epsilon[0]] = 1;

    vector<char> eachstate;
    int start = 0, end = 1;

    while (start < end)
    {
        for (int x = 0; x < differentway - 1; x++)
        {
            for (int i = 0; i < arrofnewstates[start].length(); i++)
            {
                if (matri[arr1[arrofnewstates[start][i]]][x][0] != '0')
                {
                    for (int j = 0; j < noofstates; j++)
                    {
                        if (matri[arr1[arrofnewstates[start][i]]][x][j] != '0')
                        {
                            eachstate.push_back(matri[arr1[arrofnewstates[start][i]]][x][j]);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }

            for (int l = 0; l < eachstate.size(); l++)
            {
                for (int k = 0; k < epsilon[arr1[eachstate[l]]].length(); k++)
                    if (newstatematric[start][x].find(epsilon[arr1[eachstate[l]]][k]) == string::npos)
                    {
                        newstatematric[start][x] += epsilon[arr1[eachstate[l]]][k];
                    }
            }

            eachstate.clear();
            if (newstates[newstatematric[start][x]] != 1)
            {
                arrofnewstates[end] = newstatematric[start][x];
                end++;
            }

            newstates[newstatematric[start][x]] = 1;
        }
        start++;
    }
    cout << "    DFA table" << endl;
    for (int i = 0; i < newstates.size(); i++)
    {
        cout << arrofnewstates[i] << " ---> ";
        for (int j = 0; j < differentway - 1; j++)
        {
            cout << newstatematric[i][j] << " |";
        }
        cout << endl;
    }

    return 0;
}
