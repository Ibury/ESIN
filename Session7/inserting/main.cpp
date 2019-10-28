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

int countDigit(long n) 
{
    if (n == 0) return 1;
    
    int count = 0; 
    while (n != 0) { 
        n = n / 10; 
        ++count; 
    } 
    return count; 
}

void print_bst(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l, unsigned int level)
{
    if (f != l)
    {   
        ++level;
        print_bst(f.fdret(), l, level);
        int iter = (10*(level-1))-countDigit(*f);

        for (int i=0; i<iter; ++i)
        {
            cout << " ";
        }

        cout << *f << endl;
        print_bst(f.fesq(), l, level);
        
    }
}

void print_bst(Abin<unsigned int> &a)
{
    unsigned int level = 1;
    print_bst(a.arrel(), a.final(), level);
}

int main()
{
    string line;
    Abin<unsigned int> a;
    vector<int> v;

    int n;

    // Insert elements to BST.
    while (cin >> n)
        a.insereix_bst(n);

    print_bst(a);
}