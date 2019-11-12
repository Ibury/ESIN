#include "queue.hpp"
#include <iostream>
#include <sstream>

using namespace std;

/*
int reverseQueue(queue *q)
//PRE: Cua
//POST: Suma total de tots elements més inversió de la cua.
{
    int sum = 0;

    if (not q->empty())
    {

        int val = q->first();

        q->pop();

        sum += reverseQueue(q) + val;

        q->push(val);
    }

    return sum;
}

void remove_older_previous_sum2(queue *q, queue *out)
//PRE: Cua
//POST: Nova cua amb els elements menors a la suma dels X anterios elements.
{
    int total = reverseQueue(q);

    while (not q->empty())
    {
        int val = q->first();
        q->pop();

        total -= val;

        if (val < total)
            out->push(val);
    }
}
*/

void remove_older_previous_sum(queue *q, queue *out)
//PRE: Cua
//POST: Nova cua amb els elements menors a la suma dels X anterios elements.
{
    int total = 0;

    while (not q->empty())
    {
        int val = q->first();
        q->pop();

        if (val <= total)
            out->push(val);

        total += val;
    }
}

void printQueue(queue q)
{
    while (not q.empty())
    {
        cout << q.first();

        q.pop();

        if (not q.empty())
            cout << " ";
    }

    cout << endl;
}


int main()
{
    string line;
    int x;

    while (getline(cin, line))
    {
        istringstream ss(line);

        queue *q = new queue;

        while (ss >> x)
        {
            q->push(x);
        }

        queue *modified = new queue;

        remove_older_previous_sum(q, modified);

        printQueue(*modified);
    }
}