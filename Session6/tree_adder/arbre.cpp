// La còpia es fa seguint un recorregut en preordre.
template <typename T>
typename Arbre<T>::node *Arbre<T>::copia_arbre(node *p)
{
  node *aux = NULL;
  if (p != NULL)
  {
    aux = new node;
    try
    {
      aux->info = p->info;
      aux->primf = aux->seggerm = NULL;
      aux->primf = copia_arbre(p->primf);
      aux->seggerm = copia_arbre(p->seggerm);
    }
    catch (...)
    {
      destrueix_arbre(aux);
    }
  }
  return aux;
}

// La destrucció es fa seguint un recorregut en postordre.
template <typename T>
void Arbre<T>::destrueix_arbre(node *p) throw()
{
  if (p != NULL)
  {
    destrueix_arbre(p->primf);
    destrueix_arbre(p->seggerm);
    delete p;
  }
}

// Construcció d'un arbre que conté un sol element x a l'arrel.
template <typename T>
Arbre<T>::Arbre(const T &x)
{
  _arrel = new node;
  try
  {
    _arrel->info = x;
    _arrel->seggerm = NULL;
    _arrel->primf = NULL;
  }
  catch (...)
  {
    delete _arrel;
    throw;
  }
}

template <typename T>
Arbre<T>::Arbre(const Arbre<T> &a)
{
  _arrel = copia_arbre(a._arrel);
}

template <typename T>
Arbre<T> &Arbre<T>::operator=(const Arbre<T> &a)
{
  Arbre<T> tmp(a);
  node *aux = _arrel;
  _arrel = tmp._arrel;
  tmp._arrel = aux;
  return *this;
}

template <typename T>
Arbre<T>::~Arbre() throw()
{
  destrueix_arbre(_arrel);
}

template <typename T>
void Arbre<T>::afegir_fill(Arbre<T> &a)
{
  if (_arrel == NULL or a._arrel == NULL or
      a._arrel->seggerm != NULL)
  {
    throw ArbreInvalid;
  }
  a._arrel->seggerm = _arrel->primf;
  _arrel->primf = a._arrel;
  a._arrel = NULL;
}

template <typename T>
Arbre<T> Arbre<T>::operator+(const Arbre<T> &a)
{
  Arbre<T> b(*this);
  b._arrel = suma_arbres(b._arrel, a._arrel);

  return b;
}

template <typename T>
typename Arbre<T>::node *Arbre<T>::suma_arbres(node *a1, node *a2)
{
  if (a1 != NULL and a2 != NULL)
  {

    suma_arbres(a1->primf, a2->primf);
    suma_arbres(a1->seggerm, a2->seggerm);

    a1->info += a2->info;

    if (a1->primf == NULL and a2->primf != NULL)
    {

      node *a = a1->primf, *b = a2->primf;

      while (b != NULL)
      {
        a = new node;
        a->primf = a->seggerm = NULL;
        a->info = b->info;

        a = a->primf;
        b = b->primf;
      }
    }

    if (a1->seggerm == NULL and a2->seggerm != NULL)
    {
      node *a = a1->seggerm, *b = a2->seggerm;

      while (b != NULL)
      {
        a = new node;
        a->primf = a->seggerm = NULL;
        a->info = b->info;

        a = a->seggerm;
        b = b->seggerm;
      }
    }
  }

  return a1;
}

template <typename T>
void Arbre<T>::preordre() const
{
  preordre(_arrel);
  cout << endl;
}

template <typename T>
void Arbre<T>::preordre(node *n)
{
  if (n != NULL)
  {
    cout << " " << n->info;
    preordre(n->primf);
    preordre(n->seggerm);
  }
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::arrel() const throw()
{
  iterador it;
  it._p = _arrel;
  return it;
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::final() const throw()
{
  return iterador();
}

template <typename T>
Arbre<T>::iterador::iterador() throw() : _p(NULL)
{
}

template <typename T>
T Arbre<T>::iterador::operator*() const
{
  if (_p == NULL)
  {
    throw IteradorInvalid;
  }
  return _p->info;
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::iterador::primogenit() const
{
  if (_p == NULL)
  {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p->primf;
  return it;
}

template <typename T>
typename Arbre<T>::iterador Arbre<T>::iterador::seg_germa() const
{
  if (_p == NULL)
  {
    throw IteradorInvalid;
  }
  iterador it;
  it._p = _p->seggerm;
  return it;
}

template <typename T>
Arbre<T> Arbre<T>::iterador::arbre() const
{
  if (_p == NULL)
  {
    throw IteradorInvalid;
  }
  Arbre<T> a;
  a._arrel = _p;
  Arbre<T> aux(a);
  a._arrel = NULL;
  return aux;
}
