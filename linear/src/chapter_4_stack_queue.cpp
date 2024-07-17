//
// Created by shiqing on 2020/5/21.
//
#include <cstring>
#include "../../common/CommonHeaders.h"
#include "stack_queue.h"

void convert(linear::stack<char> &S, int n, int base)
{
    static const char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (n)
    {
        S.push(digit[n % base]);
        n /= base;
    }
}

void testingConvert()
{
    linear::stack<char> S;
    int n = 0x3fff'ffff;
    convert(S, n, 2);
    cout << S << endl;
}

template<typename T>
bool legalStackPermutation(T src[], T need_judge[], int n)
{
    linear::stack<T> S;
    int curr = 0;
    for (int i = 0; i < n; ++i)
    {
        S.push(src[i]);
        while (!S.empty() && S.top() == need_judge[curr])
        {
            S.pop();
            ++curr;
        }
    }
    return S.empty();
}

void testingLegalSP()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7}, r[] = {3, 2, 1, 7, 5, 6, 4};
    cout << legalStackPermutation(arr, r, 7) << endl;
}

template<typename T>
void recursivePermutation(T src[], int index, int n, linear::stack<T> &S,
                          std::vector<T> &out, std::vector<std::vector<T>> &r)
{
    if (out.size() == n)
    {
        r.push_back(out);
        return;
    }
    if (index < n)
    {
        S.push(src[index]);
        recursivePermutation(src, index + 1, n, S, out, r);
        S.pop();
    }
    if (!S.empty())
    {
        T tmp = S.pop();
        out.push_back(tmp);
        recursivePermutation(src, index, n, S, out, r);
        S.push(tmp);
        out.pop_back();
    }
}

template<typename T>
std::vector<std::vector<T>> generateStackPermutation(T src[], int n)
{
    linear::stack<T> S;
    std::vector<T> out;
    std::vector<std::vector<T>> r;
    recursivePermutation(src, 0, n, S, out, r);
    return r;
}

