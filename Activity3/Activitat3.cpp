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
 
   // Retorna el nombre de fulles (nodes de grau 0) de l’arbre
   nat fulles() const;

   nat fulles(node *n) const;
 };


template <typename T>
nat Arbre<T>::fulles(node *n) const
{

	unsigned int f = 0;

	if (n != NULL)
	{

		if (n->primf == NULL) f = 1;
			
		f += fulles(n->primf) + fulles(n->seggerm);

	}

	return f;
}

template <typename T>
nat Arbre<T>::fulles() const
{
	return fulles(_arrel);
}

