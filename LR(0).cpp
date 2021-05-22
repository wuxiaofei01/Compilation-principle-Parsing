#include<bits/stdc++.h>
#define MAX 40
using namespace std;

typedef struct code{
    string data;
    int num;
}Code;
Code code[MAX];

struct Gene{//产生式
    string left;
    char* right;
};
vector<Gene> gene;

typedef struct action{
    char para;
    int val;
}Action;
Action action[][MAX]={
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S',3},{'O',0}, {'O',0},{'O',0},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'A', 0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'S', 4},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'R', 10},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S',8},{'S',9},{'O',0},{'O',0},{'O',0}},
    {{'S',10},{'S',11},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'O',0},{'R',1}},
    {{'R', 4},{'R', 4},{'S', 12},{'S', 13},{'O',0},{'O',0},{'R',4},{'O',0},{'R', 4}},
    {{'R', 7},{'R', 7},{'R', 7},{'R', 7},{'O',0},{'O',0},{'R',7},{'O',0},{'R', 7}},
    {{'R', 8},{'R', 8},{'R', 8},{'R', 8},{'O',0},{'O',0},{'R',8},{'O',0},{'R', 8}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S', 8},{'S', 9},{'O', 0},{'O',0},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S', 8},{'S', 9},{'O', 0},{'O',0},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S', 8},{'S', 9},{'O', 0},{'O',0},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S', 8},{'S', 9},{'O', 0},{'O',0},{'O',0}},
    {{'O',0},{'O',0},{'O',0},{'O',0},{'S', 8},{'S', 9},{'O', 0},{'O',0},{'O',0}},
    {{'S',10},{'S',11},{'O',0},{'O',0},{'O',0},{'O',0},{'S',19},{'O',0},{'O',0}},
    {{'R',2},{'R',2},{'S',12},{'S',13},{'O',0},{'O',0},{'R',2},{'O', 0},{'R',2}},
    {{'R',3},{'R',3},{'S',12},{'S',13},{'O',0},{'O',0},{'R',3},{'O', 0},{'R',3}},
    {{'R',5},{'R',5},{'R',5},{'R',5},{'O',0},{'O',0},{'R',5},{'O', 0},{'R',5}},
    {{'R',6},{'R',6},{'R',6},{'R',6},{'O',0},{'O',0},{'R',6},{'O', 0},{'R',6}},
    {{'R',9},{'R',9},{'R',9},{'R',9},{'O',0},{'O',0},{'R',9},{'O', 0},{'R',9}},
};
//转移表goto
int Goto[MAX][MAX];
int num;//词法分析得到的单词个数
string str;//输入串
char *key[10]={"main","void","int","char","printf","scanf","else","if","return"};
char Word[20],ch;
string Vn="AETFV";//非终结符
int Seq;//三元式序号
string Equ[MAX][3];//存储三元式
int IsAlpha(char c)
{
    if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A')))
        return 1;
    else 
        return 0;
}

int IsNumber(char c)
{
    if(c>='0'&&c<='9')
        return 1;
    else 
        return 0;
}

int IsKey(char *word)
{
    int m,i;
    for(i=0;i<9;i++)
    {
        if((m=strcmp(word,key[i]))==0)
        {
            if(i==0)
                return 2;
            return 1;
        }
    }
    return 0;
}

