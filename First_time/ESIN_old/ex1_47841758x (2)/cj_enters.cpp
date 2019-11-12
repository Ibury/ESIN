#include "cj_enters.hpp"

using namespace std;


  //Cost: Θ(1)
  cj_enters::cj_enters()
  /*Pre: Cert.*/
  /*Post: Crea una llista dinámica buida.*/
  {
	p_node = NULL;
	u_node = NULL;
	cardinal = 0;
  }

  //Cost: Θ(n)
  cj_enters::cj_enters(const cj_enters &cj)
  /*Pre: cj es un conjunt d'enters.*/
  /*Post: Crea una llista dinámica buida i fa una copia del paràmetre.*/
  {

  	delete this;

  	p_node = NULL;
  	u_node = NULL;
  	node* ant;
  	node* ptr=cj.p_node;
  	cardinal = cj.card();

  	for (int i=0; i<cj.card(); ++i) {
  		node* nd = new node;
  		nd->info = ptr->info;
  		if (i==0) {
  			p_node = nd;
  			nd->ant_node=NULL;
  			nd->seg_node=NULL;
  			ant = p_node;
  		}else{
  			nd->seg_node = NULL;
  			nd->ant_node = ant;
  		}
  		u_node = nd;

  		ptr = ptr->seg_node;

  	}

  }

  //Cost: Θ(n)
  cj_enters::~cj_enters()
  /*Pre: Cert.*/
  /*Post: Esborra la llista desde el principi cap al final.*/
  {

  	if (p_node != NULL) p_node = p_node->seg_node;

  	while (p_node != NULL) {
  		delete p_node->ant_node;
  		p_node = p_node->seg_node;
  	}

  	delete u_node;

  	u_node = NULL;
  	cardinal = 0;
  }

  //Cost: Θ(n)
  cj_enters& cj_enters::operator=(const cj_enters &cj)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea una còpia del paràmetre en el p.i.*/
  {
	

  	if (this!=&cj) cj_enters B = cj_enters(cj);
  	
  	return *this;
  }
  
  //Cost: Θ(n)²
  void cj_enters::insereix(int e)
  /*Pre: Es necessari un enter.*/
  /*Post: Insereix e en la llista si no el conté i a més la ordena..*/
  {
	  if (not conte(e)) {
	  	if (p_node==NULL) {
		  	p_node = new node;
		  	p_node->info = e;
		  	p_node->seg_node = NULL;
		  	p_node->ant_node = NULL;
		  	u_node = p_node;

	  	}else{
		  	u_node->seg_node = new node;
		  	u_node->seg_node->info = e;
		  	u_node->seg_node->seg_node = NULL;
		  	u_node->seg_node->ant_node = u_node;

		  	u_node = u_node->seg_node;
		}
		++cardinal;
		ordena();
  	  }
  }

  //Cost: Θ(1)
  void cj_enters::esborra(node* ptr)
  /*Pre: Es necessari un punter del node a esborrar.*/
  /*Post: Esborra el node que conté en el camp info l'enter e.*/
  {

    if (this->card()>1) {
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

  }
  
  //Cost: Θ(n)²
  void cj_enters::ordena()
  /*Pre: Llista no necessàriament ordenada.*/
  /*Post: Ordena la llista de conjunts.*/
  {
	  int i=1;
	  bool ordenat = false;
	  
	  node* ptr;
	  
	  while ((i<card()) and ordenat==false) {
		++i;
		ordenat = true;
		ptr = p_node;

		for (int j=0; j<card()-1; ++j) {
			if (ptr->info > ptr->seg_node->info) {
				
				ordenat = false;
				
				int aux = ptr->info;
				ptr->info = ptr->seg_node->info;
				
				ptr->seg_node->info = aux;
			}
			ptr = ptr->seg_node;
		}
	
	  }
  }
  
  //Cost: Θ(n)²
  void cj_enters::unir(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Uneix el conjunt del p.i amb B.*/
  {

	  node* ptr = B.p_node;

  	while(ptr != NULL) {
  		if (not this->conte(ptr->info)) this->insereix(ptr->info);
  		ptr = ptr->seg_node;
  	}

  }

  //Cost: Θ(n)²
  void cj_enters::intersectar(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Intersecta el conjunt del p.i amb B*/
  {

	  node* ptr = p_node;

  	while(ptr != NULL) {
  		if (not B.conte(ptr->info)) this->esborra(ptr);
		  ptr = ptr->seg_node;
  	}

  }

  //Cost: Θ(n)²
  void cj_enters::restar(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Resta el conjunt del p.i amb B*/ 
  {

	  node* ptr = p_node;

  	while(ptr != NULL) {
  		if (B.conte(ptr->info)) this->esborra(ptr);
  		ptr = ptr->seg_node;
  	}
  }

  //Cost: Θ(n)
  cj_enters cj_enters::operator+(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i uneix el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->unir(B);

  	return *C;

  }

  //Cost: Θ(n)
  cj_enters cj_enters::operator*(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i intersecta el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->intersectar(B);

  	return *C;
  }

  //Cost: Θ(n)
  cj_enters cj_enters::operator-(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i resta el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->restar(B);

  	return *C;
  }

  //Cost: Θ(n)
  bool cj_enters::conte(int e) const
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
  int cj_enters::max() const
  /*Pre: Cert.*/
  /*Post: Enter màxim del conjunt*/
  {

	int max=0;
	
	if (u_node!=NULL) max = u_node->info;

	return max;

  }

  //Cost: Θ(1)
  int cj_enters::min() const
  /*Pre: Cert.*/
  /*Post: Enter mínim del conjunt*/
  {
  	int min=0;

	if (p_node!=NULL) min = p_node->info;

	return min;
  }

  //Cost: Θ(1)
  int cj_enters::card() const
  /*Pre: Cert.*/
  /*Post: Número d'elements que té el conjunt*/
  {
	  return cardinal;
  }

  //Cost: Θ(n)²
  bool cj_enters::operator==(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es igual al del p.i, false en cas contrari*/
  {
	  bool es_igual = true;

    if (this->card() != B.card()) {

      es_igual = false; 

    }else{

  	  node* ptr = B.p_node;

  	  while(ptr != NULL and es_igual) 
  	  {	
  	  	  es_igual=this->conte(ptr->info);
  		  ptr = ptr->seg_node;
  		 
  	  }
    }
	  
	  return es_igual;
  }

  //Cost: Θ(n)²
  bool cj_enters::operator!=(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es diferent al del p.i, true en cas contrari*/
  {

	  return not (*this==B);
  }

  //Cost: Θ(n)
  void cj_enters::print(ostream& os) const
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