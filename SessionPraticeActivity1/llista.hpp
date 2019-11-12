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
 
     //void separa(Llista &l2);
     // Pre: l2 és buida
     // Post: S’han separat els elements del p.i., quedant al p.i. els elements
     // de les posicions senars i a l2 els de les posicions parells.
     // Exemple: [2 5 3 8 1] => [2 3 1] i l2 = [5 8]
 
 // Aquí va la implementació del mètode separa

    // PRE: predecessor and current nodes.
    // POST: Previous is going to point to the successor of current node.
    void hook(node *previous, node *current)
    {
        if (previous == nullptr)
        {
            _prim = _prim->seg;
        }
        else
        {
            previous->seg = current->seg;
        }
    }

    void swap (Llista &l2)
    {
        node *tmp = _prim;
        _prim = l2._prim;
        l2._prim = tmp;

        nat aux = _long;
        _long = l2._long;
        l2._long = aux;
    }

    void separa(Llista &l2)
    {
        node *prev = nullptr, *curr = _prim, *l2_last = l2._prim;
        nat elems = _long;
        nat i = 0;

        while (curr != nullptr)
        {
            if (i % 2 == 0)
            {
                // No ghost pointer so we have to check if it's first elem.
                if (l2_last == nullptr)
                {
                    l2._prim = l2_last = curr;
                    hook(nullptr, curr);
                }
                else
                {
                    l2_last = l2_last->seg = curr;
                    hook(prev, curr);
                }

                --_long;                         
            }
            
            ++i;
            prev = curr;
            curr = curr->seg;
        }

        l2._long = elems - _long;

        if (l2._long > 0)
            l2_last->seg = nullptr;

        swap(l2);
    }
 };