char* scanner(char *fp,int ii)
{
    char Word[20]={'\0'};
    char ch;
    int i,c,sign=9;
    ch=*fp;
    if(IsAlpha(ch))
    {
        Word[0]=ch;
        fp++;
        ch=*fp;
        i=1;
        while(IsNumber(ch)||IsAlpha(ch))
        {
            Word[i]=ch;
            i++;
            fp++;
            ch=*fp;
        }
        Word[i]='\0';
        c=IsKey(Word);
        if(c==0)
        {
            sign=4;
            printf("%s\t普通标识符\t%d\n",Word,sign);
        }
        else if(c==2)
            printf("%s\t主函数  \t%d\n",Word,sign);
        else
            printf("%s\t关键字  \t%d\n",Word,sign);
    }
    else 
        if(IsNumber(ch))
        {
            Word[0]=ch;
            fp++;
            ch=*fp;
            i=1;
            while(IsNumber(ch))
            {
                Word[i]=ch;
                i++;
                fp++;
                ch=*fp;
            }
            Word[i]='\0';
            sign=4;
            printf("%s\t无符号实数\t%d\n",Word,sign);
        }
        else
        {
            Word[0]=ch;
            switch(ch)
            {
            case '[':
            case '(':
            case '{':
                fp++;
                sign=5;
                printf("%s\t界符      \t%d\n",Word,sign); 
                break;
            case ',':
            case '"':
            case ';':
                fp++;
                printf("%s\t界符      \t%d\n",Word,sign); 
                break;
            case ']':
            case ')':
            case '}':
                fp++;
                sign=6;
                printf("%s\t界符      \t%d\n",Word,sign); 
                break;
            case '+':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else if(ch=='+')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    sign=0;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                break;
            case '-':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else if(ch=='-')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    sign=1;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                break;
            case '*':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    sign=2;
                    printf("%s\t运算符  \t%d\n",Word,sign);

                }
                break;
            case '/':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    sign=3;
                    printf("%s\t运算符  \t%d\n",Word,sign);

                }
                break;
            case '!':
            case '=':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    sign=7;
                    printf("%s\t运算符  \t%d\n",Word,sign);

                }
                break;
            case '<':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else if(ch=='<')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                break;
            case '>':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else if(ch=='>')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                else
                {
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                break;
            case '%':
                fp++;
                ch=*fp;
                if(ch=='=')
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t运算符  \t%d\n",Word,sign);
                }
                if(IsAlpha(ch))
                {
                    Word[1]=ch;
                    fp++;
                    printf("%s\t类型标识符\t%d\n",Word,sign);
                }
                else
                {
                    printf("%s\t取余运算符\t%d\n",Word,sign);
                }
                break;
            case '\\':
                fp++;
                ch=*fp;
                Word[1]=ch;
                fp++;
                printf("%s\t制表符  \t%d\n",Word,sign);
                break;
            default:
                printf("无法识别字符\n"); 
                break;
        }
    }
    code[ii].data=Word;
    code[ii].num=sign;
    return fp;
}

int Cifafenxi()
{
    int i=-1;//种别码
    printf("请输入表达式(以‘#’号结束):\n");
    cin>>str;   
    cout<<"词法分析：\n";
    char *fp=&str[0];                   
    do{
        i++;                
        if(*fp=='#')
            break;
        else if(*fp==' ')
        {}
        else
        {
            fp=scanner(fp,i);
        }
    }while(*fp!='#');
    return i;
}

void GetWenfa()
{
    Gene gen;
    gen.left='S';
    gen.right="A";
    gene.push_back (gen);           

    gen.left ='A';
    gen.right ="V=E";
    gene.push_back (gen);               

    gen.left ='E';
    gen.right ="E+T";
    gene.push_back (gen);
    gen.right ="E-T";
    gene.push_back (gen);
    gen.right ="T";
    gene.push_back (gen);

    gen.left ='T';
    gen.right ="T*F";
    gene.push_back (gen);
    gen.right ="T/F";
    gene.push_back (gen);
    gen.right ="F";
    gene.push_back (gen);   

    gen.left ='F';
    gen.right ="i";
    gene.push_back (gen);
    gen.right ="(E)";
    gene.push_back (gen);

    gen.left ='V';
    gen.right ="i";
    gene.push_back (gen);

}

void Init()
{
    Goto[13][1]=9; Goto[13][3]=18;
    Goto[12][1]=9; Goto[12][3]=17;
    Goto[11][1]=9; Goto[11][2]=16;Goto[11][3]=7;
    Goto[10][1]=9; Goto[10][2]=15; Goto[10][3]=7; 
    Goto[9][1]=14; Goto[9][2]=6; Goto[9][3]=7;
    Goto[4][1]=5; Goto[4][2]=6; Goto[4][3]=7;
    Goto[0][0]=1; Goto[0][4]=2;;    
}

