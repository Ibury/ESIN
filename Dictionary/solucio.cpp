#include <iostream>
using namespace std;

typedef unsigned int nat;

template <typename Clau>
class dicc
{

public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    dicc(const dicc &d);
    ~dicc();
    dicc &operator=(const dicc &d);

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Elimina la clau k del diccionari. Si no hi era, no fa res.
    void elimina(const Clau &k);

    // Consulta si la clau k està en el diccionari.
    bool consulta(const Clau &k) const;

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
    // Imprimeix totes les claus
    void print() const;
    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
    void print_interval(const Clau &k1, const Clau &k2) const;

    // Retorna la clau més petita i la més gran respectivament.
    // Pre: El diccionari no està buit
    Clau min() const;
    Clau max() const;

    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
    // Pre: El diccionari no està buit. 1 <= i <= quants()
    Clau iessim(nat i) const;

    // TEST PUBLIC METHODS
    unsigned int public_high(const Clau &k);

private:
    // Aquí van els atributs i mètodes privats
    struct node
    {
        Clau m_key;
        node *m_ls;
        node *m_rs;
        unsigned int m_high;
    };

    Clau m_min;
    Clau m_max;

    unsigned int m_total;

    node *m_root;

    Clau min(node *n) const;
    Clau max(node *n) const;
    unsigned int max(unsigned int a, unsigned int b);
    node *left_rotation(node *n);
    node *right_rotation(node *n);
    node *insert(const Clau &k, node *act);
    node *left_leave(node *n);
    node *remove(const Clau &k, node *n);
    void remove_all(node *n);
    node *copy_all(node *src);
    bool search(const Clau &k, node *n) const;
    unsigned int high(node *n) const;
    int balance(node *n);
    Clau iessim(nat i, nat &actual, node *n, bool &found) const;
    void print(node *n) const;
    void print_interval(const Clau &k1, const Clau &k2, node *n) const;

    // TEST PRIVATE METHODS
    unsigned int find_high(const Clau &k, node *n);
};

// Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
dicc<Clau>::dicc()
{
    m_min = m_max = (Clau)0;
    m_root = nullptr;
    m_total = 0;
}

template <typename Clau>
dicc<Clau>::dicc(const dicc &d)
{
    m_root = copy_all(d.m_root);
    m_min = d.m_min;
    m_max = d.m_max;
    m_total = d.m_total;
}

template <typename Clau>
dicc<Clau>::~dicc()
{
    remove_all(m_root);
    m_min = 0;
    m_max = 0;
    m_total = 0;
}

template <typename Clau>
dicc<Clau> &dicc<Clau>::operator=(const dicc<Clau> &d)
{
    if (this != &d)
    {
        dicc C(*this);

        node *tmp = m_root;

        m_root = C.m_root;
        C.m_root = tmp;

        unsigned int val = m_min;

        m_min = C.m_min;
        C.m_min = val;

        val = m_max;

        m_max = C.m_max;
        C.m_max = val;

        val = m_total;

        m_total = C.m_total;
        C.m_total = val;
    }

    return *this;
}

template <typename Clau>
void dicc<Clau>::insereix(const Clau &k)
{
    m_root = insert(k, m_root);
}

template <typename Clau>
void dicc<Clau>::elimina(const Clau &k)
{
    m_root = remove(k, m_root);
}

template <typename Clau>
bool dicc<Clau>::consulta(const Clau &k) const
{
    return search(k, m_root);
}

template <typename Clau>
nat dicc<Clau>::quants() const
{
    return m_total;
}

