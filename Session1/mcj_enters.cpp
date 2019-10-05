#include "mcj_enters.hpp"
#include <iostream>
#include <sstream>
using namespace std;

mcj_enters::mcj_enters()
{
    m_lastIndex = -1;
}

mcj_enters::mcj_enters(const mcj_enters &cj)
{
    unsigned int i = 0, elems = cj.card();

    for (i = 0; i < elems; ++i)
    {
        m_cj[i] = cj.m_cj[i];
    }

    m_lastIndex = cj.m_lastIndex;
    m_max = cj.m_max;
    m_min = cj.m_min;
}

mcj_enters::~mcj_enters()
{
}

void mcj_enters::clean()
{
    for (unsigned int i = 0; i < card(); ++i)
    {
        m_cj[i] = 0;
    }

    m_lastIndex = -1;
}

void mcj_enters::copy(const mcj_enters &cj)
{
    unsigned int i = 0, elems = cj.card();

    for (i = 0; i < elems; ++i)
    {
        m_cj[i] = cj.m_cj[i];
    }

    m_lastIndex = cj.m_lastIndex;
    m_max = cj.m_max;
    m_min = cj.m_min;
}

void mcj_enters::insertAtEnd(int val)
{
    m_cj[card()] = val;

    ++m_lastIndex;

    if (val > m_max)
    {
        m_max = val;
    }

    if (val < m_min)
    {
        m_min = val;
    }
}

int mcj_enters::max() const
{
    //return m_max;

    return m_cj[card() - 1];
}

int mcj_enters::min() const
{
    //return m_min;
    return m_cj[0];
}

// Intercanvia els valors de la posició a per la b.
void mcj_enters::swap(unsigned int a, unsigned int b)
{

    int tmp = m_cj[b];

    m_cj[b] = m_cj[a];
    m_cj[a] = tmp;
}

// Insereix els valors ordenats de forma ascendent
void mcj_enters::insereix(int e)
{

    if (card() < MAXSIZE)
    {
        ++m_lastIndex;

        if (card() == 1)
        {
            m_max = m_min = e;
            m_cj[m_lastIndex] = e;
        }
        else
        {
            if (e > m_max)
            {
                m_max = e;
            }

            if (e < m_min)
            {
                m_min = e;
            }

            m_cj[m_lastIndex] = e;

            unsigned int i = m_lastIndex;

            // Coloca el nombre en el lloc corresponent.
            while ((i > 0) and (m_cj[i] < m_cj[i - 1]))
            {
                swap(i, i - 1);
                --i;
            }
        }
    }

    /*
    ++m_lastIndex;

    if (m_lastIndex > 0)
    {
        if (e > m_max)
        {
            m_max = e;
        }

        if (e < m_min)
        {
            m_min = e;
        }
        for (unsigned int i = 0; i < m_lastIndex; ++i)
        {
            if (m_cj[i] > e)
            {
                int aux = m_cj[i];
                m_cj[i] = e;
                e = aux;
            }
        }
    }
    else
    {
        m_max = m_min = e;
    }
    m_cj[m_lastIndex] = e;

    */
}

int mcj_enters::card() const
{
    return m_lastIndex + 1;
}

// Binary search
bool mcj_enters::conte(int e) const
{
    bool found = false;

    int first, last, middle;

    first = 0;
    last = m_lastIndex;
    middle = (first + last) / 2;

    while (first <= last and not found)
    {
        if (last >= 0)
        {
            if (m_cj[middle] < e)
                first = middle + 1;
            else if (m_cj[middle] == e)
                found = true;
            else
                last = middle - 1;

            middle = (first + last) / 2;
        }
    }

    return found;
}

