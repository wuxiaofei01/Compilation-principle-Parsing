#include <bits/stdc++.h>
using namespace std;
void E();
void E1();
void T();
void T1();
void F();
string s;
int i;
int ERR;
int SwitchNum;
int main()
{
    s   = "";
    i   = 0;
    ERR = 0;
    cout << "Please enter your sentence:" << endl;
    cin >> s;
    s.resize(s.size() + 1);
    s[s.size() - 1] = '#';
    E();
    if (s[i] == '#')
        cout << "success" << endl;
    else
        cout << endl;
    return 0;
}
void E()
{
    if (ERR == 0)
    {
        T();
        E1();
    }
}
void E1()
{
    if (ERR == 0)
    {
        if (s[i] == '+')
        {
            ++i;
            T();
            E1();
        }
        else if (s[i] != '#' && s[i] != ')')
        {
            cout << "fail" << endl;
            ERR = 1;
        }
    }
}
void T()
{
    if (ERR == 0)
    {
        F();
        T1();
    }
}
void T1()
{
    if (ERR == 0)
    {
        if (s[i] == '*')
        {
            ++i;
            F();
            T1();
        }
        else if (s[i] != '#' && s[i] != ')' && s[i] != '+')
        {
            cout << "fail" << endl;
            ERR = 1;
        }
    }
}
void F()
{
    if (ERR == 0)
    {
        if (s[i] == '(')
        {
            ++i;
            E();
            if (s[i] == ')')
                ++i;
            else if (s[i] == '#')
            {
                cout << "fail" << endl;
                ERR = 1;
                ++i;
            }
        }
        else if (isalnum(s[i]))
            ++i;
        else
        {
            cout << "fail" << endl;
            ERR = 1;
        }
    }
}
