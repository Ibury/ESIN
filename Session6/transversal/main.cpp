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
        // Construct tree from the last element to first and construct from right to left.

        Arbre<int> a(v[pos].valor);

        for (int i = v[pos].fill.size() - 1; i >= 0; --i)
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

void draw(const Arbre<int>::iterador &f, const Arbre<int>::iterador &l, const string &ident)
{
    if (f != l)
    {
        cout << ident;
        cout << *f << endl;
        draw(f.primogenit(), l, ident + "\t");
        draw(f.seg_germa(), l, ident);
    }
}

void draw(const Arbre<int> &a)
{
    draw(a.arrel(), a.final(), "");
}

unsigned int altura(Arbre<int>::iterador p, Arbre<int>::iterador ul)
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

unsigned int altura(Arbre<int> &a)
{
    return altura(a.arrel(), a.final());
}

void print_level(Arbre<int>::iterador p, Arbre<int>::iterador ul, int actual, int level)
{
    if (p != ul)
    {
        if (actual == level)
        {
            cout << " " << *p;
            print_level(p.seg_germa(), ul, actual, level);
        }
        else
        {
            print_level(p.primogenit(),ul, actual+1, level);
            print_level(p.seg_germa(), ul, actual, level);
        }
    }
}

void print_level(Arbre<int> &a, int level)
{
    int actual = 1;
    print_level(a.arrel(), a.final(), actual, level);
}


bool es_avl(Arbre<int>::iterador p, Arbre<int>::iterador ul)
{
    if (p != ul)
    {

        Arbre<int>::iterador germ = p.seg_germa();
        int diff = 1;
        while (germ != ul)
        {
            diff = (diff - altura(p.seg_germa(),ul));
            if (diff < 0)
                diff *= -1;

            germ = germ.seg_germa();
        }

        return (diff <= 1) and es_avl(p.primogenit(), ul) and es_avl(p.seg_germa(), ul);
    }
    else
    {
        return true;
    }
    
}

bool es_avl(Arbre<int> &a)
{
    return es_avl(a.arrel(), a.final());
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
    draw(a);

    cout << "Altura: " << altura(a) << endl;
    cout << "Level 2: ";
    print_level(a, 3);
    cout << endl;

    cout << "Es AVL ? " << (es_avl(a) ? "sí" : "no") << endl;
}