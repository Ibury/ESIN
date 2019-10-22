#include <iostream>
#include <vector>
#include <sstream>
#include "arbre.hpp"

using namespace std;

typedef vector<int> VE;

struct Node
{
    int valor;
    VE fill;
};

// Llegeix un arbre i el desa a un tros del vector v començant a la posició j.
// Modifica la variable j perque apunti a la següent posició lliure de v.
// Retorna la posició dins de v de l'arrel del (sub)arbre llegit.

int arbre(int &j, vector<Node> &v)
{
    int a = j, f;

    ++j;

    cin >> v[a].valor >> f;
    v[a].fill = VE(f);

    for (int i = 0; i < f; ++i)
        v[a].fill[i] = arbre(j, v);

    return a;
}

void postordre(const Arbre<int> &a, const Arbre<int>::iterador &f, const Arbre<int>::iterador &l)
{
    if (f != l)
    {
        postordre(a, f.primogenit(), l);
        cout << " " << *f;
        postordre(a, f.seg_germa(), l);
    }
}

void print(const Arbre<int> &a)
{
    postordre(a, a.arrel(), a.final());
    cout << endl;
}

Arbre<int> mount(const vector<Node> &v, unsigned int pos)
{
    // Case base
    if (v[pos].fill.size() == 0)
    {
        return Arbre<int>(v[pos].valor);
    }
    else
    {
        // Construct tree from the last element to first.

        Arbre<int> a(v[pos].valor);

        for (int i=v[pos].fill.size()-1; i>=0; --i)
        {
            Arbre<int> b(mount(v, v[pos].fill[i]));
            a.afegir_fill(b);
        }

        return a;
    }
}

Arbre<int> mount(const vector<Node> &v)
{
    unsigned int pos = 0;

    return mount(v, pos);
}

int main()
{
    int n, j = 0;

    // Get total number of nodes of the tree.
    cin >> n;

    vector<Node> v(n);

    // Store tree
    arbre(j, v);

    // Build tree
    Arbre<int> a(mount(v));
    print(a);
}