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
        unsigned int m_high;
    };

    Clau m_min;
    Clau m_max;

    node *m_root;

    void insert(const Clau &k, node *prev, node *act);
    void remove(const Clau &k, node *n);
    void remove_all(node *n);
    node *copy_all(node *src);
    bool search(const Clau &k, node *n) const;
    unsigned int high(node *n) const;
    void print(node *n) const;
    void print_interval(const Clau &k1, const Clau &k2, node *n) const;
};

// Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
dicc<Clau>::dicc()
{
    m_min = m_max = (Clau) 0;
    m_root = nullptr;
}

template <typename Clau>
dicc<Clau>::dicc(const dicc &d)
{
    m_root = copy_all(d.m_root);
    m_min = d.m_min;
    m_max = d.m_max;
}

template <typename Clau>
dicc<Clau>::~dicc()
{
    remove_all(m_root);
    m_min = 0;
    m_max = 0;
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
    }

    return *this;
}

template <typename Clau>
void dicc<Clau>::insereix(const Clau &k)
{
    if (m_root == nullptr)
    {
        m_root = new node;

        m_root->m_ls = m_root->m_rs = nullptr;
        m_root->m_high = high(m_root);

        m_root->m_key = k;
    }
    else
    {
        insert(k, nullptr, m_root);
    }
}

template <typename Clau>
void dicc<Clau>::elimina(const Clau &k)
{
}

template <typename Clau>
bool dicc<Clau>::consulta(const Clau &k) const
{
    return search(k, m_root);
}

template <typename Clau>
nat dicc<Clau>::quants() const
{
    return m_root->m_total;
}

template <typename Clau>
void dicc<Clau>::print() const
{
    print(m_root);
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const
{
    print_interval(k1, k2, m_root);
}

template <typename Clau>
Clau dicc<Clau>::min() const
{
    return m_min;
}

template <typename Clau>
Clau dicc<Clau>::max() const
{
    return m_max;
}

template <typename Clau>
Clau dicc<Clau>::iessim(nat i) const
{
}

template <typename Clau>
unsigned int dicc<Clau>::high(node *n) const
{
    if (n->ls == nullptr and n->rs != nullptr)
    {
        return n->rs->m_high;
    }
    else if (n->ls != nullptr and n->rs == nullptr)
    {
        return n->ls->m_high;
    }
    else if (n->ls != nullptr and n->rs != nullptr)
    {
        return max(n->ls->m_high, n->rs->m_high);
    }
    else
    {
        return 1;
    }
}

template <typename Clau>
void dicc<Clau>::insert(const Clau &k, node *prev, node *act)
{
    if (act != nullptr)
    {

        if (k < act->m_key)
        {
            if (act->m_ls == nullptr)
            {
                node *n = new node;

                n->m_key = k;
                n->m_ls = n->m_fs = nullptr;
                n->m_high = 1;

                ++act->m_high;
            }
            else
            {
                insert(k, act, act->m_ls);
                insert(k, act, act->m_rs);
            }
        }
        else if (k > act->m_key)
        {
            if (act->m_rs == nullptr)
            {
                node *n = new node;

                n->m_key = k;
                n->m_ls = n->m_fs = nullptr;
                n->m_high = 1;

                ++act->m_high;
            }
            else
            {
                insert(k, act, act->m_ls);
                insert(k, act, act->m_rs);
            }
        }


        act->high = high(act);
    }
}

template <typename Clau>
void dicc<Clau>::remove(const Clau &k, node *n)
{
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
            if (not search(k, n->m_ls))
                return search(k, n->m_fs);
        }
    }
    else
    {
        return false;
    }
}

template <typename Clau>
void dicc<Clau>::print(node *n) const
{
    if (n != nullptr)
    {
        print(n->m_ls);
        cout << n->m_key;
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
            print_interval(k1, k2, n->ls);
            cout << n->m_key << ", ";
            print_interval(k1, k2, n->rs);
        }
        else
        {
            print_interval(k1, k2, n->ls);
            print_interval(k1, k2, n->rs);
        }
    }
}