template <typename Clau>
void dicc<Clau>::print() const
{
    cout << "[";
    print(m_root);
    cout << "]";
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const
{
    cout << "[";
    print_interval(k1, k2, m_root);
    cout << "]";
}

template <typename Clau>
Clau dicc<Clau>::min() const
{
    return min(m_root);
}

template <typename Clau>
Clau dicc<Clau>::max() const
{
    return max(m_root);
}

template <typename Clau>
Clau dicc<Clau>::iessim(nat i) const
{
    unsigned int node = 0;
    bool found = false;
    return iessim(i, node, m_root, found);
}

template <typename Clau>
Clau dicc<Clau>::min(node *n) const
{
    node *prev = nullptr;

    while (n != nullptr)
    {
        prev = n;
        n = n->m_ls;
    }

    return prev->m_key;
}

template <typename Clau>
Clau dicc<Clau>::max(node *n) const
{
    node *prev = nullptr;

    while (n != nullptr)
    {
        prev = n;
        n = n->m_rs;
    }

    return prev->m_key;
}

template <typename Clau>
unsigned int dicc<Clau>::max(unsigned int a, unsigned int b)
{
    if (a < b)
        return b;
    else
        return a;
}

template <typename Clau>
unsigned int dicc<Clau>::high(node *n) const
{
    if (n != nullptr)
        return n->m_high;
    else
        return 0;
}

template <typename Clau>
int dicc<Clau>::balance(node *n)
{
    if (n != nullptr)
        return high(n->m_ls) - high(n->m_rs);
    else
        return 0;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::left_rotation(node *n)
{
    node *a = n;
    node *c = n->m_rs;

    a->m_rs = c->m_ls;
    c->m_ls = a;

    a = c;

    a->m_high = max(high(a->m_ls), high(a->m_rs)) + 1;
    c->m_high = max(high(c->m_ls), high(c->m_rs)) + 1;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::right_rotation(node *n)
{
    node *a = n;
    node *c = n->m_ls;

    a->m_ls = c->m_rs;
    c->m_rs = a;

    a = c;

    a->m_high = max(high(a->m_ls), high(a->m_rs)) + 1;
    c->m_high = max(high(c->m_ls), high(c->m_rs)) + 1;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::insert(const Clau &k, node *act)
{
    node *n = nullptr;

    if (act != nullptr)
    {
        if (k > act->m_key)
        {
            act->m_rs = insert(k, act->m_rs);
        }
        else if (k < act->m_key)
        {
            act->m_ls = insert(k, act->m_ls);
        }
        else
        { // Duplicated node !!
            return act;
        }

        act->m_high = max(high(act->m_ls), high(act->m_rs)) + 1;

        int b = balance(act);

        // Simple cases
        // ##############################################################

        // Left
        if (b > 1 and k < act->m_ls->m_key)
        {
            return right_rotation(act);
        }

        // Right
        if (b < -1 and k > act->m_rs->m_key)
        {
            return left_rotation(act);
        }
        // ##############################################################

        // Two step cases
        // ##############################################################

        // Left-Right
        if (b > 1 and k > act->m_ls->m_key)
        {
            act->m_ls = left_rotation(act->m_ls);
            return right_rotation(act);
        }

        // Right-Left
        if (b < -1 and k < act->m_rs->m_key)
        {
            act->m_rs = right_rotation(act->m_rs);
            return left_rotation(act);
        }
        // ##############################################################

        return act;
    }
    else
    {
        n = new node;
        n->m_key = k;
        n->m_ls = n->m_rs = NULL;
        n->m_high = 1;
        ++m_total;
    }

    return n;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::left_leave(node *n)
{
    node *tmp = n;

    while (tmp->m_ls != nullptr)
    {
        tmp = tmp->m_ls;
    }

    return tmp;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::remove(const Clau &k, node *n)
{

    if (n != nullptr)
    {
        if (k < n->m_key)
        {
            n->m_ls = remove(k, n->m_ls);
        }
        else if (k > n->m_key)
        {
            n->m_rs = remove(k, n->m_rs);
        }
        else
        {
            if (n->m_ls == nullptr or n->m_rs == nullptr)
            {
                node *tmp = (n->m_ls != nullptr) ? n->m_ls : n->m_rs;

                if (tmp == nullptr)
                {
                    tmp = n;
                    --m_total;
                }
                else
                {
                    *n = *tmp;
                    --m_total;
                }
                delete tmp;
                return nullptr;
            }
            else
            {
                node *tmp = left_leave(n->m_rs);
                n->m_key = tmp->m_key;
                n->m_rs = remove(tmp->m_key, n->m_rs);
            }

            if (n != nullptr)
            {
                if (n->m_ls != nullptr and n->m_rs != nullptr)
                {
                    n->m_high = max(high(n->m_ls), high(n->m_rs)) + 1;
                }
                else if (n->m_ls != nullptr and n->m_rs == nullptr)
                {
                    n->m_high = n->m_ls->m_high + 1;
                }
                else if (n->m_ls == nullptr and n->m_rs != nullptr)
                {
                    n->m_high = n->m_rs->m_high + 1;
                }
            }

            int b = balance(n);

            if (b > 1 && balance(n->m_ls) >= 0)
            {
                return right_rotation(n);
            }

            if (b > 1 && balance(n->m_ls) < 0)
            {
                n->m_ls = left_rotation(n->m_ls);
                return right_rotation(n);
            }

            if (b < -1 && balance(n->m_rs) <= 0)
            {
                return left_rotation(n);
            }

            if (b < -1 && balance(n->m_rs) > 0)
            {
                n->m_rs = right_rotation(n->m_rs);
                return left_rotation(n);
            }
        }
    }

    return n;
}

template <typename Clau>
void dicc<Clau>::remove_all(node *n)
{
    if (n != nullptr)
    {
        remove_all(n->m_ls);
        remove_all(n->m_rs);
        delete n;
    }
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::copy_all(node *src)
{
    if (src != nullptr)
    {
        node *n = new node;

        n->m_key = src->m_key;
        n->m_total = src->m_total;
        n->m_ls = copy_all(src->m_ls);
        n->m_rs = copy_all(src->m_rs);
    }
}

template <typename Clau>
bool dicc<Clau>::search(const Clau &k, node *n) const
{
    if (n != nullptr)
    {
        if (n->m_key == k)
            return true;
        else
        {
            if (k < n->m_key and n->m_ls != nullptr)
            {
                return search(k, n->m_ls);
            }
            else if (k > n->m_key and n->m_rs != nullptr)
            {
                return search(k, n->m_rs);
            }
        }
    }
    else
    {
        return false;
    }

    return false;
}

template <typename Clau>
Clau dicc<Clau>::iessim(nat i, nat &actual, node *n, bool &found) const
{
    Clau res;
    if (n != nullptr)
    {

        res = iessim(i, actual, n->m_ls, found);
        ++actual;
        if (actual == i)
        {
            found = true;
            return n->m_key;
        }

        if (not found)
            res = iessim(i, actual, n->m_rs, found);
    }

    return res;
}

template <typename Clau>
void dicc<Clau>::print(node *n) const
{
    if (n != nullptr)
    {
        print(n->m_ls);
        cout << n->m_key;
        if (n->m_key != m_max)
            cout << " ";
        print(n->m_rs);
    }
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2, node *n) const
{
    if (n != nullptr)
    {
        if (k1 <= n->m_key and n->m_key <= k2)
        {
            print_interval(k1, k2, n->m_ls);
            cout << n->m_key;
            if (n->m_key != k2)
                cout << " ";
            print_interval(k1, k2, n->m_rs);
        }
        else
        {
            print_interval(k1, k2, n->m_ls);
            print_interval(k1, k2, n->m_rs);
        }
    }
}

// TEST METHODS
template <typename Clau>
unsigned int dicc<Clau>::find_high(const Clau &k, node *n)
{
    if (n != nullptr)
    {
        if (n->m_key == k)
            return n->m_high;
        else
        {
            if (k < n->m_key and n->m_ls != nullptr)
            {
                return search(k, n->m_ls);
            }
            else if (k > n->m_key and n->m_rs != nullptr)
            {
                return search(k, n->m_rs);
            }
        }
    }
    else
    {
        return 0;
    }

    return 0;
}

template <typename Clau>
unsigned int dicc<Clau>::public_high(const Clau &k)
{
    return find_high(k, m_root);
}