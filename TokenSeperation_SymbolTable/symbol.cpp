#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
struct Symbol
{
    string name;
    string type;
    int size;
    int address;
};
map<string, Symbol> symbol_table;
void parse_declaration(const string &declaration)
{
    vector<string> tokens;
    string token;
    for (char c : declaration)
    {
        if (isspace(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
        {
            token += c;
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
    if (tokens.size() < 2)
    {
        return;
    }
    Symbol symbol;
    symbol.name = tokens.back();
    symbol.type = tokens[tokens.size() - 2];
    symbol.size = 4;
    symbol.address = symbol_table.empty() ? 2024 : symbol_table.rbegin() -> second.address + symbol_table.rbegin()->second.size;
    symbol_table[symbol.name] = symbol;
}
void parse_program(const string &program)
{
    size_t pos = 0;
    while (pos < program.size())
    {
        size_t start = program.find_first_not_of(" \t\n", pos);
        if (start == string::npos)
        {
            break;
        }
        size_t end = program.find_first_of(";\n", start);
        if (end == string::npos)
        {
            end = program.size();
        }
        string statement = program.substr(start, end - start);
        size_t semicolon = statement.find_last_of(";");
        if (semicolon != string::npos)
        {
            statement = statement.substr(0, semicolon);
        }
        size_t equal = statement.find("=");
        if (equal != string::npos)
        {
            statement = statement.substr(0, equal);
        }
        parse_declaration(statement);
        pos = end + 1;
    }
}
int main()
{
    string program;
    cout << "Enter Program $ for termination:\n";
    getline(cin, program, '$');
    parse_program(program);
    for (const auto &entry : symbol_table)
    {
        const Symbol &symbol = entry.second;
        if (symbol.name != "main()")
        {
            cout << "Name\tType\tSize\tAddress\n";
            cout << symbol.name << "\t" << symbol.type << "\t" << symbol.size
                 << "\t" << symbol.address << "\n";
        }
    }
    return 0;
}