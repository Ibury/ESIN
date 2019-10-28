#include <iostream>
#include <cstddef>
using namespace std;

template <typename T>
class Abin {
  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;
    static node* copia_nodes(node* m);
    static void esborra_nodes(node* m);

    static node* insereix_bst(node* n, const T &k );
    static node* consulta_bst(node* n, const T &k );

  public:
    //constructors
    Abin(): _arrel(NULL) {};
    /* Pre: cert */
    /* Post: el resultat és un arbre sense cap element */
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos subarbres */

    void insereix_bst( const T &k ) ;
    // Pre: cert
    // Post: L’element k s’ha inserit en el p.i. tenint en compte que és un BST

    bool consulta_bst ( const T &k ) const ;
    // Pre: cert
    // Post: Retorna true si l’element k està en el p.i. tenint en compte que és un BST

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T>& operator=(const Abin<T>& a);

    // Iterador sobre arbres binaris.
    friend class iterador;
    class iterador {
      private:
        Abin<T>::node* _p;

      public:
        friend class Abin;
        iterador(): _p(NULL) {};
        /* Pre: cert */
        /* Post: Construeix un iterador no vàlid. */

        Abin<T> arbre() const;
        /* Pre: cert */
        /* Post: Retorna el subarbre al que apunta l'iterador; llança un error
        si l'iterador no és vàlid. */

        T operator*() const;
        /* Pre: cert */
        /* Post: Retorna l'element en el node al que apunta l'iterador, o
        llança un error si l'iterador no és vàlid. */

        iterador fesq() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill esquerre; llança
        un error si l'iterador no és vàlid. */

        iterador fdret() const;
        /* Pre: cert */
        /* Post: Retorna un iterador al fill dret; llança
        un error si l'iterador no és vàlid. */

        /* Operadors de comparació. */
        bool operator==(const iterador &it) const {
          return _p == it._p;
        };
        bool operator!=(const iterador &it) const {
          return _p != it._p;
        };
        static const int IteradorInvalid = 410;
    };

    //consultors
    bool es_buit() const;
    /* Pre: cert */
    /* Post: el resultat indica si el p.i. és buit o no */

    iterador arrel() const;
    /* Pre: cert */
    /* Post: Retorna un iterador al node arrel. */
    
    iterador final() const;
    /* Pre: cert */
    /* Post: Retorna un iterador no vàlid. */
};


