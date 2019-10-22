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

Arbre<unsigned int> mount(const vector<Node> &v, unsigned int pos)
{
    // Case base
    if (v[pos].fill.size() == 0)
    {
        return Arbre<unsigned int>(v[pos].valor);
    }
    else
    {
        // Construct tree from the last element to first and construct from right to left.

        Arbre<unsigned int> a(v[pos].valor);

        for (int i = v[pos].fill.size() - 1; i >= 0; --i)
        {
            Arbre<unsigned int> b(mount(v, v[pos].fill[i]));
            a.afegir_fill(b);
        }

        return a;
    }
}

Arbre<unsigned int> mount(const vector<Node> &v)
{
    unsigned int pos = 0;

    return mount(v, pos);
}

int main()
{
    int n, j = 0;

    // General trees can not be empty, so to can declare them the solution is use pointers.
    Arbre<unsigned int> *a, *b;

    // Do twice
    for (int i = 0; i < 2; ++i)
    {
        // Get total number of nodes of the tree.
        cin >> n;

        vector<Node> v(n);

        // Store tree
        arbre(j, v);

        // Build trees
        if (i == 0)
            a = new Arbre<unsigned int>(mount(v));
        else
            b = new Arbre<unsigned int>(mount(v));

        j = 0;
    }

    *a = *a + *b;
    a->preordre();

    delete a;
    delete b;
}