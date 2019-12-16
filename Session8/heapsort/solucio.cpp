#ifndef _CUAPRIO_HPP
#define _CUAPRIO_HPP
#include <vector>
using namespace std;
typedef unsigned int nat;

template <typename Elem, typename Prio>
class CuaPrio {
public:
  // Constructora, crea una cua buida.                                    
  CuaPrio();

  // Tres grans.
  CuaPrio(const CuaPrio &p);
  CuaPrio& operator=(const CuaPrio &p);
  ~CuaPrio() throw();

  // Afegeix l'element x amb prioritat p a la cua de prioritat.
  void insereix(const Elem &x, const Prio &p);

  // Retorna un element de mínima prioritat en la cua de prioritat. Llança un error si la cua és buida.
  Elem min() const;

  // Retorna la mínima prioritat present en la cua de prioritat. Llança un error si la cua és buida. 
  Prio prio_min() const;

  // Elimina un element de mínima prioritat de la cua de prioritat. Llança un error si la cua és buida.
  void elim_min();

  // Retorna cert si i només si la cua és buida.
  bool es_buida() const throw();

  static const int CuaPrioBuida = 320;

private:

  nat _nelems;                  // Nombre d'elements en el heap.  
  vector<pair<Elem, Prio> > _h; // Vector de pair d'Elem i Prio. La component 0 no s'usa.

  void enfonsar (nat p) throw();
  void surar (nat p) throw();
};

#endif

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio() : _nelems(0) {
  Elem x;
  Prio p;
  _h.push_back(make_pair(x, p));
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio(const CuaPrio &p) : _nelems(p._nelems), _h(p._h) {
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>& CuaPrio<Elem, Prio>::operator=(const CuaPrio &p) {
  _nelems = p._nelems;
  _h = p._h;
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::~CuaPrio() throw() {
}
  
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::insereix(const Elem &x, const Prio &p) {
  _h.push_back(make_pair(x, p));
  ++_nelems; 
  surar(_nelems);
}

template <typename Elem, typename Prio>
Elem CuaPrio<Elem, Prio>::min() const {
  if (_nelems == 0) throw CuaPrioBuida;
  return _h[1].first;
}

template <typename Elem, typename Prio>
Prio CuaPrio<Elem, Prio>::prio_min() const {
  if (_nelems == 0) throw CuaPrioBuida;
  return _h[1].second;
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::elim_min() {
  if (_nelems == 0) throw CuaPrioBuida;
  swap(_h[1], _h[_nelems]);
  _h.pop_back();
  --_nelems;
  enfonsar(1);
}

template <typename Elem, typename Prio>
bool CuaPrio<Elem, Prio>::es_buida() const throw() {
  return _nelems == 0;
}

// Enfonsa al node j-èssim fins a restablir l’ordre del monticle a _h; els subarbres del node j són heaps.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::enfonsar(nat j) throw() {
  nat hj;
  // si j no té fill esquerre ja hem acabat
  if (2*j <= _nelems) {
  hj = 2*j;
    if (hj < _nelems and _h[hj].second > _h[hj+1].second) { 
      ++hj;
    }
    // hj apunta al fill de mínima prioritat de j. 
    // Si la prioritat de j és major que la prioritat del 
    // seu fill menor cal intercanviar i seguir enfonsant.
    if (_h[j].second > _h[hj].second) {
      swap(_h[j], _h[hj]);
      enfonsar(hj);
    }
  }
}

// Fa surar el node p-èssim fins a restablir l’ordre del monticle; tots els nodes excepte el p-èssim satisfan la propietat 3.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::surar(nat p) throw() {
  nat q;
  bool fi = false;
  while (p > 1 and not fi) {
    q = p / 2;
    if (_h[q].second > _h[p].second) {
      swap(_h[p], _h[q]);
      p = q;
    }
  else {
      fi = true;
    }
  }
}
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
void heap_sort(vector<T> &v)
{
    CuaPrio<T, T> c;

    for (int i = 0; i < v.size(); ++i)
    {
        c.insereix(v[i], v[i]);
    }

    for (int i = v.size() - 1; i >= 0; --i)
    {
        v[i] = c.min();
        c.elim_min();
    }
}

int main()
{

    string line;

    CuaPrio<int, int> c;

    int x;

    vector<int> v;

    while (getline(cin, line))
    {
        istringstream ss(line);

        while (ss >> x)
        {
            v.push_back(x);
        }
    }

    heap_sort(v);

    for (int i = v.size()-1; i >= 0; --i)
    {
        cout << v[i];

        if (i != 0)
            cout << " ";
    }

    cout << endl;

    for (unsigned int i = 0; i < v.size(); ++i)
    {
        cout << v[i];

        if (i != v.size() - 1)
            cout << " ";
    }

    cout << endl;
}