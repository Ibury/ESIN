#include "conjunt.hpp"

using namespace std;


  //Cost: Θ(1)
  template <typename T>
  conjunt<T>::conjunt() throw(error)
  /*Pre: Cert.*/
  /*Post: Crea una llista dinámica buida.*/
  {


		p_node = NULL;
		u_node = NULL;
		cardinal = 0;

  }

  //Cost: Θ(n)
  template <typename T>
  conjunt<T>::conjunt(const conjunt &cj) throw(error)
  /*Pre: cj es un conjunt d'enters.*/
  /*Post: Crea una llista dinámica buida i fa una copia del paràmetre.*/
  {

  	p_node = NULL;
  	u_node = NULL;
  	node* ant;
  	node* ptr = cj.p_node;
  	cardinal = cj.card();

  	for (int i=0; i<cj.card(); ++i) {
  		node* nd = new node;
      try {
    		nd->info = ptr->info;
    		if (i==0) {
    			p_node = nd;
    			nd->ant_node=NULL;
    			nd->seg_node=NULL;
    			ant = p_node;
    		}else{
          ant->seg_node = nd;
    			nd->seg_node = NULL;
    			nd->ant_node = ant;
          ant = nd;
    		}
    		u_node = nd;

    		ptr = ptr->seg_node;

    }catch(error) {
      
       if (p_node != NULL) {
          p_node = p_node->seg_node;
        }

        while (p_node != NULL) {
          delete p_node->ant_node;
          p_node = p_node->seg_node;
        }

        if (u_node != NULL) delete u_node;
        u_node = NULL;
        cardinal=0;
        throw;
    }

  	}
  }

  //Cost: Θ(n)
  template <typename T>
  conjunt<T>::~conjunt() throw()
  /*Pre: Cert.*/
  /*Post: Esborra la llista desde el principi cap al final.*/
  {

   if (p_node != NULL) {
      p_node = p_node->seg_node;
    }

  	while (p_node != NULL) {
  		delete p_node->ant_node;
  		p_node = p_node->seg_node;
  	}

  	if (u_node != NULL) delete u_node;

  	u_node = NULL;
  	cardinal = 0;
  }
  
  //Cost: Θ(n)
  template <typename T>
  void conjunt<T>::insereix(const T& e) throw(error)
  /*Pre: Es necessari un enter.*/
  /*Post: Insereix e en la llista si no el conté i a més la ordena..*/
  {
    bool conte = false;
    bool trobat = false;


  		if (p_node==NULL) {
		  	p_node = new node;
        try{
		  	   p_node->info = e;
		       p_node->seg_node = NULL;
		  	   p_node->ant_node = NULL;
		  	   u_node = p_node;
	         cardinal=1;
        }catch(error) {
          delete p_node;
          p_node = NULL;
          cardinal=0;
          throw;
        }
  		}else{
      
		    node* ptr = p_node;
		      
		    if (e<ptr->info) {
          trobat = true;
        }else if(e>u_node->info) {
          ptr = NULL;
        }

		    while ((not trobat) and (ptr!=NULL) and (not conte)) {
		        if (ptr->info==e) conte = true;
		        else if (e<ptr->info) trobat = true;
		        else ptr = ptr->seg_node;
		    }
		    if (not conte) {

		      node* nnode = new node;
          try {
		          nnode->info = e;

              ++cardinal;

    		      if (ptr==NULL) {
    		        u_node->seg_node = nnode;
    		        nnode->seg_node = NULL;
    		        nnode->ant_node = u_node;
    		        u_node = nnode;
    		      }else if (ptr==p_node) {
    		        nnode->seg_node = ptr;
    		        ptr->ant_node = nnode;
    		        nnode->ant_node = NULL;
    		        p_node = nnode;       
    		      }else{
    		        ptr->ant_node->seg_node = nnode;
    		        nnode->ant_node = ptr->ant_node;
    		        nnode->seg_node = ptr;
    		        ptr->ant_node = nnode;
    		      }

          }catch(error) {
              delete nnode;
              --cardinal;
          }

		    }

		}	
		
  }

  //Cost: Θ(1)
  template <typename T>
  void conjunt<T>::esborra(node* ptr) throw(error)
  /*Pre: Es necessari un punter del node a esborrar.*/
  /*Post: Esborra el node que conté en el camp info l'enter e.*/
  {

  	try {

	    if (cardinal>1) {
	  		if (ptr == p_node){
	  			p_node = ptr->seg_node;
	  			p_node->ant_node = NULL;
	  		}else if (ptr == u_node) {
	  			u_node = ptr->ant_node;
	  			u_node->seg_node = NULL;
	  		}else{
	  			ptr->ant_node->seg_node = ptr->seg_node;
	  			ptr->seg_node->ant_node = ptr->ant_node;
	  		}
	    }else{
	      p_node = NULL;
	      u_node = p_node;
	    }

			delete ptr;
			
			--cardinal;
  	}catch(error) {
  		throw;
  	}

  }
  
  //Cost: Θ(n)
  template <typename T>
  void conjunt<T>::unir(const conjunt& B) throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Uneix el conjunt del p.i amb B.*/
  {

     node* ptrA = u_node;
     node* ptrB = B.u_node;

      while (ptrA != NULL and ptrB != NULL) {
          
          if (ptrA->info < ptrB->info) {
            ptrA = ptrA->ant_node;
          }else if (ptrA->info > ptrB->info){
            insereix(ptrB->info);
            ptrA = ptrA->ant_node;
            ptrB = ptrB->ant_node;
          }else{
            ptrA = ptrA->ant_node;
            ptrB = ptrB->ant_node;
          }
      }

      while(ptrB != NULL) {
        insereix(ptrB->info);
        ptrB = ptrB->ant_node;
      }

  }

  //Cost: Θ 2(n)
  template <typename T>
  void conjunt<T>::intersectar(const conjunt& B) throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Intersecta el conjunt del p.i amb B*/
  {

		 node* ptrA = p_node;
	   node* ptrB = B.p_node;

	    while (ptrA != NULL and ptrB != NULL) {
	        
	        if (ptrA->info < ptrB->info) {
	          esborra(ptrA);
	          ptrA = ptrA->seg_node;
	        }else if (ptrA->info > ptrB->info){
	          ptrB = ptrB->seg_node;
	        }else{
	          ptrA = ptrA->seg_node;
	          ptrB = ptrB->seg_node;
	        }
	    }

      while(ptrA != NULL) {
        esborra(ptrA);
        ptrA = ptrA->seg_node;
      }

	}



  //Cost: Θ(n)
  template <typename T>
  void conjunt<T>::restar(const conjunt& B) throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Resta el conjunt del p.i amb B*/ 
  {

     node* ptrA = p_node;
     node* ptrB = B.p_node;

      while (ptrA != NULL and ptrB != NULL) {
          
          if (ptrA->info < ptrB->info) {
            ptrA = ptrA->seg_node;
          }else if (ptrA->info > ptrB->info){
            ptrB = ptrB->seg_node;
          }else{
            esborra(ptrA);
            ptrA = ptrA->seg_node;
            ptrB = ptrB->seg_node;
          }
      }

  }

  //Cost: Θ 2(n)
  template <typename T>
  conjunt<T> conjunt<T>::operator+(const conjunt& B) const throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i uneix el conjunt del p.i amb B.*/
  {
  	conjunt* C = new conjunt(*this);

  	try{

  		C->unir(B);
  	
  	}catch(error) { 
  		throw;
  	}

  	return *C;

  }

  //Cost: Θ 2(n)
  template <typename T>
  conjunt<T> conjunt<T>::operator*(const conjunt& B) const throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i intersecta el conjunt del p.i amb B.*/
  {
  	conjunt* C = new conjunt(*this);

    try {

        C->intersectar(B);

    }catch(error) {
        throw;
    }

    

  	return *C;
  }

  //Cost: Θ 2(n)
  template <typename T>
  conjunt<T> conjunt<T>::operator-(const conjunt& B) const throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i resta el conjunt del p.i amb B.*/
  {
  	conjunt* C = new conjunt(*this);

    try {

        C->restar(B);

    }catch(error) {
        throw;
    }

  	return *C;
  }

  //Cost: Θ(n)
  template <typename T>
  conjunt<T>& conjunt<T>::operator=(const conjunt &cj) throw(error)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea una còpia del paràmetre en el p.i.*/
  {
      
      if (this!=&cj) {
        conjunt B = conjunt(cj);

        try {
        
          node* ptr = p_node;
          p_node = B.p_node;
          B.p_node = ptr;


          ptr = u_node;
          u_node = B.u_node;
          B.u_node = ptr; 

          cardinal = B.card();

        }catch(error) {
          throw;
        }
 
      }
    
    return *this;
  }

  //Cost: Θ(n)
  template <typename T>
  bool conjunt<T>::conte(const T& e) const throw()
  /*Pre: enter.*/
  /*Post: true si e está al conjunt del p.i.*/
  {
	  bool conte = false;
	  
	  node* ptr = p_node;

	  while(ptr != NULL and not conte) 
	  {
		  conte=(ptr->info==e);
		  ptr = ptr->seg_node;
	  }
	  
	  return conte;
  }

  //Cost: Θ(1)
  template <typename T>
  T conjunt<T>::max() const throw(error)
  /*Pre: Cert.*/
  /*Post: Enter màxim del conjunt*/
  {
		
		if (u_node==NULL) throw error(NoMinMaxEnConjBuit);

	  return u_node->info;

  }

  //Cost: Θ(1)
  template <typename T>
  T conjunt<T>::min() const throw(error)
  /*Pre: Cert.*/
  /*Post: Enter mínim del conjunt*/
  {

  	
    if (p_node==NULL) throw error(NoMinMaxEnConjBuit);

    return p_node->info;
  }

  //Cost: Θ(1)
  template <typename T>
  int conjunt<T>::card() const throw()
  /*Pre: Cert.*/
  /*Post: Número d'elements que té el conjunt*/
  {
	  return cardinal;
  }

  //Cost: Θ(n)²
  template <typename T>
  bool conjunt<T>::operator==(const conjunt& B) const throw()
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es igual al del p.i, false en cas contrari*/
  {
	bool es_igual = true;

    if (this->card() != B.card()) {

      es_igual = false; 

    }else{

  	  node* ptrA = p_node;
      node* ptrB = B.p_node;

  	  while((ptrA != NULL and ptrB != NULL) and es_igual) 
  	  {	
  	  	  es_igual=(ptrA->info == ptrB->info);
  		    ptrA = ptrA->seg_node;
          ptrB = ptrB->seg_node;
  		 
  	  }
    }
	  
	  return es_igual;
  }

  //Cost: Θ(n)
  template <typename T>
  bool conjunt<T>::operator!=(const conjunt& B) const throw()
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es diferent al del p.i, true en cas contrari*/
  {

	  return not (*this==B);
  }

  //Cost: Θ(n)
  template <typename T>
  void conjunt<T>::print(ostream& os) const throw()
  /*Pre: Cert.*/
  /*Post: Canal estandard de sortida*/
  {
	  os << "[";

	  node* ptr = p_node;

	  while(ptr != NULL) 
	  {
		  os << (ptr->info);
		  ptr = ptr->seg_node;
		  if (ptr != NULL) os << " ";
	  }

	  os << "]";
  }