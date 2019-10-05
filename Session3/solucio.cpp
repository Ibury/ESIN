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

  void test(int val);

private:
  // Aqui van els atributs i metodes privats

  struct node
  {
    int info;
    node *next;
  };

  node *m_ghost;
  node *m_first;
  node *m_last;

  void copy(const mcj_enters &cj);
  void insertAtEnd(int val);
  void remove(node *&previous, node *&current);
  void swap(mcj_enters &cj);
  void forward(node *&curr);
  void setup();
};
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

    m_last = m_first = nullptr;
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
    /*
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
    else // It means that B is empty, therefore, we're going to remove all elements using swap trick.
    {
        mcj_enters C = mcj_enters();
        swap(C);
    }
    */

    mcj_enters *C = new mcj_enters();

    node *B = cj.m_first;

    while (B != nullptr)
    {
        C->insereix(B->info);
        forward(B);
    }

    swap(*C);
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

    delete current;
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
    mcj_enters tmp(*this + B);
    copy(tmp);
}

//Cost: Θ(n)
void mcj_enters::intersectar(const mcj_enters &B)
{
    mcj_enters tmp(*this * B);
    copy(tmp);
}

//Cost: Θ(n)
void mcj_enters::restar(const mcj_enters &B)
{
    mcj_enters tmp(*this - B);
    copy(tmp);
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator+(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i uneix el conjunt del p.i amb B.*/
{
    mcj_enters *tmp = new mcj_enters();

    if (card() > 0 and B.card() > 0)
    {

        node *i = m_first, *j = B.m_first;

        while (i != nullptr and j != nullptr)
        {
            if (i->info > j->info)
            {
                tmp->insereix(j->info);
                j = j->next;
            }
            else if (i->info < j->info)
            {
                tmp->insereix(i->info);
                i = i->next;
            }
            else
            {
                tmp->insereix(i->info);
                i = i->next;
                j = j->next;
            }
        }

        while (i != nullptr)
        {
            tmp->insereix(i->info);
            i = i->next;
        }

        while (j != nullptr)
        {
            tmp->insereix(j->info);
            j = j->next;
        }

        return *tmp;
    }
    else if (card() == 0)
    {
        return B;
    }

    return *this;
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator*(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i intersecta el conjunt del p.i amb B.*/
{

    mcj_enters tmp = mcj_enters();

    node *i = m_first, *j = B.m_first;

    while (i != nullptr and j != nullptr)
    {

        if (i->info < j->info)
        {
            i = i->next;
        }
        else if (i->info > j->info)
            j = j->next;
        else
        {
            tmp.insereix(i->info);
            i = i->next;
            j = j->next;
        }
    }

    return tmp;
}

//Cost: Θ(3n)
mcj_enters mcj_enters::operator-(const mcj_enters &B) const
/*Pre: Conjunt d'enters.*/
/*Post: Crea un nou conjunt i resta el conjunt del p.i amb B.*/
{
    mcj_enters tmp = mcj_enters();

    node *i = m_first, *j = B.m_first;

    if (i == nullptr or j == nullptr)
        return *this;

    while (i != nullptr and j != nullptr)
    {
        if (i->info < j->info)
        {
            tmp.insereix(i->info);
            i = i->next;
        }
        else if (i->info > j->info)
        {
            j = j->next;
        }
        else
        {
            i = i->next;
            j = j->next;
        }
    }

    while (i != nullptr)
    {
        tmp.insereix(i->info);
        i = i->next;
    }

    return tmp;
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
        mcj_enters *C = new mcj_enters(cj);
        swap(*C);
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