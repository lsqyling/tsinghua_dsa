 //
// Created by shiqing on 19-5-26.
//

#include <sstream>
#include <cmath>
#include "dsa/InfixExpression.h"


namespace linear {

const char InfixExpression::priorityTable_[LEN][LEN];

double InfixExpression::evaluate() noexcept
{
    opNums_.clear();
    std::cout << suffixExpr_ << std::endl;
    std::istringstream iss(suffixExpr_);
    std::string word;
    while (iss >> word)
    {
        if (word == "+")
        {
            auto rq = opNums_.pop();
            auto lq = opNums_.pop();
            opNums_.push(lq + rq);
        }
        else if (word == "-")
        {
            auto rq = opNums_.pop();
            auto lq = opNums_.pop();
            opNums_.push(lq - rq);
        }
        else if (word == "*")
        {
            auto rq = opNums_.pop();
            auto lq = opNums_.pop();
            opNums_.push(lq * rq);
        }
        else if (word == "/")
        {
            auto rq = opNums_.pop();
            auto lq = opNums_.pop();
            opNums_.push(lq / rq);
        }
        else if (word == "^")
        {
            auto rq = opNums_.pop();
            auto lq = opNums_.pop();
            opNums_.push(std::pow(lq, rq));
        }
        else if (word == "!")
        {
            int r = opNums_.pop();
            double result = 1;
            while (r)
            {
                result *= r;
                --r;
            }
            opNums_.push(result);
        }
        else
        {
            opNums_.push(std::atof(word.c_str()));
        }
    }
    return opNums_.pop();
}

void InfixExpression::readNumber(const char *&s)
{
    opNums_.push(*s - '0');
    while (isdigit(*++s))
    {
        opNums_.push(opNums_.pop() * 10 + (*s - '0'));
    }
    if (*s != '.') return;
    double fraction = 1;
    while (isdigit(*++s))
    {
        opNums_.push(opNums_.pop() + (*s - '0') * (fraction /= 10));
    }
}

String InfixExpression::init() noexcept
{
    const char *s = infixExpr_.c_str();
    opChars_.push('\0');
    std::string infix;
    while (!opChars_.empty())
    {
        if (isdigit(*s))
        {
            readNumber(s);
            std::string s;
            infix.append(std::to_string(opNums_.top()));
            infix.append(" ");
        }
        else
        {
            switch (orderBetween(opChars_.top(), *s))
            {
                case '<':
                    opChars_.push(*s++);
                    break;
                case '=':
                    opChars_.pop();
                    ++s;
                    break;
                case '>':
                    infix.append(" ");
                    infix.insert(infix.end(), opChars_.pop());
                    infix.append(" ");
                    break;
                default:
                    exit(-1);
            }
        }
    }
    return suffixExpr_ = String(infix);
}

}

int linear::expressionValue()
{
    int result = termValue();
    bool more = true;
    while (more)
    {
        char op = std::cin.peek();
        if (op == '+' || op == '-')
        {
            std::cin.get();
            int value = termValue();
            if (op == '+') result += value;
            else result -= value;
        }
        else more = false;
    }
    return result;
}

int linear::factorValue()
{
    int result = 0;
    char c = std::cin.peek();
    if (c == '(')
    {
        std::cin.get();
        result = expressionValue();
        std::cin.get();
    }
    else
    {
        while (isdigit(c))
        {
            result = 10 * result + c - '0';
            std::cin.get();
            c = std::cin.peek();
        }
    }
    return result;
}

int linear::termValue()
{
    int result = factorValue();
    while (true)
    {
        char op = std::cin.peek();
        if (op == '*' || op == '/')
        {
            std::cin.get();
            int value = factorValue();
            if (op == '*') result *= value;
            else result /= value;
        }
        else break;
    }

    return result;
}




