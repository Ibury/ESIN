#include <iostream>
#include "llista_itr.hpp"
using namespace std;
using iter = llista_itr<int>::iterador;

bool es_capicua(const llista_itr<int> &l)
{
    bool capicua = true;

    iter it_first = l.primer();
    iter it_last = l.ultim();

    while (it_first != it_last and capicua)
    {
        if (*it_first != *it_last)
            capicua = false;

        ++it_first;
        --it_last;
    }

    return capicua;
}

bool es_capicua(int n)
{
    llista_itr<int> l;
    iter it = l.primer();

    do
    {
        l.inserir_darrera(n % 10, it);
        n /= 10;
    } while (n > 0);

    return es_capicua(l);
}

int main()
{
    int n;
    while (cin >> n)
        cout << (es_capicua(n) ? "true" : "false") << endl;
}
