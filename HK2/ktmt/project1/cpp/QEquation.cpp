// #include "QFloat.h"
// #include "QInt.h"
// #include <stack>

#include "QEquation.h"
bool IsDigit(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}

bool IsOperator(char ch)
{
    return ch == '+' ||
           ch == '-' ||
           ch == '*' ||
           ch == '/';
}

int Precedence(string x)
{
    if (x == "(")
        return 0;
    if (x == "+" || x == "-")
        return 1;
    if (x == "*" || x == "/")
        return 2;
    return 3;
}

template <class T>
T EvalNPR(const vector<string> &StrEquation)
{
    stack<T> Nums;
    for (int i = 0; i < (int)StrEquation.size(); ++i)
    {
        string x = StrEquation[i];
        if (IsOperator(x.back()))
        {
            T a = Nums.top();
            Nums.pop();
            T b = Nums.top();
            Nums.pop();

            T c;
            switch (x.back())
            {
            case '+':
                c = b + a;
                break;
            case '-':
                c = b - a;
                break;
            case '*':
                c = b * a;
                break;
            case '/':
                c = b / a;
                break;
            }
            Nums.push(c);
        }
        else
        {
            Nums.push(x);
        }
    }
    if (Nums.size() > 0)
        return Nums.top();
    return "0";
}

vector<string> InfixToPostfix(const vector<string> &Infix)
{
    vector<string> Postfix;
    stack<string> St;
    for (int i = 0; i < (int)Infix.size(); ++i)
    {
        string x = Infix[i];
        if (IsDigit(x.back()))
        {
            Postfix.push_back(x);
        }
        else if (x == "(")
        {
            St.push(x);
        }
        else if (x == ")")
        {
            while (!St.empty())
            {
                string tmp = St.top();
                St.pop();
                if (tmp == "(")
                    break;
                Postfix.push_back(tmp);
            }
        }
        else
        {
            while (!St.empty() && Precedence(x) <= Precedence(St.top()))
            {
                Postfix.push_back(St.top());
                St.pop();
            }
            St.push(x);
        }
    }
    while (!St.empty())
    {
        Postfix.push_back(St.top());
        St.pop();
    }
    return Postfix;
}

vector<string> ExtractEquation(const string &s)
{
    vector<string> StrEquation;
    string tmp;
    for (int i = 0; i < (int)s.size(); ++i)
    {
        if (s[i] == ' ')
        {
            StrEquation.push_back(tmp);
            tmp = "";
        }
        else
        {
            bool isDigit = IsDigit(s[i]);
            if (isDigit)
            {
                if (tmp.size() > 0 && tmp.back() != '-' && !IsDigit(tmp.back()))
                {
                    StrEquation.push_back(tmp);
                    tmp = "";
                }
                if (tmp.size() > 0 && tmp.back() == '-')
                {
                    if (StrEquation.size() > 0 && IsDigit(StrEquation.back().back()))
                    {
                        StrEquation.push_back(tmp);
                        tmp = "";
                    }
                }
                tmp.push_back(s[i]);
            }
            else
            {
                if (tmp.size() > 0)
                    StrEquation.push_back(tmp);
                tmp = "";
                tmp.push_back(s[i]);
            }
        }
    }
    StrEquation.push_back(tmp);
    return StrEquation;
}

template <class T>
T CalEquation(const string &s)
{
    vector<string> StrEquation = ExtractEquation(s);
    StrEquation = InfixToPostfix(StrEquation);
    return EvalNPR<T>(StrEquation);
}

int main()
{
#ifdef __linux__
    cerr << "Linux\n";
#endif

#ifdef _WIN32
    cerr << "Windows\n";
#endif

    QInt res = CalEquation<QInt>("(-13+3)*4");
    res.PrintQInt(10);
    // QInt a = "-10";
    // a.PrintQInt(10);
    // QInt b = "4";
    // b.PrintQInt(10);
    // QInt res = a * b;
    // res.PrintQInt(10);
}