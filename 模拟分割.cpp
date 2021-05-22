#include <bits/stdc++.h>

using namespace std;

string s;
stack<char> sta;
bool search(int pos)
{
    //cout << s[pos] << endl;
    if (s[pos] == '+' || s[pos] == '-')
        return true;
    if (s[pos] == '*' || s[pos] == '/')
        return true;
    return false;
}

void fun(int& pos)
{
    int flag = 0; //默认第一个是字符
    for (; pos < s.size(); pos++)
    {
        if(s[pos] ==')')
        {
            pos++;
            sta.pop();
            return;
        }
        if (s[pos] == '(')
        {
            pos++;
            sta.push(s[pos]);
            fun(pos);
            flag = 0;
        }
        else if (flag == 1) //前一个是 数字 那么 这一个需要是 算术符号
        {
            if (!search(pos))
            {
                cout << "错误";
                exit(0);
            }
            flag = 0;
        }
        else
        {
            if (!isalnum(s[pos]))
            {
                cout << "错误";
                exit(0);
            }
            flag = 1;
        }
    }
}
int main()
{
    cin >> s;
    int pos = 0;
    fun(pos);
    if(sta.empty())
        cout << "正确";
    else cout<<"错误";
}