void mcj_enters::unir(const mcj_enters &B)
{
    /*
    unsigned int i = 0, j = 0, cardA = card(), cardB = B.card();

    while (i < cardA and j < cardB)
    {
        if (m_cj[i] > B.m_cj[j])
        {
            insereix(B.m_cj[j]);
            ++j;
        }
        else if (m_cj[i] < B.m_cj[j])
        {
            ++i;
        }
        else
        {
            ++i;
            ++j;
        }
    }

    while (j < cardB)
    {
        insereix(B.m_cj[j]);
        ++j;
    }
    */
    /*
    if (card() > 0 and B.card() > 0)
    {
        mcj_enters tmp(*this);

        clean();

        unsigned int i = 0, j = 0, cardA = tmp.card(), cardB = B.card();

        while (i < cardA and j < cardB)
        {
            if (tmp.m_cj[i] > B.m_cj[j])
            {
                insereix(B.m_cj[j]);
                ++j;
            }
            else if (tmp.m_cj[i] < B.m_cj[j])
            {
                insereix(tmp.m_cj[i]);
                ++i;
            }
            else
            {
                insereix(tmp.m_cj[i]);
                ++i;
                ++j;
            }
        }

        while (i < cardA)
        {
            insereix(tmp.m_cj[i]);
            ++i;
        }

        while (j < cardB)
        {
            insereix(B.m_cj[j]);
            ++j;
        }
    }
    else if (card() == 0)
    {
        copy(B);
    }

    */

    mcj_enters tmp(*this + B);
    copy(tmp);
}

void mcj_enters::intersectar(const mcj_enters &B)
{
    /*
    if (card() > 0 and B.card() > 0)
    {

        mcj_enters tmp(*this);

        clean();

        unsigned int i = 0, j = 0;

        while (i < tmp.card() and j < B.card())
        {
            if (tmp.m_cj[i] < B.m_cj[j])
                ++i;
            else if (tmp.m_cj[i] > B.m_cj[j])
                ++j;
            else
            {
                insereix(tmp.m_cj[i]);
                ++i;
                ++j;
            }
        }
    }
    */
    mcj_enters tmp(*this * B);
    copy(tmp);
}

void mcj_enters::restar(const mcj_enters &B)
{
    /*
    if (card() > 0 and B.card() > 0)
    {
        mcj_enters tmp(*this);

        clean();

        unsigned int i = 0, j = 0;

        while (i < tmp.card() and j < B.card())
        {
            if (tmp.m_cj[i] < B.m_cj[j])
            {
                insereix(tmp.m_cj[i]);
                ++i;
            }
            else if (tmp.m_cj[i] > B.m_cj[j])
            {
                ++j;
            }
            else
            {
                ++i;
                ++j;
            }
        }

        while (i < tmp.card())
        {
            insereix(tmp.m_cj[i]);
            ++i;
        }
    }
    */
    mcj_enters tmp(*this - B);
    copy(tmp);
}

