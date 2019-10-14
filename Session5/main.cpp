#include <iostream>
#include <sstream>
#include <vector>
#include "abin.hpp"
using namespace std;
using iter = Abin<int>::iterador;

//Escriptura
std::string dep = "";
void pinta(const Abin<int> &a, iter f, iter l)
{

    std::string d1 = dep;
    if (f == l)
        cout << ".";
    else
    {
        cout << "[" << *f << "]\n"
             << d1 << " \\__";
        dep = d1 + " |  ";
        pinta(a, f.fdret(), l);
        cout << "\n"
             << d1 << " \\__";
        dep = d1 + "    ";
        pinta(a, f.fesq(), l);
    }
    dep = d1;
}

void pinta(const Abin<int> &a)
{
    pinta(a, a.arrel(), a.final());
    cout << endl;
}

Abin<int> mount(vector<int> &v, unsigned int &pos)
{
    Abin<int> a;

    // Case base is when we reach a leave of tree.
    if (pos < v.size() and v[pos] != -1)
    {
        int root = v[pos];

        Abin<int> lt = mount(v, ++pos);
        Abin<int> rt = mount(v, ++pos);

        a = Abin<int>(lt, root, rt);
    }

    return a;
}

Abin<int> mount(vector<int> &v)
{
    auto pos = 0U;
    return mount(v, pos);
}

void printPostorder(Abin<int> &a, iter f, iter l)
{
    if (f != l)
    {
        printPostorder(a, f.fesq(), l);
        printPostorder(a, f.fdret(), l);
        cout << " " << *f;
    }
}

void printInorder(Abin<int> &a, iter f, iter l)
{
    if (f != l)
    {
        printInorder(a, f.fesq(), l);
        cout << " " << *f;
        printInorder(a, f.fdret(), l);
    }
}

void print(Abin<int> &a)
{
    iter f = a.arrel();
    iter l = a.final();

    cout << "pos: ";
    printPostorder(a, f, l);
    cout << endl;
    cout << "ino: ";
    printInorder(a, f, l);
    cout << endl;
}

int high(const iter &f, const iter &l)
{
    if (f == l)
    {
        return 0;
    }
    else
    {
        return 1 + max(high(f.fesq(), l), high(f.fdret(), l));
    }
}

int count(const iter &f, const iter &l)
{
    if (f == l)
    {
        return 0;
    }
    else
    {
        return high(f.fesq(), l) + high(f.fdret(), l) + 1;
    }
}

int main()
{
    string line;
    Abin<int> a;
    vector<int> v;

    while (getline(cin, line))
    {
        istringstream ss(line);

        int x;

        cout << "Entrando valores: " << line << endl;

        while (ss >> x)
        {
            v.push_back(x);
        }

        cout << "Montando arbol" << endl;
        a = mount(v);

        cout << "Recorriendo arbol" << endl;
        print(a);

        v.clear();

        cout << "Altura del arbol: " << high(a.arrel(), a.final()) << endl;
        cout << "Nodos del arbol: " << count(a.arrel(), a.final()) << endl;

        pinta(a);
    }
}