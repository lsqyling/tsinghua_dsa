//
// Created by shiqing on 19-5-25.
//

#include "../include/Stack.h"
#include "../include/InfixExpression.h"
#include "../../common/CommonHeaders.h"

void testingStack()
{
    linear::Stack<int> si;
    for (int i = 0; i != 10; ++i)
    {
        si.push(i);
    }

    for (int j = 0; j != 5; ++j)
    {
        cout << si.pop() << " ";
    }
}

void testingSimpleExpression()
{
    cout << linear::expressionValue() << endl;
}

int main()
{
    testingStack();
    testingSimpleExpression();

    return 0;
}


