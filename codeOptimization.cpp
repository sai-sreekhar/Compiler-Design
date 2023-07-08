#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

int main()
{
    std::ifstream f("inp.txt");
    std::ofstream fout("out.txt");

    std::vector<std::string> list_of_lines;
    std::string line;
    while (std::getline(f, line))
    {
        list_of_lines.push_back(line);
    }

    std::map<std::string, std::string> dictValues;
    std::vector<std::vector<std::string>> constantFoldedList;
    std::cout << "Quadruple form after Constant Folding" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    for (const std::string &i : list_of_lines)
    {
        std::string op, arg1, arg2, res;
        std::istringstream iss(i);
        iss >> op >> arg1 >> arg2 >> res;
        if (op == "+" || op == "-" || op == "*" || op == "/")
        {
            if (std::isdigit(arg1[0]) && std::isdigit(arg2[0]))
            {
                int result = 0;
                if (op == "+")
                {
                    result = std::stoi(arg1) + std::stoi(arg2);
                }
                else if (op == "-")
                {
                    result = std::stoi(arg1) - std::stoi(arg2);
                }
                else if (op == "*")
                {
                    result = std::stoi(arg1) * std::stoi(arg2);
                }
                else if (op == "/")
                {
                    result = std::stoi(arg1) / std::stoi(arg2);
                }
                dictValues[res] = std::to_string(result);
                std::cout << "= " << result << " NULL " << res << std::endl;
                constantFoldedList.push_back({"=", std::to_string(result), "NULL", res});
            }
            else if (std::isdigit(arg1[0]))
            {
                if (dictValues.find(arg2) != dictValues.end())
                {
                    int result = 0;
                    if (op == "+")
                    {
                        result = std::stoi(arg1) + std::stoi(dictValues[arg2]);
                    }
                    else if (op == "-")
                    {
                        result = std::stoi(arg1) - std::stoi(dictValues[arg2]);
                    }
                    else if (op == "*")
                    {
                        result = std::stoi(arg1) * std::stoi(dictValues[arg2]);
                    }
                    else if (op == "/")
                    {
                        result = std::stoi(arg1) / std::stoi(dictValues[arg2]);
                    }
                    dictValues[res] = std::to_string(result);
                    std::cout << "= " << result << " NULL " << res << std::endl;
                    constantFoldedList.push_back({"=", std::to_string(result), "NULL", res});
                }
                else
                {
                    std::cout << op << " " << arg1 << " " << arg2 << " " << res << std::endl;
                    constantFoldedList.push_back({op, arg1, arg2, res});
                }
            }
            else if (std::isdigit(arg2[0]))
            {
                if (dictValues.find(arg1) != dictValues.end())
                {
                    int result = 0;
                    if (op == "+")
                    {
                        result = std::stoi(dictValues[arg1]) + std::stoi(arg2);
                    }
                    else if (op == "-")
                    {
                        result = std::stoi(dictValues[arg1]) - std::stoi(arg2);
                    }
                    else if (op == "*")
                    {
                        result = std::stoi(dictValues[arg1]) * std::stoi(arg2);
                    }
                    else if (op == "/")
                    {
                        result = std::stoi(dictValues[arg1]) / std::stoi(arg2);
                    }
                    dictValues[res] = std::to_string(result);
                    std::cout << "= " << result << " NULL " << res << std::endl;
                    constantFoldedList.push_back({"=", std::to_string(result), "NULL", res});
                }
                else
                {
                    std::cout << op << " " << arg1 << " " << arg2 << " " << res << std::endl;
                    constantFoldedList.push_back({op, arg1, arg2, res});
                }
            }
            else
            {
                int flag1 = 0;
                int flag2 = 0;
                std::string arg1Res = arg1;
                if (dictValues.find(arg1) != dictValues.end())
                {
                    arg1Res = dictValues[arg1];
                    flag1 = 1;
                }
                std::string arg2Res = arg2;
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
                        result = std::stoi(arg1Res) + std::stoi(arg2Res);
                    }
                    else if (op == "-")
                    {
                        result = std::stoi(arg1Res) - std::stoi(arg2Res);
                    }
                    else if (op == "*")
                    {
                        result = std::stoi(arg1Res) * std::stoi(arg2Res);
                    }
                    else if (op == "/")
                    {
                        result = std::stoi(arg1Res) / std::stoi(arg2Res);
                    }
                    dictValues[res] = std::to_string(result);
                    std::cout << "= " << result << " NULL " << res << std::endl;
                    constantFoldedList.push_back({"=", std::to_string(result), "NULL", res});
                }
                else
                {
                    std::cout << op << " " << arg1Res << " " << arg2Res << " " << res << std::endl;
                    constantFoldedList.push_back({op, arg1Res, arg2Res, res});
                }
            }
        }
        else if (op == "=")
        {
            if (std::isdigit(arg1[0]))
            {
                dictValues[res] = arg1;
                std::cout << "= " << arg1 << " NULL " << res << std::endl;
                constantFoldedList.push_back({"=", arg1, "NULL", res});
            }
            else
            {
                if (dictValues.find(arg1) != dictValues.end())
                {
                    std::cout << "= " << dictValues[arg1] << " NULL " << res << std::endl;
                    constantFoldedList.push_back({"=", dictValues[arg1], "NULL", res});
                }
                else
                {
                    std::cout << "= " << arg1 << " NULL " << res << std::endl;
                    constantFoldedList.push_back({"=", arg1, "NULL", res});
                }
            }
        }
        else
        {
            std::cout << op << " " << arg1 << " " << arg2 << " " << res << std::endl;
            constantFoldedList.push_back({op, arg1, arg2, res});
        }
    }

    std::cout << std::endl;
    std::cout << "Constant folded expression - " << std::endl;
    std::cout << "--------------------" << std::endl;
    for (const auto &i : constantFoldedList)
    {
        if (i[0] == "=")
        {
            std::cout << i[3] << " " << i[0] << " " << i[1] << std::endl;
        }
        else if (i[0] == "+" || i[0] == "-" || i[0] == "*" || i[0] == "/" || i[0] == "==" || i[0] == "<=" || i[0] == "<" || i[0] == ">" || i[0] == ">=")
        {
            std::cout << i[3] << " = " << i[1] << " " << i[0] << " " << i[2] << std::endl;
        }
        else if (i[0] == "if" || i[0] == "goto" || i[0] == "label" || i[0] == "not")
        {
            if (i[0] == "if")
            {
                std::cout << i[0] << " " << i[1] << " goto " << i[3] << std::endl;
            }
            if (i[0] == "goto")
            {
                std::cout << i[0] << " " << i[3] << std::endl;
            }
            if (i[0] == "label")
            {
                std::cout << i[3] << ":" << std::endl;
            }
            if (i[0] == "not")
            {
                std::cout << i[3] << " = " << i[0] << " " << i[1] << std::endl;
            }
        }
    }

    std::cout << std::endl;
    std::cout << "After dead code elimination - " << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (const auto &i : constantFoldedList)
    {
        if (i[0] == "=")
        {
            continue;
        }
        else if (i[0] == "+" || i[0] == "-" || i[0] == "*" || i[0] == "/" || i[0] == "==" || i[0] == "<=" || i[0] == "<" || i[0] == ">" || i[0] == ">=")
        {
            std::cout << i[3] << " = " << i[1] << " " << i[0] << " " << i[2] << std::endl;
        }
        else if (i[0] == "if" || i[0] == "goto" || i[0] == "label" || i[0] == "not")
        {
            if (i[0] == "if")
            {
                std::cout << i[0] << " " << i[1] << " goto " << i[3] << std::endl;
            }
            if (i[0] == "goto")
            {
                std::cout << i[0] << " " << i[3] << std::endl;
            }
            if (i[0] == "label")
            {
                std::cout << i[3] << ":" << std::endl;
            }
            if (i[0] == "not")
            {
                std::cout << i[3] << " = " << i[0] << " " << i[1] << std::endl;
            }
        }
    }

    return 0;
}
