#include <iostream>
#include <cstddef>
using namespace std;

template <typename T>
class Arbre
{
private:
  Arbre() : _arrel(NULL){};
  struct node
  {
    T info;
    node *primf;
    node *seggerm;
  };
  node *_arrel;
  static node *copia_arbre(node *p);
  static void destrueix_arbre(node *p) throw();

  // My private methods.
  //------------------------------------------------------------------------------------------
  static void add_childs(node *a1, node *a2);
  static void add_brothers(node *a1, node *a2);
  //------------------------------------------------------------------------------------------

public:
  // Construeix un Arbre format per un únic node que conté a x.
  Arbre(const T &x);

  // Tres grans.
  Arbre(const Arbre<T> &a);
  Arbre &operator=(const Arbre<T> &a);
  ~Arbre() throw();

  // Col·loca l'Arbre donat com a primer fill de l'arrel de l'arbre sobre el que s'aplica el mètode i l'arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
  void afegir_fill(Arbre<T> &a);

  // My public methods.
  //------------------------------------------------------------------------------------------
  Arbre operator+(const Arbre<T> &a);
  // Retorna un arbre que és la suma del p.i. i l’arbre a que crida al mètode privat recursiu
  static node *suma_arbres(node *a1, node *a2);
  // Retorna el punter a l’arrel de la suma dels arbres apuntats per a1 i a2.
  void preordre() const;
  // Escriu una línia amb el recorregut en preordre de l’arbre general
  // Cada element ha de sortir precedit d’un espai que crida al mètode privat recursiu
  static void preordre(node *n);
  // Escriu una línia amb el recorregut en preordre de l’arbre general
  // que apunta n. Cada element ha de sortir precedit d’un espai.
  //------------------------------------------------------------------------------------------

  // Iterador sobre arbre general.
  friend class iterador;
  class iterador
  {
  public:
    friend class Arbre;

    // Construeix un iterador no vàlid.
    iterador() throw();

    // Retorna el subarbre al que apunta l'iterador; llança un error si l'iterador no és vàlid.
    Arbre<T> arbre() const;

    // Retorna l'element del node al que apunta l'iterador o llança un error si l'iterador no és vàlid.
    T operator*() const;

    // Retorna un iterador al primogenit del node al que apunta; llança un error si l'iterador no és vàlid.
    iterador primogenit() const;

    // Retorna un iterador al següent germà del node al que apunta; llança un error si l'iterador no és vàlid.
    iterador seg_germa() const;

    // Operadors de comparació.
    bool operator==(const iterador &it) const
    {
      return _p == it._p;
    };
    bool operator!=(const iterador &it) const
    {
      return _p != it._p;
    };
    static const int IteradorInvalid = 410;

  private:
    Arbre<T>::node *_p;
  };

  // Retorna un iterador al node arrel de l'Arbre (un iterador no vàlid si l'arbre no és vàlid).
  iterador arrel() const throw();

  // Retorna un iterador no vàlid.
  iterador final() const throw();

  static const int ArbreInvalid = 400;
};

#include "arbre.cpp"
