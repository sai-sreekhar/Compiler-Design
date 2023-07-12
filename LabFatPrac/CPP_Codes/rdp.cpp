#include <iostream>
#include <stdlib.h>
using namespace std;
int count = 0;
void E();
void Ed();
void T();
void Td();
void F();
string expr;
int main()
{
    int n;
    cout << "Enter the number of productions: "
         << "\n";
    cin >> n;
    cout << "Enter the productions: "
         << "\n";
    for (int i = 0; i <= n; i++)
    {
        string prod;
        cin >> prod;
    }
    cout << "Enter the expression to be parsed: "
         << "\n";
    cin >> expr;
    int l = expr.length();
    expr += "$";
    E();
    if (l == count)
        cout << "Accepted"
             << "\n";
    else
        cout << "Rejected"
             << "\n";
}
void E()
{
    cout << "E->TE'"
         << "\n";
    T();
    Ed();
}
void Ed()
{
    if (expr[count] == '+')
    {
        count++;
        cout << "E'->+TE'"
             << "\n";
        T();
        Ed();
    }
    else if (expr[count] == '-')
    {
        count++;
        cout << "E'->-TE'"
             << "\n";
        T();
        Ed();
    }
    else
    {
        cout << "E'->null"
             << "\n";
    }
}
void T()
{
    cout << "T->FT'"
         << "\n";
    F();
    Td();
}
void Td()
{
    if (expr[count] == '*')
    {
        count++;
        cout << "T'->*FT'"
             << "\n";
        F();
        Td();
    }
    else if (expr[count] == '/')
    {
        count++;
        cout << "T'->/FT'"
             << "\n";
        F();
        Td();
    }
    else
    {
        cout << "T'->null"
             << "\n";
    }
}
void F()
{
    if (isalpha(expr[count]))
    {
        count++;
        cout << "F->id"
             << "\n";
    }
    else if (isdigit(expr[count]))
    {
        count++;
        cout << "F->digit"
             << "\n";
    }
    else if (expr[count] == '(')
    {
        count++;
        cout << "F->(E)"
             << "\n";
        E();
        if (expr[count] != ')')
        {
            cout << "Rejected"
                 << "\n";
            exit(0);
        }
        count++;
    }
    else
    {
        cout << "Rejected"
             << "\n";
        exit(0);
    }
}