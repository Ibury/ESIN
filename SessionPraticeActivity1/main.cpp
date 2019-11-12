#include <iostream>
#include <sstream>
#include "llista.hpp"
using namespace std;

Llista::Llista() : _prim(NULL), _long(0) {}
   
Llista::Llista(const vector<int> &v) : _prim(NULL), _long(v.size()) {
  node *p, *pant = NULL;
  for (int i=0; i<v.size(); i++) {
    p = new node;
    p->info = v[i];
    p->seg = NULL;
    if (pant == NULL)
      _prim = p;
    else
      pant->seg = p;
    pant = p;
  }
}

Llista::~Llista() {
  node *p = _prim, *pelim;
  while (p != NULL) {
    pelim = p;
    p = p->seg;
    delete pelim;
  }
}

nat Llista::longitud() const {
  return _long;
}

void Llista::mostra() const {
  node *p = _prim;
  cout << "[";
  if (p != NULL) {
    cout << p->info;
    p = p->seg;
  }
  while (p != NULL) {
    cout << " " << p->info;
    p = p->seg;
  }
  cout << "]";
}


int main() {
  // Vigilar la classe Llista
  class Llista_ctrl {
    private:
      struct node {
        int info;  // Informació del node
        node *seg; // Punter al següent element
      };
      node *_prim; // Punter al primer element
      nat _long;   // Nombre d'elements
  };

  Llista ln;
  Llista_ctrl lc;
  // diagnosis en temps d'execució
  if (sizeof(ln)!=sizeof(lc))
    throw string("Sembla que la classe 'Llista' no està ben definida.");

  string linea;
  while (getline(cin, linea)) {
    vector<int> v;
    istringstream ss(linea);
    int n;
    while (ss >> n) {
      v.push_back(n);
    }
    Llista l(v);
    Llista l2;
    l.separa(l2);
    cout << l.longitud() << " ";
    l.mostra();
    cout << " " << l2.longitud() << " ";
    l2.mostra();
    cout << endl;
  }
}