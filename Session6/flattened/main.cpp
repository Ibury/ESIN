#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>
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

int arbre(int &j, istringstream &ss, vector<Node> &v)
{
    int a = j, f;

    while (ss >> f)
    {
        ++j;

        v[a].valor = 0;

        v[a].fill = VE(f);

        for (int i = 0; i < f; ++i)
            v[a].fill[i] = arbre(j, ss, v);
    }

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

/*
float ach(Arbre<unsigned int> &a, Arbre<unsigned int>::iterador p, Arbre<unsigned int>::iterador ul)
{
    if (p != ul)
    {
        return 1;
    }
}

float aa(Arbre<unsigned int> &a)
{
    float ac = 0;
    return 1;
}
*/

unsigned int hermanos(Arbre<unsigned int>::iterador p, Arbre<unsigned int>::iterador ul)
{
    if (p != ul)
    {
        unsigned int mx = 0;
        return max(hermanos(p.seg_germa(), ul), mx) + 1;
    }
    else
    {
        return 1;
    }
}

unsigned int hijos(Arbre<unsigned int>::iterador p, Arbre<unsigned int>::iterador ul)
{
    if (p != ul)
    {
        unsigned int mx = 0;
        return max(hijos(p.primogenit(), ul), mx) + 1;
    }
    else
    {
        return 1;
    }
}

unsigned int altura(Arbre<unsigned int>::iterador p, Arbre<unsigned int>::iterador ul)
{

    if (p != ul)
    {
        int altV = altura(p.primogenit(), ul) + 1;
        int altH = altura(p.seg_germa(), ul);

        return max(altV, altH);
    }
    else
    {
        return 0;
    }
}

unsigned int altura(Arbre<unsigned int> &a)
{
    return altura(a.arrel(), a.final());
}

unsigned int nodos(Arbre<unsigned int>::iterador p, Arbre<unsigned int>::iterador ul)
{
    if (p == ul)
    {
        return 0;
    }
    else
    {
        return nodos(p.primogenit(), ul) + nodos(p.seg_germa(), ul) + 1;
    }
}

unsigned int nodos(Arbre<unsigned int> &a)
{
    return nodos(a.arrel(), a.final());
}

void draw(const Arbre<unsigned int>::iterador &f, const Arbre<unsigned int>::iterador &l, const string &ident)
{
    if (f != l)
    {
        cout << ident;
        cout << *f;
        draw(f.seg_germa(), l, "--");
        if ((f.primogenit() == l) and (f.seg_germa() == l))
            cout << endl;
        draw(f.primogenit(), l, "\n|\n");
    }
}

void draw(const Arbre<unsigned int> &a)
{
    draw(a.arrel(), a.final(), "");
}

int main()
{
    int n, j = 0;

    // General trees can not be empty, so to can declare them the solution is use pointers.
    Arbre<unsigned int> *a;

    // Get total trees to iterate.
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i)
    {

        // Get preorder line
        string line;

        while (i < n and getline(cin, line))
        {
            if (line != "")
            {
                // Add each element into vector
                istringstream ss(line);

                int nodes = 0;

                if (line.size() % 2 == 0)
                {
                    nodes = line.size() >> 1;
                }
                else
                {
                    nodes = (line.size() >> 1) + 1;
                }

                vector<Node> v(nodes);

                // Store tree
                arbre(j, ss, v);

                // Build trees
                a = new Arbre<unsigned int>(mount(v));

                a->preordre();

                //draw(*a);

                cout << "Altura " << altura(*a) << endl;
                cout << "Nodos " << nodos(*a) << endl;

                j = 0;
            }
        }
    }

    delete a;
}