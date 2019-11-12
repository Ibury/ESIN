#include "pila.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int main ()
{
    string line;
    pila *odd_stack, *pair_stack;
    int val;

    while (getline(cin,line))
    {
        istringstream ss(line);

        odd_stack = new pila;
        pair_stack = new pila;

        while (ss >> val)
        {
            if (val % 2 == 0)
                pair_stack->apilar(val);
            else
                odd_stack->apilar(val);
        }

        while(not pair_stack->es_buida())
        {
            cout << pair_stack->cim();

            pair_stack->desapilar();

            if (not pair_stack->es_buida())
                cout << " ";
            else if(not odd_stack->es_buida())
                cout << " ";
        }

        while(not odd_stack->es_buida())
        {
            cout << odd_stack->cim();

            odd_stack->desapilar();

            if (not odd_stack->es_buida())
                cout << " ";
        }

        delete odd_stack;
        delete pair_stack;

        cout << endl;
    }
}