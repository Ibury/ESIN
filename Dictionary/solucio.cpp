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

private:
    // Aquí van els atributs i mètodes privats
    struct node
    {
        Clau m_key;
        node *m_ls;
        node *m_rs;
        nat m_high;
    };

    Clau m_min;
    Clau m_max;

    nat m_total;

    node *m_root;

    Clau min(node *n) const;
    Clau max(node *n) const;
    nat max(nat a, nat b);
    node *left_rotation(node *n);
    node *right_rotation(node *n);
    node *insert(const Clau &k, node *act);
    node *left_leave(node *n);
    node *remove(const Clau &k, node *n);
    void remove_all(node *n);
    node *copy_all(node *src);
    bool search(const Clau &k, node *n) const;
    nat high(node *n) const;
    int balance(node *n);
    Clau iessim(nat i, nat &actual, node *n, bool &found) const;
    void print(node *n, string &str) const;
    void print_interval(const Clau &k1, const Clau &k2, node *n, string &str) const;
};

// Aquí va la implementació dels mètodes públics i privats

#include <string>
#include <sstream>

// FIX: g++-5 does not support to_string method from std.
namespace patch
{
template <typename T>
std::string to_string(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
} // namespace patch

template <typename Clau>
dicc<Clau>::dicc()
{
    m_min = m_max = (Clau)0;
    m_root = NULL;
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

        nat val = m_min;

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
    string str = "";

    cout << "[";
    print(m_root, str);
    cout << str.substr(0, str.size() - 1) << "]";
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const
{
    string str = "";

    cout << "[";
    print_interval(k1, k2, m_root, str);
    cout << str.substr(0, str.size() - 1) << "]";
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
    nat node = 0;
    bool found = false;
    return iessim(i, node, m_root, found);
}

template <typename Clau>
Clau dicc<Clau>::min(node *n) const
{
    node *prev = NULL;

    while (n != NULL)
    {
        prev = n;
        n = n->m_ls;
    }

    return prev->m_key;
}

template <typename Clau>
Clau dicc<Clau>::max(node *n) const
{
    node *prev = NULL;

    while (n != NULL)
    {
        prev = n;
        n = n->m_rs;
    }

    return prev->m_key;
}

template <typename Clau>
nat dicc<Clau>::max(nat a, nat b)
{
    if (a < b)
        return b;
    else
        return a;
}

template <typename Clau>
nat dicc<Clau>::high(node *n) const
{
    if (n != NULL)
        return n->m_high;
    else
        return 0;
}

template <typename Clau>
int dicc<Clau>::balance(node *n)
{
    if (n != NULL)
        return high(n->m_ls) - high(n->m_rs);
    else
        return 0;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::left_rotation(node *n)
{
    node *a = n->m_rs;
    node *c = a->m_ls;

    a->m_ls = n;
    n->m_rs = c;

    n->m_high = max(high(n->m_ls), high(n->m_rs)) + 1;
    a->m_high = max(high(a->m_ls), high(a->m_rs)) + 1;

    return a;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::right_rotation(node *n)
{
    node *a = n->m_ls;
    node *c = a->m_rs;

    a->m_rs = n;
    n->m_ls = c;

    n->m_high = max(high(n->m_ls), high(n->m_rs)) + 1;
    a->m_high = max(high(a->m_ls), high(a->m_rs)) + 1;

    return a;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::insert(const Clau &k, node *act)
{
    node *n = NULL;

    if (act != NULL)
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

        // Left-Left
        if (b > 1 and k < act->m_ls->m_key)
        {
            return right_rotation(act);
        }

        // Right-Right
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

    while (tmp->m_ls != NULL)
    {
        tmp = tmp->m_ls;
    }

    return tmp;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::remove(const Clau &k, node *n)
{

    if (n != NULL)
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
            if (n->m_ls == NULL or n->m_rs == NULL)
            {
                node *tmp = (n->m_ls != NULL) ? n->m_ls : n->m_rs;

                if (tmp == NULL)
                {
                    tmp = n;
                    --m_total;
                    n = NULL;
                }
                else
                {
                    *n = *tmp;
                    --m_total;
                }
                delete tmp;
            }
            else
            {
                node *tmp = left_leave(n->m_rs);
                n->m_key = tmp->m_key;
                n->m_rs = remove(tmp->m_key, n->m_rs);
            }

            if (n == NULL)
                return n;

            n->m_high = max(high(n->m_ls), high(n->m_rs));

            int b = balance(n);

            // Simple cases
            // ##############################################################

            // Left-Left
            if (b > 1 and balance(n->m_ls) >= 0)
            {
                return right_rotation(n);
            }

            // Left-Right
            if (b > 1 and balance(n->m_ls) < 0)
            {
                n->m_ls = left_rotation(n->m_ls);
                return right_rotation(n);
            }
            // ##############################################################

            // Two step cases
            // ##############################################################

            // Right-Right
            if (b < -1 and balance(n->m_rs) <= 0)
            {
                return left_rotation(n);
            }

            // Right-Left
            if (b < -1 and balance(n->m_rs) > 0)
            {
                n->m_rs = right_rotation(n->m_rs);
                return left_rotation(n);
            }
            // ##############################################################
        }
    }

    return n;
}

template <typename Clau>
void dicc<Clau>::remove_all(node *n)
{
    if (n != NULL)
    {
        remove_all(n->m_ls);
        remove_all(n->m_rs);
        delete n;
    }
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::copy_all(node *src)
{
    if (src != NULL)
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
    if (n != NULL)
    {
        if (n->m_key == k)
            return true;
        else
        {
            if (k < n->m_key and n->m_ls != NULL)
            {
                return search(k, n->m_ls);
            }
            else if (k > n->m_key and n->m_rs != NULL)
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
    if (n != NULL)
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
void dicc<Clau>::print(node *n, string &str) const
{
    if (n != NULL)
    {
        print(n->m_ls, str);
        str += patch::to_string(n->m_key) + " ";
        print(n->m_rs, str);
    }
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2, node *n, string &str) const
{
    if (n != NULL)
    {
        if (k1 < n->m_key and k2 < n->m_key)
        {
            print_interval(k1, k2, n->m_ls, str);
        }
        else if (k1 > n->m_key and k2 > n->m_key)
        {
            print_interval(k1, k2, n->m_rs, str);
        }
        else if (k1 <= n->m_key and n->m_key <= k2)
        {
            print_interval(k1, k2, n->m_ls, str);
            str += patch::to_string(n->m_key) + " ";
            print_interval(k1, k2, n->m_rs, str);
        }
        else
        {
            print_interval(k1, k2, n->m_ls, str);
            print_interval(k1, k2, n->m_ls, str);
        }
    }
}