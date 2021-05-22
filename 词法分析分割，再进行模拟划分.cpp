#include <bits/stdc++.h>
using namespace std;

map<string, int> Token_K;//关键字
map<string, int> Token_P;//界符
map<string, int> Token_I;//标识符
map<string, int> Token_C1;//常数
map<string, int> Token_C2;//常实数表
map<string, int> Token_CT;//字符常量
map<string, int> Token_ST;//字符串常量
string s;
queue<pair<string , int> > que;
void init_Token_K()
{
    Token_K.insert(pair<string, int>{"int"    ,  1});
    Token_K.insert(pair<string, int>{"void"   ,  2});
    Token_K.insert(pair<string, int>{"break"  ,  3});
    Token_K.insert(pair<string, int>{"float"  ,  4});
    Token_K.insert(pair<string, int>{"while"  ,  5});
    Token_K.insert(pair<string, int>{"do"     ,  6});
    Token_K.insert(pair<string, int>{"struct" ,  7});
    Token_K.insert(pair<string, int>{"const"  ,  8});
    Token_K.insert(pair<string, int>{"case"   ,  9});
    Token_K.insert(pair<string, int>{"for"    , 10});
    Token_K.insert(pair<string, int>{"return" , 11});
    Token_K.insert(pair<string, int>{"if"     , 12});
    Token_K.insert(pair<string, int>{"defalut", 13});
    Token_K.insert(pair<string, int>{"else"   , 14});
}
void init_Token_P()
{
    Token_P.insert(pair<string, int>{"-"    ,  1});
    Token_P.insert(pair<string, int>{"/"    ,  2});
    Token_P.insert(pair<string, int>{"("    ,  3});
    Token_P.insert(pair<string, int>{")"    ,  4});
    Token_P.insert(pair<string, int>{"=="   ,  5});
    Token_P.insert(pair<string, int>{"<="   ,  6});
    Token_P.insert(pair<string, int>{"<"    ,  7});
    Token_P.insert(pair<string, int>{"+"    ,  8});
    Token_P.insert(pair<string, int>{"*"    ,  9});
    Token_P.insert(pair<string, int>{">"    , 10});
    Token_P.insert(pair<string, int>{"="    , 11});
    Token_P.insert(pair<string, int>{","    , 12});
    Token_P.insert(pair<string, int>{";"    , 13});
    Token_P.insert(pair<string, int>{"++"   , 14});
    Token_P.insert(pair<string, int>{"{"    , 15});
    Token_P.insert(pair<string, int>{"}"    , 16});
}
void init()
{
    init_Token_K();
    init_Token_P();
}
// map<string, int> Token_K;//关键字
// map<string, int> Token_P;//界符
// map<string, int> Token_I;//标识符
// map<string, int> Token_C1;//常数
// map<string, int> Token_C2;//常实数表
// map<string, int> Token_CT;//字符常量
// map<string, int> Token_ST;//字符串常量
void Token_out(string cha , int p)
{
    que.push({cha,p});
    //cout << cha << p << endl;
}
void OUT_MAP(map<string , int > mp , int choose)
{
    vector<pair<int , string >>a;
    for(auto it = mp.begin() ; it != mp.end() ; it++)
    {
        a.push_back({it->second , it ->first});
    }
    sort(a.begin() , a.end());
    for(int i = 0 ; i < a.size() ; i ++)
    {
        if(choose == 1)//是实数
        {
            int p = 0 ;
            for(int j = a[i].second.size() - 1; j >= 0 ; j--)
            {
                if(a[i].second[j] != '0') 
                {
                    p = j;
                    break;
                }
            }
            for(int j = 0 ; j <= p ; j ++)
            {
                cout <<a[i].second[j];
            }
            
        }
        else cout << a[i].second;
        if(i!=a.size() - 1)cout <<" ";
    }
}

void Fun_K(int &pos)
{
    if(!isalpha(s[pos])) return ;
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isalpha(s[i]))//不是字母 那么 就是 分隔符
        {
            if(Token_K[temp] != 0)
            {
                pos = i ;
                Token_out("K", Token_K[temp]);
            }
            return ;
        }
        temp += s[i];
    }
}

void Fun_I(int &pos)
{
    if(!isalpha(s[pos]) && s[pos] != '_' )return ;
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isalnum(s[i]) && s[i] != '_')//标识符 只能是 数字字母 下划线
        {
            if(!Token_I[temp])//不存在
            //Token_I.insert(pair<string , int >{temp , Token_I.size() + 1 });
            Token_I[temp] = Token_I.size() + 1;
            Token_out("I",Token_I.size());
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}

void Fun_C1(int &pos)
{
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(!isdigit(s[i]))
        {
            if(s[i] == '.' || s[i] == 'e')return ;//应该是实数
            else if(isalpha(s[i]))//标识符输出错误
            {
                cout <<"词法错误";
                exit(0);
            }
            else 
            {
                if(!Token_C1[temp])
                //Token_C1.insert(pair<string,int>{temp , Token_C1.size() + 1});
                Token_C1[temp] = Token_C1.size() + 1;
                Token_out("C1",Token_C1.size());
                pos = i ;
                return ;
            }
        }
        temp += s[i];
    }
}

