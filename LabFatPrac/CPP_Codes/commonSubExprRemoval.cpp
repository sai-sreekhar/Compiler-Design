#include <iostream>
#include <map>
#include <string>

using namespace std;
struct Expression
{
    string id;
    string value;
};

void eliminateCommonSubexpressions(std::map<std::string, Expression> &expressions)
{
    map<string, string> subexpressions;
    for (auto &entry : expressions)
    {
        const string &id = entry.first;
        Expression &expression = entry.second;

        if (subexpressions.find(expression.value) != subexpressions.end())
        {
            expression.value = subexpressions[expression.value];
        }
        else
        {
            subexpressions[expression.value] = expression.id;
        }
    }
}

int main()
{
    map<string, Expression> expressions = {
        {"A", {"expr1", "a + b"}},
        {"B", {"expr2", "a + b"}},
        {"C", {"expr3", "c + d"}},
        {"D", {"expr4", "c + d"}},
        {"E", {"expr5", "e * f"}},
        {"F", {"expr6", "e * f"}},
    };

    std::cout << "Expressions before common subexpression elimination:" << std::endl;
    for (const auto &entry : expressions)
    {
        std::cout << entry.first << ": " << entry.second.value << std::endl;
    }

    eliminateCommonSubexpressions(expressions);

    std::cout << "Expressions after common subexpression elimination:" << std::endl;
    for (const auto &entry : expressions)
    {
        std::cout << entry.first << ": " << entry.second.value << std::endl;
    }

    return 0;
}
