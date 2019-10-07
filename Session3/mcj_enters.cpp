#include "mcj_enters.hpp"
#include <iostream>
#include <sstream>
using namespace std;

//Cost: Θ(1)
mcj_enters::mcj_enters()
{
    setup();
}

//Cost: Θ(n)
mcj_enters::mcj_enters(const mcj_enters &cj)
{
    setup();
    copy(cj);
}

//Cost: Θ(n)
mcj_enters::~mcj_enters()
{
    node *prev = m_ghost;

    while (prev != nullptr)
    {
        m_first = prev->next;
        delete prev;
        prev = m_first;
    }
}

//Cost: Θ(1)
void mcj_enters::setup()
{
    m_ghost = new node{0, nullptr};
    m_first = nullptr;
    m_last = nullptr;
}

//Cost: Θ(n)
void mcj_enters::copy(const mcj_enters &cj)
{
    node *tmpA = m_first;
    node *tmpB = cj.m_first;
    node *prev = m_ghost;

    if (tmpB != nullptr)
    {

        while (tmpA != nullptr and tmpB != nullptr)
        {
            tmpA->info = tmpB->info;

            m_last = tmpA;

            forward(tmpA);
            forward(tmpB);
            forward(prev);
        }

        // If we arrive here it means that cj has more elems than p.i. so delete extra elems.
        if (tmpB == nullptr and tmpA != nullptr)
        {

            m_last = tmpA;
            m_last->next = nullptr;

            while (tmpA != nullptr)
            {
                remove(prev, tmpA);
                forward(tmpA);
            }
        }
        else if (tmpA == nullptr and tmpB != nullptr) // If we arrive here it means that B is bigger than p.i. so we have to add rest elems to p.i.
        {
            while (tmpB != nullptr)
            {
                insereix(tmpB->info);
                forward(tmpB);
            }
        }
    }
    else // It means that B is empty, therefore, we're going to remove all elements from p.i.
    {
        while (tmpA != nullptr)
        {
            remove(prev, tmpA);
            forward(tmpA);
        }
    }
}

//Cost: Θ(1)
void mcj_enters::swap(mcj_enters &cj)
{
    node *tmp = m_ghost;
    m_ghost = cj.m_ghost;
    cj.m_ghost = tmp;

    cj.m_first = m_first;
    m_first = m_ghost->next;

    tmp = m_last;
    m_last = cj.m_last;
    cj.m_last = tmp;
}

//Cost: Θ(1)
void mcj_enters::forward(node *&curr)
{
    //FIXME: TEST
    if (curr != nullptr)
    {
        if (curr != curr->next)
            curr = curr->next;
        else
        {
            curr = nullptr;
        }
    }
}

//Cost: Θ(1)
void mcj_enters::insertAtEnd(int val)
{
    m_last->next = new node{val, nullptr};
    forward(m_last);
}

//Cost: Θ(1)
// Pre: Previous is the predecessor node of current.
// Post: The successor of previous is going to be the successor of current so current is going to be eliminated.
void mcj_enters::remove(node *&previous, node *&current)
{

    if (current == m_first)
    {
        m_first = current->next;
        previous->next = m_first;

        // First elem. can be last elem.
        if (current == m_last)
            m_last = nullptr;
    }
    else if (current == m_last)
    {
        m_last = previous;
        m_last->next = nullptr;
    }
    else
    {
        previous->next = current->next;
    }

    if (current != nullptr) delete current;
    current = previous;

    if (m_ghost != nullptr and m_ghost->info > 0)
        --m_ghost->info;
}

//Cost: Θ(n)
// Insereix els valors ordenats de forma ascendent
void mcj_enters::insereix(int e)
{

    if (card() == 0)
    {
        m_ghost->next = new node{e, nullptr};
        m_last = m_first = m_ghost->next;
    }
    else
    {
        if (e <= m_first->info)
        {
            m_ghost->next = new node{e, m_first};
            m_first = m_ghost->next;
        }
        else if (e > m_last->info)
        {
            insertAtEnd(e);
        }
        else
        {
            // Forward one step because we have already analyzed the first elem.
            node *prev = m_first, *aux = m_first->next;
            bool inserted = false;

            while (aux != nullptr and not inserted)
            {

                // FIXME: Maybe it's here the focus of the problem.
                if (aux != nullptr)
                {

                    if (aux->info >= e)
                    {
                        prev->next = new node{e, aux};
                        inserted = true;
                    }
                    else
                    {
                        forward(prev);
                        forward(aux);
                    }
                }
            }
        }
    }

    ++m_ghost->info;
}