void Fun_C2(int &pos)
{
    if(pos == s.size() || s[pos] == ' ' || !isdigit(s[pos]))return ;
    string temp;
    int flag1 = 0 , flag2 = 0 , flag3 = 0 , flag4 = 0;//记录 . e - + 
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(s[i] == '+' || s[i] == '-')
        if(s[i-1] !='e')//需要退出 但是 也需要判断是不是合法的符号 比如 0.5
        {
            if(flag1 == 1)
            {
                if(!Token_C2.count(to_string(atof(temp.c_str()))))
                Token_C2.insert(pair<string,int>(to_string(atof(temp.c_str())),Token_C2.size() + 1));
                //Token_C2[to_string(atof(temp.c_str()))] = Token_C2.size() + 1;

                Token_out("C2",Token_C2.size());
                pos = i ;
            }
            return ;
        }
        if(!isdigit(s[i]) && s[i] != '.' && s[i] != 'e' && s[i] != '-' && s[i] !='+')
        {
            if(flag1 <= 1 && flag2 <= 1 && flag3 <= 1 && flag4 <= 1)
            {
                if(!Token_C2.count(to_string(atof(temp.c_str()))))
                Token_C2.insert(pair<string,int>(to_string(atof(temp.c_str())),Token_C2.size() + 1));
                //Token_C2[to_string(atof(temp.c_str()))] = Token_C2.size() + 1;
                Token_out("C2",Token_C2.size());
                pos = i ;
                return ;
            }
            else 
            {
                cout <<"词法错误";
                exit(0);
            }
        }
        if(s[i] == '.')flag1++;
        if(s[i] == 'e')flag2++;
        if(s[i] == '-')flag3++;
        if(s[i] == '+')flag4++;
        temp += s[i];
    } 
}
void Fun_CT(int &pos)
{
    if(s[pos] !='\'')return;
    string temp;
    for(int i = pos + 1 ; i <= s.size() ; i ++)
    {
        if(s[i] == '\'')
        {
            if(Token_CT[temp])
            //Token_CT.insert(pair<string,int>{temp,Token_CT.size() + 1});
            Token_CT[temp] = Token_CT.size() + 1;
            Token_out("CT",Token_CT.size());
            i++;
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}
void Fun_ST(int &pos)
{
    if(s[pos] !='\"')return;
    string temp;
    for(int i = pos + 1; i <= s.size() ; i ++)
    {
        if(s[i] == '\"') 
        {
            if(Token_ST[temp])
            //Token_ST.insert(pair<string,int>{temp,Token_ST.size() + 1});
            Token_ST[temp] = Token_ST.size() +  1;
            Token_out("ST",Token_ST.size());
            i++;
            pos = i ;
            return ;
        }
        temp += s[i];
    }
}
void Fun_P(int &pos)
{
    string temp ;
    for(int i = pos ; i <= s.size() ; i ++)
    {
        if(Token_P[temp])
        {
            Token_out("P",Token_P[temp]);
            pos = i ;
            return ;
        }
        temp+=s[i];
    }
}
void Check(int i)
{
    if(!isdigit(s[i])) return ;
    string temp ;
    for(int i = i ; i <= s.size() ; i ++)
    {
        if(!isdigit(s[i]))
        {
            if(s[i] == '.' || s[i] == 'e')return ;//应该是实数
            else if(isalpha(s[i]))//标识符输出错误
            {
                cout <<"词法错误";
                exit(0);
            }
            else 
                return ;
        }
    temp += s[i];
    }
}

int main()
{
    init();
    getline(cin,s);
    int i = 0;
    Check(i);
    
    for(int i = 0 ; i < s.size() ;)
    {
        if(s[i] == ' ')
        {
            i++;
            continue;
        }
        if(isalpha(s[i]))//如果第一个字符是 字母 那么 就只能是 关键字 或者 标识符
        {
            Fun_K(i);
            Fun_I(i);
        }
        else if(isdigit(s[i]))//如果是 数字 那么是 ， 常数，常实数
        {
            Fun_C1(i);
            Fun_C2(i);
        }
        else if(s[i] =='\'')//字符常量
        {
            Fun_CT(i);
        }
        else if(s[i] == '\"')//字符串常量
        {
            Fun_ST(i);
        }
        else 
        {
            Fun_P(i);
        }
    }
    

    //通过词法分析 然后进行语法分析即可
    int flag = 1;//标志位 表示 前一个位置是什么符号
    while(!que.empty())
    {
        pair<string , int > now = que.front();
        que.pop();
        if(now.first == "P" && (now.second == 3 || now.second == 4))// 当前位置是 ( )
        continue;

        if(now.first == "C1" || now.first == "C2" || now.first =="I")//为标识符 或者 数字
        {
            if(flag == 1)flag = 0;
            else
            {
                 cout<<"错误";
                 return 0;
            }
        }
        else 
        {
            if(flag == 0) flag = 1;
            else 
            {
                cout<<"错误";
                 return 0;
            }
        }
    }
    cout <<"正确";
}