void testingGenerateStackPermutation()
{
    int src[] = {1, 2, 3, 4};
    auto ans = generateStackPermutation(src, 4);
    int line = 1;
    for (const auto &item : ans)
    {
        cout << line++ << ": ";
        for (const auto &e : item)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}

bool paren(const char str[])
{
    int len = strlen(str);
    linear::stack<char> S;
    for (int i = 0; i < len; ++i)
    {
        switch (str[i])
        {
            case '(':
            case '{':
            case '[':
                S.push(str[i]);
                break;
            case ')':
                if (S.empty() || S.pop() != '(')
                    return false;
                break;
            case ']':
                if (S.empty() || S.pop() != '[')
                    return false;
                break;
            case '}':
                if (S.empty() || S.pop() != '{')
                    return false;
                break;
            default:
                break;
        }
    }
    return S.empty();
}

void testingParen()
{
    const char str[] = "a / ( b [ i - 1] [ j + 1]) + c[i+1][j-1]) * 2";
    cout << paren(str) << endl;
}


namespace expression_evaluate {
constexpr int L = 8;
constexpr char priority_curr_top[L][L] = {
        /* \0 */{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        /* ( */
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        /* + */
                {'>', '>', '=', '=', '<', '<', '<', '<'},
        /* - */
                {'>', '>', '=', '=', '<', '<', '<', '<'},
        /* * */
                {'>', '>', '>', '>', '=', '=', '<', '<'},
        /* / */
                {'>', '>', '>', '>', '=', '=', '<', '<'},
        /* ^ */
                {'>', '>', '>', '>', '>', '>', '=', '='},
        /* ! */
                {'>', '>', '>', '>', '>', '>', '=', '='}
};

enum Operator
{
    ZERO, LP, ADD, SUB, MUL, DIV, EXP, FAC, ERROR
};

inline Operator map_to(int c)
{
    switch (c)
    {
        case '\0':
            return ZERO;
        case '(':
            return LP;
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '^':
            return EXP;
        case '!':
            return FAC;
        default:
            return ERROR;
    }
}

bool greaterThan(int curr, int top)
{
    Operator op_c = map_to(curr), op_t = map_to(top);
    if (op_c == ERROR || op_t == ERROR) throw std::logic_error("the expr is illegal");
    return priority_curr_top[op_c][op_t] == '>';
}

void removeSpace(char src[])
{
    int len = strlen(src), i = 0, j = 0;
    while (j < len)
    {
        if (src[j] == ' ') ++j;
        else
        {
            src[i++] = src[j++];
        }
    }
    src[i] = '\0';
}

void readNumber(linear::stack<double> &s, string expr, int &i)
{
    double r = 0, fraction = 1;
    if (isdigit(expr[i]))
    {
        while (isdigit(expr[i]))
        {
            r = r * 10 + (expr[i] - '0');
            ++i;
        }

    }
    if (expr[i] == '.')
    {
        while (isdigit(expr[++i]))
        {
            r += (expr[i] - '0') * (fraction /= 10);
        }
    }
    --i;
    s.push(r);
}

string removePostZero(double r)
{
    string s = std::to_string(r);
    string tmp;
    for (int i = s.size() - 1; i >= 0; --i)
    {
        if (s[i] == '0') continue;
        tmp += s.substr(0, i + 1);
        break;
    }
    if (tmp.find('.') == tmp.size() - 1) tmp.pop_back();
    return tmp;
}


void readNumber(char *buf, int &j, char *str, int &i)
{
    double r = 0, fraction = 1;
    if (isdigit(str[i]))
    {
        while (isdigit(str[i]))
        {
            r = r * 10 + (str[i] - '0');
            ++i;
        }

    }
    if (str[i] == '.')
    {
        while (isdigit(str[++i]))
        {
            r += (str[i] - '0') * (fraction /= 10);
        }
    }
    --i;
    string s = removePostZero(r);
    for (auto c : s)
    {
        buf[j++] = c;
    }
    buf[j++] = ' ';
}

string infixToSuffix(char src[])
{
    removeSpace(src);
    linear::stack<char> op_c;
    op_c.push('\0');
    int len = std::strlen(src);
    char buf[len * 2 + 5];
    int j = 0;
    for (int i = 0; i < len; ++i)
    {
        if (std::isdigit(src[i]) || src[i] == '.')
        {
            readNumber(buf, j, src, i);
        }
        else if (src[i] == '(')
        {
            op_c.push(src[i]);
        }
        else if (src[i] == ')')
        {
            while (!op_c.empty() && op_c.top() != '(')
            {
                buf[j++] = op_c.pop();
                buf[j++] = ' ';
            }
            op_c.pop();
        }
        else
        {
            if (greaterThan(src[i], op_c.top()))
            {
                op_c.push(src[i]);
            }
            else
            {
                buf[j++] = op_c.pop();
                buf[j++] = ' ';
                while (!op_c.empty() && !greaterThan(src[i], op_c.top()))
                {
                    buf[j++] = op_c.pop();
                    buf[j++] = ' ';
                }
                op_c.push(src[i]);
            }
        }
    }
    while (!op_c.empty())
    {
        buf[j++] = op_c.pop();
    }
    return buf;
}

constexpr double factorial(int n)
{
    double sum = 1;
    for (int i = 1; i <= n; ++i)
    {
        sum *= i;
    }
    return sum;
}


double calculateSuffixExpression(string expr)
{
    cout << expr << endl;
    linear::stack<double> S;
    for (int i = 0; i < expr.size(); ++i)
    {
        if (isdigit(expr[i]) || expr[i] == '.')
        {
            readNumber(S, expr, i);
        }
        else
        {
            double d2, d1;
            switch (expr[i])
            {
                case '+':
                    d2 = S.pop(), d1 = S.pop();
                    S.push(d1 + d2);
                    break;
                case '-':
                    d2 = S.pop(), d1 = S.pop();
                    S.push(d1 - d2);
                    break;
                case '*':
                    d2 = S.pop(), d1 = S.pop();
                    S.push(d1 * d2);
                    break;
                case '/':
                    d2 = S.pop(), d1 = S.pop();
                    S.push(d1 / d2);
                    break;
                case '^':
                    d2 = S.pop(), d1 = S.pop();
                    S.push(pow(d1, d2));
                    break;
                case '!':
                    d1 = S.pop();
                    S.push(factorial(static_cast<int>(d1)));
                    break;
                case ' ':
                    break;
                default:
                    throw std::logic_error("expr is illegal");
            }
        }
    }
    return S.pop();
}


double calculateInfixExpression(const char *str)
{
    char src[strlen(str) + 1];
    strcpy(src, str);
    string suffix = infixToSuffix(src);
    return calculateSuffixExpression(suffix);
}

void testingCalculateExpression()
{
    const char str[] = "(0! + 1) * 2^(3! + 4) - (5! - 67 -(8 + 9))";
    cout << calculateInfixExpression(str) << endl;
}
}


int main(int argc, char *argv[])
{
    testingConvert();
    testingLegalSP();
    testingGenerateStackPermutation();
    testingParen();
    expression_evaluate::testingCalculateExpression();


    return 0;
}
