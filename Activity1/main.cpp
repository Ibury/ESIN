#include <vector>
 #include <cstddef>
 using namespace std;
 typedef unsigned int nat;
 
 class Llista {
   // Llista simplement encadenada, sense fantasma i no circular.
   private:
     struct node {
       int info;  // Informació del node
       node *seg; // Punter al següent element
     };
     node *_prim; // Punter al primer element
     nat _long;   // Nombre d’elements
 
   public:
     Llista();
     // Pre: True
     // Post: El p.i. és una llista buida.
 
     Llista(const vector<int> &v);
     // Pre: True
     // Post: El p.i. conté els elements de v amb el mateix ordre.
 
     ~Llista();
     // Post: Destrueix els elements del p.i.
 
     nat longitud() const;
     // Pre: True
     // Post: Retorna el nombre d’elements del p.i.
 
     void mostra() const;
     // Pre: True
     // Post: Mostra el p.i. pel canal estàndard de sortida.
 
     void duplica();
     // Pre: True
     // Post: S’han duplicat els elements del p.i.
     // Exemple: [2 5 3] quedaria [2 2 5 5 3 3]
 };
 
 // Aquí va la implementació del mètode duplica
void Llista::duplica()
{
	node *actual = _prim, *prev = NULL;
	
	while (actual != NULL)
	{
		// We are evaluating first elem.
		if (prev == NULL)
		{
			_prim = new node;
			_prim->info = actual->info;
			_prim->seg = actual;
			++_long;

		}else{
			
			prev->seg = new node;
			prev->seg->info = actual->info;
			prev->seg->seg = actual;
			++_long;
		}
		
		prev = actual;
		actual = actual->seg;
	}
}
