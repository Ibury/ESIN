#include <iostream>
#include <sstream>
#include "cuaprio.hpp"

using namespace std;

template <typename T>
void heap_sort(vector<T> &v)
{
    CuaPrio<T, T> c;

    for (int i = 0; i < v.size(); ++i)
    {
        c.insereix(v[i], v[i]);
    }

    for (int i = v.size() - 1; i >= 0; --i)
    {
        v[i] = c.min();
        c.elim_min();
    }
}

int main()
{

    string line;

    CuaPrio<int, int> c;

    int x;

    vector<int> v;

    while (getline(cin, line))
    {
        istringstream ss(line);

        while (ss >> x)
        {
            v.push_back(x);
        }
    }

    heap_sort(v);

    for (int i = v.size()-1; i >= 0; --i)
    {
        cout << v[i];

        if (i != 0)
            cout << " ";
    }

    cout << endl;

    for (unsigned int i = 0; i < v.size(); ++i)
    {
        cout << v[i];

        if (i != v.size() - 1)
            cout << " ";
    }

    cout << endl;
}