mcj_enters mcj_enters::operator+(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i uneix el conjunt del p.i amb B.*/
{
    /*
    mcj_enters *C = new mcj_enters(*this);

    C->unir(B);

    return *C;
    */

    mcj_enters tmp;

    if (card() > 0 and B.card() > 0)
    {
        unsigned int i = 0, j = 0, cardA = card(), cardB = B.card();

        while (i < cardA and j < cardB)
        {
            if (m_cj[i] > B.m_cj[j])
            {
                tmp.insertAtEnd(B.m_cj[j]);
                ++j;
            }
            else if (m_cj[i] < B.m_cj[j])
            {
                tmp.insertAtEnd(m_cj[i]);
                ++i;
            }
            else
            {
                tmp.insertAtEnd(m_cj[i]);
                ++i;
                ++j;
            }
        }

        while (i < cardA)
        {
            tmp.insertAtEnd(m_cj[i]);
            ++i;
        }

        while (j < cardB)
        {
            tmp.insertAtEnd(B.m_cj[j]);
            ++j;
        }
    }
    else if (card() == 0)
    {
        return B;
    }
    else
    {
        return *this;
    }

    return tmp;
}

mcj_enters mcj_enters::operator*(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i intersecta el conjunt del p.i amb B.*/
{
    /*
    mcj_enters *C = new mcj_enters(*this);

    C->intersectar(B);

    return *C;
    */

    mcj_enters tmp;

    if (card() > 0 and B.card() > 0)
    {

        unsigned int i = 0, j = 0;

        while (i < card() and j < B.card())
        {
            if (m_cj[i] < B.m_cj[j])
                ++i;
            else if (m_cj[i] > B.m_cj[j])
                ++j;
            else
            {
                tmp.insertAtEnd(m_cj[i]);
                ++i;
                ++j;
            }
        }
    }

    return tmp;
}

mcj_enters mcj_enters::operator-(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i resta el conjunt del p.i amb B.*/
{
    /*
    mcj_enters *C = new mcj_enters(*this);

    C->restar(B);

    return *C;
    */

    mcj_enters tmp;

    if (card() > 0 and B.card() > 0)
    {
        unsigned int i = 0, j = 0;

        while (i < card() and j < B.card())
        {
            if (m_cj[i] < B.m_cj[j])
            {
                tmp.insertAtEnd(m_cj[i]);
                ++i;
            }
            else if (m_cj[i] > B.m_cj[j])
            {
                ++j;
            }
            else
            {
                ++i;
                ++j;
            }
        }

        while (i < card())
        {
            tmp.insertAtEnd(m_cj[i]);
            ++i;
        }
    }
    else
    {
        return *this;
    }

    return tmp;
}

//Cost: Θ(n)
bool mcj_enters::operator==(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: true si el conjunt B es igual al del p.i, false en cas contrari*/
{
    bool same = card() == B.card();

    unsigned int i = 0;

    while (i < card() and same)
    {
        if (m_cj[i] != B.m_cj[i])
            same = false;
        ++i;
    }

    return same;
}

//Cost: Θ(n)
bool mcj_enters::operator!=(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: true si el conjunt B es diferent al del p.i, true en cas contrari*/
{

    return not(*this == B);
}

//Cost: Θ(n)
mcj_enters &mcj_enters::operator=(const mcj_enters &cj)
/*Pre: Conjunt d'enters.*/
/*Post: Crea una còpia del paràmetre en el p.i.*/
{

    if (this != &cj)
    {
        copy(cj);
    }

    return *this;
}

void mcj_enters::print(ostream &os) const
{
    os << "[";

    unsigned int i = 0;

    while (i < card())
    {
        os << m_cj[i];
        ++i;
        if (i != card())
            os << " ";
    }

    os << "]";
}
/*
int test()
{

    mcj_enters mcj;

    cout << "Set: ";

    mcj.print(cout);

    cout << endl;

    mcj.insereix(1);

    mcj.insereix(2);

    mcj.insereix(3);

    cout << "Set: ";

    mcj.print(cout);

    cout << endl;

    cout << "Max: " << mcj.max() << endl;
    cout << "Min: " << mcj.min() << endl;
    cout << "Size: " << mcj.card() << endl;

    cout << "Contain(-1): " << (mcj.conte(-1) == true ? "Yes!" : "NO!") << endl;
    //cout << "Contain(0): " << (mcj.conte(0) == true ? "Yes!" : "NO!") << endl;

    //mcj.insereix(0);

    //cout << "Contain(0): " << (mcj.conte(-1) == true ? "Yes!" : "NO!") << endl;

    mcj_enters bb;

    bb.insereix(3);

    bb.insereix(4);

    bb.insereix(5);

    cout << "Set: ";

    bb.print(cout);

    cout << endl;

    mcj_enters C;

    //---------------------------

    mcj.print(cout);

    cout << " ∪ ";

    bb.print(cout);

    cout << " = ";

    C = mcj + bb;

    C.print(cout);

    cout << endl;

    //---------------------------

    //---------------------------

    mcj.print(cout);

    cout << " ∩ ";

    bb.print(cout);

    cout << " = ";

    C = mcj * bb;

    C.print(cout);

    cout << endl;

    //---------------------------

    //---------------------------

    mcj.print(cout);

    cout << " - ";

    bb.print(cout);

    cout << " = ";

    C = mcj - bb;

    C.print(cout);

    cout << endl;

    //---------------------------
}
*/

int main()
{
    string linea, comanda;
    char cjt, cjt1, cjt2;
    int n;
    while (getline(cin, linea))
    {
        mcj_enters c[2];

        // Obtenim elements 1er conjunt
        istringstream ss1(linea);
        while (ss1 >> n)
        {
            c[0].insereix(n);
            //cout << "INSERTO 0" << endl;
        }
        c[0].print(cout);
        cout << endl;

        // Obtenim elements 2on conjunt
        getline(cin, linea);
        istringstream ss2(linea);
        while (ss2 >> n)
        {
            c[1].insereix(n);
            //cout << "INSERTO 1" << endl;
        }
        c[1].print(cout);
        cout << endl;

        // Processem comandes
        while (getline(cin, linea) and linea != "----------")
        {
            cout << linea << ": ";
            istringstream ss(linea);
            ss >> comanda;
            if (comanda == "insereix")
            {
                ss >> cjt >> n;
                c[cjt - 'A'].insereix(n);
                //cout << "INSERTO 2" << endl;
                c[cjt - 'A'].print(cout);
            }
            else if (comanda == "conte")
            {
                ss >> cjt >> n;
                cout << c[cjt - 'A'].conte(n);
            }
            else if (comanda == "max")
            {
                ss >> cjt;
                cout << c[cjt - 'A'].max();
            }
            else if (comanda == "min")
            {
                ss >> cjt;
                cout << c[cjt - 'A'].min();
            }
            else if (comanda == "card")
            {
                ss >> cjt;
                cout << c[cjt - 'A'].card();
            }
            else if (comanda == "unir")
            {
                ss >> cjt1 >> cjt2;
                c[cjt1 - 'A'].unir(c[cjt2 - 'A']);
                c[cjt1 - 'A'].print(cout);
            }
            else if (comanda == "intersectar")
            {
                ss >> cjt1 >> cjt2;
                c[cjt1 - 'A'].intersectar(c[cjt2 - 'A']);
                c[cjt1 - 'A'].print(cout);
            }
            else if (comanda == "restar")
            {
                ss >> cjt1 >> cjt2;
                c[cjt1 - 'A'].restar(c[cjt2 - 'A']);
                c[cjt1 - 'A'].print(cout);
            }
            else if (comanda == "+")
            {
                ss >> cjt1 >> cjt2;
                mcj_enters cj = c[cjt1 - 'A'] + c[cjt2 - 'A'];
                cj.print(cout);
            }
            else if (comanda == "*")
            {
                ss >> cjt1 >> cjt2;
                mcj_enters cj = c[cjt1 - 'A'] * c[cjt2 - 'A'];
                cj.print(cout);
            }
            else if (comanda == "-")
            {
                ss >> cjt1 >> cjt2;
                mcj_enters cj = c[cjt1 - 'A'] - c[cjt2 - 'A'];
                cj.print(cout);
            }
            else if (comanda == "==")
            {
                ss >> cjt1 >> cjt2;
                cout << (c[cjt1 - 'A'] == c[cjt2 - 'A']);
            }
            else if (comanda == "!=")
            {
                ss >> cjt1 >> cjt2;
                cout << (c[cjt1 - 'A'] != c[cjt2 - 'A']);
            }
            else if (comanda == "print")
            {
                ss >> cjt;
                c[cjt - 'A'].print(cout);
            }
            cout << endl;
        }
        if (linea == "----------")
            cout << linea << endl;
    }
}