template <typename T>
typename Abin<T>::node *Abin<T>::copia_nodes(node *m)
{
  /* Pre: cert */
  /* Post: si m és NULL, el resultat és NULL; sinó,
   el resultat apunta al primer node d'un arbre binari
   de nodes que són còpia de l'arbre apuntat per m */
  node *n;
  if (m == NULL)
    n = NULL;
  else
  {
    n = new node;
    try
    {
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    }
    catch (...)
    {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void Abin<T>::esborra_nodes(node *m)
{
  /* Pre: cert */
  /* Post: no fa res si m és NULL, sinó allibera
   espai dels nodes de l'arbre binari apuntat per m */
  if (m != NULL)
  {
    esborra_nodes(m->f_dret);
    delete m;
  }
};

template <typename T>
typename Abin<T>::node *Abin<T>::insereix_bst(node *n, const T &k)
{
  if (n != NULL)
  {
    if (k > n->info)
    {
      if (n->f_dret != NULL)
        insereix_bst(n->f_dret, k);
      else
      {
        n->f_dret = new node;
        n->f_dret->info = k;
        n->f_dret->f_esq = n->f_dret->f_dret = NULL;
      }
    }
    else if (k < n->info)
    {
      if (n->f_esq != NULL)
        insereix_bst(n->f_esq, k);
      else
      {
        n->f_esq = new node;
        n->f_esq->info = k;
        n->f_esq->f_esq = n->f_esq->f_dret = NULL;
      }
    }
  }
  return n;
}

template <typename T>
typename Abin<T>::node *Abin<T>::consulta_bst(node *n, const T &k)
{
  node *res = NULL;

  if (n != NULL)
  {
    if (k == n->info)
    {
      res = n;
    }
    else
    {
      if (k < n->info)
      {
        res = consulta_bst(n->f_esq, k);
      }

      if (res == NULL)
      {
        if (k > n->info)
        {
          res = consulta_bst(n->f_dret, k);
        }
      }
    }
  }

  return res;
}

template <typename T>
void Abin<T>::insereix_bst(const T &k)
{
  if (_arrel == NULL)
  {
    _arrel = new node;
    _arrel->info = k;
    _arrel->f_esq = _arrel->f_dret = NULL;
  }
  else
  {
    insereix_bst(_arrel, k);
  }
}

template <typename T>
bool Abin<T>::consulta_bst(const T &k) const
{
  return consulta_bst(_arrel, k) != NULL;
}

template <typename T>
Abin<T>::Abin(Abin<T> &ae, const T &x, Abin<T> &ad)
{
  /* Pre: cert */
  /* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try
  {
    _arrel->info = x;
  }
  catch (...)
  {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}

template <typename T>
Abin<T>::Abin(const Abin<T> &a)
{
  _arrel = copia_nodes(a._arrel);
};

template <typename T>
Abin<T>::~Abin()
{
  esborra_nodes(_arrel);
};

template <typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &a)
{
  if (this != &a)
  {
    node *aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
};

template <typename T>
bool Abin<T>::es_buit() const
{
  /* Pre: cert */
  /* Post: el resultat indica si el p.i. és buit o no */
  return (_arrel == NULL);
};

template <typename T>
typename Abin<T>::iterador Abin<T>::arrel() const
{
  /* Pre: cert */
  /* Post: Retorna un iterador al node arrel. */
  iterador it;
  it._p = _arrel;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::final() const
{
  /* Pre: cert */
  /* Post: Retorna un iterador no vàlid. */
  return iterador();
};

template <typename T>
Abin<T> Abin<T>::iterador::arbre() const
{
  /* Pre: cert */
  /* Post: Retorna el subarbre al que apunta l'iterador; llança un error
si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  Abin<T> a;
  a._arrel = copia_nodes(_p);
  ;
  return a;
};

template <typename T>
T Abin<T>::iterador::operator*() const
{
  /* Pre: cert */
  /* Post: Retorna l'element en el node al que apunta l'iterador, o
llança un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  return _p->info;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fesq() const
{
  /* Pre: cert */
  /* Post: Retorna un iterador al fill esquerre; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  iterador it;
  it._p = _p->f_esq;
  return it;
};

template <typename T>
typename Abin<T>::iterador Abin<T>::iterador::fdret() const
{
  /* Pre: cert */
  /* Post: Retorna un iterador al fill dret; llança
un error si l'iterador no és vàlid. */
  if (_p == NULL)
    throw IteradorInvalid;
  iterador it;
  it._p = _p->f_dret;
  return it;
};
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

//Escriptura
std::string dep = "";
void pinta(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{

    std::string d1 = dep;
    if (f == l)
        cout << ".";
    else
    {
        cout << "[" << *f << "]\n"
             << d1 << " \\__";
        dep = d1 + " |  ";
        pinta(f.fdret(), l);
        cout << "\n"
             << d1 << " \\__";
        dep = d1 + "    ";
        pinta(f.fesq(), l);
    }
    dep = d1;
}

void pinta(const Abin<unsigned int> &a)
{
    pinta(a.arrel(), a.final());
    cout << endl;
}

Abin<unsigned int> mount(vector<int> &v, unsigned int &pos)
{
    Abin<unsigned int> a;

    // Case base is when we reach a leave of tree.
    if (pos < v.size() and v[pos] != -1)
    {
        int root = v[pos];

        Abin<unsigned int> lt = mount(v, ++pos);
        Abin<unsigned int> rt = mount(v, ++pos);

        a = Abin<unsigned int>(lt, root, rt);
    }

    return a;
}

Abin<unsigned int> mount(vector<int> &v)
{
    unsigned int pos = 0U;
    return mount(v, pos);
}

void printPostorder(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{
    if (f != l)
    {
        printPostorder(f.fesq(), l);
        printPostorder(f.fdret(), l);
        cout << " " << *f;
    }
}

void printInorder(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l)
{
    if (f != l)
    {
        printInorder(f.fesq(), l);
        cout << " " << *f;
        printInorder(f.fdret(), l);
    }
}

void print(Abin<unsigned int> &a)
{
    Abin<unsigned int>::iterador f = a.arrel();
    Abin<unsigned int>::iterador l = a.final();

    cout << "pos:";
    printPostorder(f, l);
    cout << endl;
    cout << "ino:";
    printInorder(f, l);
    cout << endl;
}

int high(const Abin<unsigned int>::iterador &f, const Abin<unsigned int>::iterador &l)
{
    if (f == l)
    {
        return 0;
    }
    else
    {
        return 1 + max(high(f.fesq(), l), high(f.fdret(), l));
    }
}

int count(const Abin<unsigned int>::iterador &f, const Abin<unsigned int>::iterador &l)
{
    if (f == l)
    {
        return 0;
    }
    else
    {
        return high(f.fesq(), l) + high(f.fdret(), l) + 1;
    }
}

int countDigit(long n) 
{
    if (n == 0) return 1;
    
    int count = 0; 
    while (n != 0) { 
        n = n / 10; 
        ++count; 
    } 
    return count; 
}

void print_bst(Abin<unsigned int>::iterador f, Abin<unsigned int>::iterador l, unsigned int level)
{
    if (f != l)
    {   
        ++level;
        print_bst(f.fdret(), l, level);
        int iter = (10*(level-1))-countDigit(*f);

        for (int i=0; i<iter; ++i)
        {
            cout << " ";
        }

        cout << *f << endl;
        print_bst(f.fesq(), l, level);
        
    }
}

void print_bst(Abin<unsigned int> &a)
{
    unsigned int level = 1;
    print_bst(a.arrel(), a.final(), level);
}

int main()
{
    string line;
    Abin<unsigned int> a;
    vector<int> v;

    int n;

    // Insert elements to BST.
    while (cin >> n)
        a.insereix_bst(n);

    print_bst(a);
}