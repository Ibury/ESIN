#include <iostream>
 #include <cstdlib>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class Arbre {
 private:
   Arbre(): _arrel(NULL) {};
   struct node {
     T info;
     node* primf;
     node* seggerm;
   };
   node* _arrel;
   static node* copia_arbre(node* p);
   static void destrueix_arbre(node* p) throw();
   
   static void nivells(nat i, nat actual, node *n);
 
 public:
   // Construeix un Arbre format per un únic node que conté a x.
   Arbre(const T &x);
 
   // Tres grans.
   Arbre(const Arbre<T> &a);
   Arbre& operator=(const Arbre<T> &a);
   ~Arbre() throw();
 
   // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
   void afegir_fill(Arbre<T> &a);
 
   static const int ArbreInvalid = 400;
 
   // Escriu una línia amb els elements del nivell i, d’esquerra a dreta.
   // Cada element ha de sortir precedit d’un espai.
   void nivell(nat i) const;
 };
 
 // Aquí va la implementació del mètode nivell

template <typename T>
void Arbre<T>::nivells(nat i, nat actual, node *n)
{
  if (n != NULL)
  {
	if (actual == i)
	{
	  cout << " " << n->info;
	  nivells(i, actual, n->seggerm);
	}else{
	  nivells(i, ++actual, n->primf);
	  nivells(i, actual, n->seggerm);
	}
  }
}

template <typename T>
void Arbre<T>::nivell(nat i) const
{
  nivells(i, 0, _arrel);
  cout << endl;
}