//Cost: Θ(n)
void mcj_enters::unir(const mcj_enters &B)
{
    mcj_enters tmp;

    if (card() > 0 and B.card() > 0)
    {

        node *i = m_first, *j = B.m_first;

        while (i != nullptr and j != nullptr)
        {
            if (i->info > j->info)
            {
                tmp.insereix(j->info);
                forward(j);
            }
            else if (i->info < j->info)
            {
                tmp.insereix(i->info);
                forward(i);
            }
            else
            {
                tmp.insereix(i->info);
                forward(i);
                forward(j);
            }
        }

        while (i != nullptr)
        {
            tmp.insereix(i->info);
            forward(i);
        }

        while (j != nullptr)
        {
            tmp.insereix(j->info);
            forward(j);
        }

        copy(tmp);
    }
    else if (card() == 0)
    {
        copy(B);
    }
}

//Cost: Θ(n)
void mcj_enters::intersectar(const mcj_enters &B)
{
    node *i = m_first, *j = B.m_first, *prev = m_ghost;

    while (i != nullptr and j != nullptr)
    {

        if (i->info < j->info)
        {
            remove(prev, i);
            forward(i);
        }
        else if (i->info > j->info)
            forward(j);
        else
        {
            forward(prev);
            forward(i);
            forward(j);
        }
    }

    while (i != nullptr)
    {
        remove(prev, i);
        forward(i);
    }
}

//Cost: Θ(n)
void mcj_enters::restar(const mcj_enters &B)
{
    node *i = m_first, *j = B.m_first, *prev = m_ghost;

    if (this != &B)
    {
        while (i != nullptr and j != nullptr)
        {
            if (i->info < j->info)
            {
                forward(prev);
                forward(i);
            }
            else if (i->info > j->info)
            {
                forward(j);
            }
            else
            {
                remove(prev, i);
                forward(i);
                forward(j);
            }
        }
    }
    else
    {
        while (i != nullptr)
        {
            remove(prev, i);
            forward(i);
        }
    }
    
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator+(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i uneix el conjunt del p.i amb B.*/
{
    mcj_enters C(*this);

    C.unir(B);

    return C;
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator*(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i intersecta el conjunt del p.i amb B.*/
{
    mcj_enters C(*this);

    C.intersectar(B);

    return C;
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator-(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i resta el conjunt del p.i amb B.*/
{
    mcj_enters C(*this);

    C.restar(B);

    return C;
}

//Cost: Θ(n)
bool mcj_enters::operator==(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: true si el conjunt B es igual al del p.i, false en cas contrari*/
{
    bool same = card() == B.card();

    node *tmpA = m_first, *tmpB = B.m_first;

    // It's not needed check both pointers cause there is a previous checking of the length so when
    // on of them finishes the other one it does too.
    while ((tmpA != nullptr and tmpB != nullptr) and same)
    {
        if (tmpA->info != tmpB->info)
            same = false;

        // FIXME: Test
        if (tmpA != nullptr)
            tmpA = tmpA->next;

        if (tmpB != nullptr)
            tmpB = tmpB->next;
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
        mcj_enters C(cj);
        swap(C);
    }

    return *this;
}

//Cost: Θ(1)
int mcj_enters::max() const
{
    // FIXME: It shouldn't happen never... unless the p.i it would be empty.
    if (m_last == nullptr)
        return 0;

    return m_last->info;
}

//Cost: Θ(1)
int mcj_enters::min() const
{
    // FIXME: It shouldn't happen never... unless the p.i it would be empty.
    if (m_first == nullptr)
        return 0;

    return m_first->info;
}

//Cost: Θ(1)
int mcj_enters::card() const
{
    // FIXME: It shouldn't happen never...
    if (m_ghost == nullptr)
        return 0;

    return m_ghost->info;
}

//Cost: Θ(n)
bool mcj_enters::conte(int e) const
{
    bool found = false;

    if ((m_first != nullptr) and (e >= min() and e <= max()))
    {
        node *tmp = m_first;

        while (tmp != nullptr and not found)
        {
            if (tmp->info == e)
                found = true;

            // FIXME: Test
            if (tmp != nullptr)
                tmp = tmp->next;
        }
    }

    return found;
}

//Cost: Θ(n)
void mcj_enters::print(ostream &os) const
{
    os << "[";

    node *tmp = m_first;

    while (tmp != nullptr)
    {
        os << tmp->info;
        tmp = tmp->next;
        if (tmp != nullptr)
        {
            os << " ";
            // FIXME: Test
            if (tmp == tmp->next)
                tmp = nullptr;
        }
    }

    os << "]";
}

void mcj_enters::test(int val)
{
    node *prev = m_ghost, *curr = m_first;

    while (curr != nullptr)
    {   
        if (curr->info == val)
            remove(prev, curr);

        forward(prev);
        forward(curr);
    } 
}