void error()
{
    cout<<"ERROR!"<<endl;
    cout<<"\n动作不存在！"<<endl;
    exit(-1);
}

void Output(vector<string> str)
{
    int len=str.size();
    for(int i=0;i<len;i++)
        cout<<str[i];
    cout<<"        \t";
}

void Yufafenxi(int num)
{                     
    Init(); 
    GetWenfa();                 
    vector<int> state;//状态栈
    vector<string> ana;//分析栈
    vector<string> an;//输入栈
    state.push_back (0);
    ana.push_back ("#");
    int i,j;
    int k=0;
    do{                                         
        for(int a=0;a<state.size();a++)//输出状态栈
            cout<<state[a];
        cout<<"\t\t";
        Output(ana);//输出分析栈                                         
        for(int a = k;a<=num;a++)//输出剩余输入栈
            cout<<code[a].data;
        cout<<"\t";
        i=state[state.size()-1];        
        j=code[k].num ; 
        if(j==9)
            error();
        cout<<"\t"<<action[i][j].para<<action[i][j].val<<"\t";  //输出动作         
        if(action[i][j].para=='O')
            error();
        else if(action[i][j].para=='S')//移进 
        {                                                                       
            cout<<"移进"<<"\n";
            state.push_back (action[i][j].val);    
            ana.push_back (code[k].data);      
            an.push_back (code[k].data);
            k++;                         
        }
        else if(action[i][j].para=='R')//规约
        {                                                               
            cout<<"规约"<<"\t";
            int len;
            int tem=action[i][j].val;
            len=strlen(gene[tem].right);            
            while(len!=0)//将分析栈中的待约项规约
            {
                state.pop_back ();                          
                ana.pop_back ();                    
                len--;
            }
            cout<<gene[action[i][j].val].left<<"->"<<gene[action[i][j].val].right<<endl;//输出规约所用的产生式
            if(action[i][j].val==1||action[i][j].val==2||action[i][j].val==3||action[i][j].val==5||action[i][j].val==6||action[i][j].val==9)//输出三元式
            {   
                int  t=an.size()-1;
                if(action[i][j].val!=9)
                {
                    Seq++;
                    Equ[Seq][0]=an[t-1];
                    Equ[Seq][1]=an[t-2];
                    Equ[Seq][2]=an[t];

                }
                an.pop_back ();
                an.pop_back ();
                an.pop_back ();
                char c=Seq+'1'-1;           
                string str="(";
                str=str+c;
                str=str+")";                    
                an.push_back (str);
            }
            ana.push_back (gene[action[i][j].val].left);    
            int a=state[state.size()-1];            
            string b=ana[ana.size()-1];         
            int dex=0;
            while(Vn[dex]!=b[0])
                dex++;                                      
            if(Goto[a][dex]==0)
                error();
            else
                state.push_back (Goto[a][dex]);         
        }
        else if(action[i][j].para=='A')
        {
            cout<<"\n分析成功！\n";
            break;
        }
    }while(1);
    int n=1;
    cout<<"\n三元式:\n";
    while(n<=Seq)
    {
        cout<<"\n"<<n<<"\t";    
        cout<<"("<<Equ[n][0]<<",\t"<<Equ[n][1]<<",\t"<<Equ[n][2]<<")"<<endl;
        n++;
    }
}
int main(void)
{  
    num=Cifafenxi();        
    cout<<"词法分析结束"<<"\n";
    system("pause");
    code[num+1].data="#";
    code[num+1].num =8;
    num++;
    int i;
    cout<<"语法分析:\n";
    cout<<"状态栈      "<<"\t"<<"分析栈"<<"\t\t"<<"剩余输入栈"<<"\t"<<"   动作   "<<"\t产生式"<<"\n"; 
    Yufafenxi(num);             
    cout<<"语法分析结束\n";
    return 0;
}