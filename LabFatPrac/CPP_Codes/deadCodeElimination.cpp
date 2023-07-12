#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    ifstream f("inp.txt");

    vector<string> list_of_lines;
    string line;
    while (getline(f, line))
    {
        list_of_lines.push_back(line);
    }

    map<string, string> dictValues;
    vector<vector<string>> constantFoldedList;
    cout << "Quadruple form after Constant Folding" << endl;
    cout << "-------------------------------------" << endl;
    for (const string &i : list_of_lines)
    {
        string op, arg1, arg2, res;
        istringstream iss(i);
        iss >> op >> arg1 >> arg2 >> res;
        if (op == "+" || op == "-" || op == "*" || op == "/")
        {
            if (isdigit(arg1[0]) && isdigit(arg2[0]))
            {
                int result = 0;
                if (op == "+")
                {
                    result = stoi(arg1) + stoi(arg2);
                }
                else if (op == "-")
                {
                    result = stoi(arg1) - stoi(arg2);
                }
                else if (op == "*")
                {
                    result = stoi(arg1) * stoi(arg2);
                }
                else if (op == "/")
                {
                    result = stoi(arg1) / stoi(arg2);
                }
                dictValues[res] = to_string(result);
                cout << "= " << result << " NULL " << res << endl;
                constantFoldedList.push_back({"=", to_string(result), "NULL", res});
            }
            else if (isdigit(arg1[0]))
            {
                if (dictValues.find(arg2) != dictValues.end())
                {
                    int result = 0;
                    if (op == "+")
                    {
                        result = stoi(arg1) + stoi(dictValues[arg2]);
                    }
                    else if (op == "-")
                    {
                        result = stoi(arg1) - stoi(dictValues[arg2]);
                    }
                    else if (op == "*")
                    {
                        result = stoi(arg1) * stoi(dictValues[arg2]);
                    }
                    else if (op == "/")
                    {
                        result = stoi(arg1) / stoi(dictValues[arg2]);
                    }
                    dictValues[res] = to_string(result);
                    cout << "= " << result << " NULL " << res << endl;
                    constantFoldedList.push_back({"=", to_string(result), "NULL", res});
                }
                else
                {
                    cout << op << " " << arg1 << " " << arg2 << " " << res << endl;
                    constantFoldedList.push_back({op, arg1, arg2, res});
                }
            }
            else if (isdigit(arg2[0]))
            {
                if (dictValues.find(arg1) != dictValues.end())
                {
                    int result = 0;
                    if (op == "+")
                    {
                        result = stoi(dictValues[arg1]) + stoi(arg2);
                    }
                    else if (op == "-")
                    {
                        result = stoi(dictValues[arg1]) - stoi(arg2);
                    }
                    else if (op == "*")
                    {
                        result = stoi(dictValues[arg1]) * stoi(arg2);
                    }
                    else if (op == "/")
                    {
                        result = stoi(dictValues[arg1]) / stoi(arg2);
                    }
                    dictValues[res] = to_string(result);
                    cout << "= " << result << " NULL " << res << endl;
                    constantFoldedList.push_back({"=", to_string(result), "NULL", res});
                }
                else
                {
                    cout << op << " " << arg1 << " " << arg2 << " " << res << endl;
                    constantFoldedList.push_back({op, arg1, arg2, res});
                }
            }
            else
            {
                int flag1 = 0;
                int flag2 = 0;
                string arg1Res = arg1;
                if (dictValues.find(arg1) != dictValues.end())
                {
                    arg1Res = dictValues[arg1];
                    flag1 = 1;
                }
                string arg2Res = arg2;
                if (dictValues.find(arg2) != dictValues.end())
                {
                    arg2Res = dictValues[arg2];
                    flag2 = 1;
                }
                if (flag1 == 1 && flag2 == 1)
                {
                    int result = 0;
                    if (op == "+")
                    {
                        result = stoi(arg1Res) + stoi(arg2Res);
                    }
                    else if (op == "-")
                    {
                        result = stoi(arg1Res) - stoi(arg2Res);
                    }
                    else if (op == "*")
                    {
                        result = stoi(arg1Res) * stoi(arg2Res);
                    }
                    else if (op == "/")
                    {
                        result = stoi(arg1Res) / stoi(arg2Res);
                    }
                    dictValues[res] = to_string(result);
                    cout << "= " << result << " NULL " << res << endl;
                    constantFoldedList.push_back({"=", to_string(result), "NULL", res});
                }
                else
                {
                    cout << op << " " << arg1Res << " " << arg2Res << " " << res << endl;
                    constantFoldedList.push_back({op, arg1Res, arg2Res, res});
                }
            }
        }
        else if (op == "=")
        {
            if (isdigit(arg1[0]))
            {
                dictValues[res] = arg1;
                cout << "= " << arg1 << " NULL " << res << endl;
                constantFoldedList.push_back({"=", arg1, "NULL", res});
            }
            else
            {
                if (dictValues.find(arg1) != dictValues.end())
                {
                    cout << "= " << dictValues[arg1] << " NULL " << res << endl;
                    constantFoldedList.push_back({"=", dictValues[arg1], "NULL", res});
                }
                else
                {
                    cout << "= " << arg1 << " NULL " << res << endl;
                    constantFoldedList.push_back({"=", arg1, "NULL", res});
                }
            }
        }
    }

    cout << endl;
    cout << "Constant folded expression - " << endl;
    cout << "--------------------" << endl;
    for (const auto &i : constantFoldedList)
    {
        if (i[0] == "=")
        {
            cout << i[3] << " " << i[0] << " " << i[1] << endl;
        }
        else if (i[0] == "+" || i[0] == "-" || i[0] == "*" || i[0] == "/" || i[0] == "==" || i[0] == "<=" || i[0] == "<" || i[0] == ">" || i[0] == ">=")
        {
            cout << i[3] << " = " << i[1] << " " << i[0] << " " << i[2] << endl;
        }
    }

    cout << endl;
    cout << "After dead code elimination - " << endl;
    cout << "------------------------------" << endl;
    for (const auto &i : constantFoldedList)
    {
        if (i[0] == "=")
        {
            continue;
        }
        else if (i[0] == "+" || i[0] == "-" || i[0] == "*" || i[0] == "/" || i[0] == "==" || i[0] == "<=" || i[0] == "<" || i[0] == ">" || i[0] == ">=")
        {
            cout << i[3] << " = " << i[1] << " " << i[0] << " " << i[2] << endl;
        }
    }

    return 0;
}
