//
// Created by shiqing on 19-5-25.
//

#include "../include/Queue.h"
#include "../../common/CommonHeaders.h"

void testingQueue()
{
    linear::Queue<int> queue;
    for (int i = 0; i != 10; ++i)
    {
        queue.enqueue(i);
    }

    cout << queue << endl;

    for (int j = 0; j != 5; ++j)
    {
        queue.dequeue();
    }

    cout << queue << endl;

}

int main()
{
    testingQueue();

    return 0;
}


