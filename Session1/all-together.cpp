#ifndef _MCJ_ENTERS_HPP_
#define _MCJ_ENTERS_HPP_
#include <iostream>
#include <array>
using namespace std;

class mcj_enters
{

public:
    // Constructora per defecte. Crea un multiconjunt buit.
    mcj_enters();

    // Les tres grans: Constructora per còpia, destructora, operador d'assignació
    mcj_enters(const mcj_enters &cj);
    ~mcj_enters();
    mcj_enters &operator=(const mcj_enters &cj);

    // Insereix l’enter e en el multiconjunt.
    void insereix(int e);

    // Unió, intersecció i diferència de multiconjunts. Operen modificant el multiconjunt sobre el que s’aplica
    // el mètode, usant el segon multiconjunt com argument. P.e.: a.restar(b) fa que el nou valor d’a sigui
    // A - B, on A i B són els valors originals dels objectes a i b.
    void unir(const mcj_enters &B);
    void intersectar(const mcj_enters &B);
    void restar(const mcj_enters &B);

    // Unió, intersecció i diferència de multiconjunts. Operen creant un nou multiconjunt sense modificar el con-
    // junt sobre el que s’aplica el mètode. La suma de multiconjunts correspon a la unió, la resta a la
    // diferència i el producte a la intersecció.
    mcj_enters operator+(const mcj_enters &B) const;
    mcj_enters operator*(const mcj_enters &B) const;
    mcj_enters operator-(const mcj_enters &B) const;

    // Retorna cert si i només si e pertany al multiconjunt.
    bool conte(int e) const;

    // Retornen els elements màxim i mínim del multiconjunt, respectivament.
    // El seu comportament no està definit si el multiconjunt és buit.
    int max() const;
    int min() const;

    // Retorna el nombre d’elements (la cardinalitat) del multiconjunt.
    int card() const;

    // Operadors relacionals. == retorna cert si i només si els
    // dos multiconjunts (el paràmetre implícit i B) contenen els
    // mateixos elements; != retorna cert si i només si els
    // multiconjunts són diferents.
    bool operator==(const mcj_enters &B) const;
    bool operator!=(const mcj_enters &B) const;

    // Imprimeix el multiconjunt d’enters, ordenats en ordre ascendent, sobre
    // el canal de sortida os; el format és [e1 e2 ... en], és a dir, amb
    // espais entre els elements i tancant la seqüència amb corxets.
    void print(ostream &os) const;

private:
    // Aqui van els atributs i metodes privats
    const static unsigned int MAXSIZE = 20000;
    int m_cj[MAXSIZE];
    int m_lastIndex = -1;
    int m_max;
    int m_min;

    unsigned int m_max_pos;
    unsigned int m_min_pos;

    void swap(unsigned int a, unsigned int b);
    void copy(const mcj_enters &cj);
    void insertAtEnd(int val);
    void clean();
};
#endif #include "mcj_enters.hpp"
mcj_enters::mcj_enters()
{
    m_lastIndex = -1;
    m_min = m_max = 0;
}

mcj_enters::mcj_enters(const mcj_enters &cj)
{
    copy(cj);
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
    return m_cj[card()-1];
    //return m_max;
}

int mcj_enters::min() const
{
    return m_cj[0];
    //return m_min;
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