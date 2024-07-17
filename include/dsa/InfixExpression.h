//
// Created by shiqing on 19-5-26.
//

#ifndef TSINGHUA_DATASTRUCTURE_INFIXEXPRESSION_H
#define TSINGHUA_DATASTRUCTURE_INFIXEXPRESSION_H

#include <iostream>
#include "String.h"
#include "Stack.h"

namespace linear {

class InfixExpression
{
public:
    explicit InfixExpression(const String &s) : infixExpr_(removeSpace(s))
    {
        init();
    }

    double evaluate() noexcept;

    String getSuffixExpr() const noexcept
    {
        return suffixExpr_;
    }

protected:
    String init() noexcept;

    void readNumber(const char *&s);

private:
    String infixExpr_;
    String suffixExpr_;

    Stack<double> opNums_;
    Stack<char> opChars_;

    enum Operator
    {
        ADD, SUB, MUL, DIV, POW, FAC, LP, RP, EOE, LEN
    };

    static constexpr char priorityTable_[LEN][LEN] = {{'>', '>', '<', '<', '<', '<', '<', '>', '>'},
                                                      {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
                                                      {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
                                                      {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
                                                      {'>', '>', '>', '>', '>', '<', '<', '>', '>'},
                                                      {'>', '>', '>', '>', '>', '>', '<', '>', '>'},
                                                      {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
                                                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                                      {'<', '<', '<', '<', '<', '<', '<', ' ', '='}};

    Operator mapTo(char c) const noexcept
    {
        switch (c)
        {
            case '+':
                return ADD;
            case '-':
                return SUB;
            case '*':
                return MUL;
            case '/':
                return DIV;
            case '^':
                return POW;
            case '!':
                return FAC;
            case '(':
                return LP;
            case ')':
                return RP;
            case '\0':
                return EOE;
            default:
                return EOE;
        }
    }

    char orderBetween(char sTop, char curr) const noexcept
    {
        return priorityTable_[mapTo(sTop)][mapTo(curr)];
    }

    String removeSpace(const String &s) noexcept
    {
        String r;
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            if (!isspace(*it))
            {
                r.pushBack(*it);
            }
        }
        return r;
    }

};


/*
 * The evaluation of simple four arithmetic expressions.
 * Restrictions: the expression cann't contain the space. only has + - * /
 */

//    the entry of program
int expressionValue();

int factorValue();

int termValue();

}

#endif //TSINGHUA_DATASTRUCTURE_INFIXEXPRESSION_H
