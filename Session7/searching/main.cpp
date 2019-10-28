#include <iostream>
#include <sstream>
#include <vector>
#include "abin.hpp"
using namespace std;

//Escriptura
std::string dep = "";
void pinta(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{

    std::string d1 = dep;
    if (f == l)
        cout << ".";
    else
    {
        cout << "[" << *f << "]\n"
             << d1 << " \\__";
        dep = d1 + " |  ";
        pinta(f.fdret(), l);
        cout << "\n"
             << d1 << " \\__";
        dep = d1 + "    ";
        pinta(f.fesq(), l);
    }
    dep = d1;
}

void pinta(const Abin<unsigned int> &a)
{
    pinta(a.arrel(), a.final());
    cout << endl;
}

Abin<unsigned int> mount(vector<int> &v, unsigned int &pos)
{
    Abin<unsigned int> a;

    // Case base is when we reach a leave of tree.
    if (pos < v.size() and v[pos] != -1)
    {
        int root = v[pos];

        Abin<unsigned int> lt = mount(v, ++pos);
        Abin<unsigned int> rt = mount(v, ++pos);

        a = Abin<unsigned int>(lt, root, rt);
    }

    return a;
}

Abin<unsigned int> mount(vector<int> &v)
{
    unsigned int pos = 0U;
    return mount(v, pos);
}

void printPostorder(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{
    if (f != l)
    {
        printPostorder(f.fesq(), l);
        printPostorder(f.fdret(), l);
        cout << " " << *f;
    }
}

void printInorder(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{
    if (f != l)
    {
        printInorder(f.fesq(), l);
        cout << " " << *f;
        printInorder(f.fdret(), l);
    }
}

void print(Abin<unsigned int> &a)
{
    Abin<unsigned int>::iterador f = a.arrel();
    Abin<unsigned int>::iterador l = a.final();

    cout << "pos:";
    printPostorder(f, l);
    cout << endl;
    cout << "ino:";
    printInorder(f, l);
    cout << endl;
}

int high(const Abin<unsigned int>::iterador &f, const Abin<unsigned int>::iterador &l)
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

int count(const Abin<unsigned int>::iterador &f, const Abin<unsigned int>::iterador &l)
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
    Abin<unsigned int> a;
    vector<int> v;

    int n, x;

    // Ignore first elem
    cin >> n;
    cin.ignore();

    bool insert = true;

    while (insert)
    {
        getline(cin, line);
        istringstream ss(line);

        if (line.size() == 0)
            insert = false;
        else
        {

            while (ss >> x)
            {
                if (x >= 0)
                {
                    a.insereix_bst(x);
                }
            }
        }
    }

    //pinta(a);

    while (cin >> n)
        cout << n << " " << a.consulta_bst(n) << endl;
}