#include "cj_enters.hpp"

using namespace std;


  cj_enters::cj_enters()
  /*Pre: Cert.*/
  /*Post: Crea una llista dinámica buida.*/
  {
	  ptr = new list<int>;
  }

  cj_enters::cj_enters(const cj_enters &cj)
  /*Pre: cj es un conjunt d'enters.*/
  /*Post: Crea una llista dinámica buida i fa una copia del paràmetre.*/
  {

  	delete this->ptr;
  	ptr = new list<int>;
  	*this->ptr = *cj.ptr;
  }

  cj_enters::~cj_enters()
  /*Pre: Cert.*/
  /*Post: Esborra l'objecte.*/
  {
  	delete this->ptr;
  }

  cj_enters& cj_enters::operator=(const cj_enters &cj)
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea una còpia del paràmetre en el p.i.*/
  {
  	cj_enters* cp = new cj_enters(cj);
  	return (*cp);
  }
  
  void cj_enters::insereix(int e)
  /*Pre: Es necessari un enter.*/
  /*Post: Insereix e en la llista si no el conté i a més la ordena..*/
  {
	  if (not conte(e)) {
	  	this->ptr->insert(this->ptr->end(),e);
  	  	this->ptr->sort();
  	  }
  }
  
  void cj_enters::unir(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Uneix el conjunt del p.i amb B.*/
  {
  	list<int>::const_iterator it = B.ptr->begin();

  	while (it!=B.ptr->end()) {
  		if (not this->conte(*it)) this->ptr->insert(this->ptr->end(),*it);
  		++it;
  	}

  }
  void cj_enters::intersectar(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Intersecta el conjunt del p.i amb B*/
  {
  	list<int>::iterator it = this->ptr->begin();

  	while (it!=this->ptr->end()) {

  		if (not B.conte(*it)) {
  			it = this->ptr->erase(it);
  		}else{
  			++it;
  		}
  	}

  }
  void cj_enters::restar(const cj_enters& B)
  /*Pre: Conjunt d'enters.*/
  /*Post: Resta el conjunt del p.i amb B*/ 
  {
  	list<int>::iterator it = this->ptr->begin();

  	while (it!=this->ptr->end()) {

  		if (B.conte(*it)) {
  			it = this->ptr->erase(it);
  		}else{
  			++it;
  		}
  	}
  }

  cj_enters cj_enters::operator+(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i uneix el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->unir(B);

  	return *C;

  }

  cj_enters cj_enters::operator*(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i intersecta el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->intersectar(B);

  	return *C;
  }

  cj_enters cj_enters::operator-(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: Crea un nou conjunto i resta el conjunt del p.i amb B.*/
  {
  	cj_enters* C = new cj_enters(*this);

  	C->restar(B);

  	return *C;
  }

  bool cj_enters::conte(int e) const
  /*Pre: enter.*/
  /*Post: true si e está al conjunt del p.i.*/
  {
	  bool conte = false;
	  list<int>::const_iterator it = this->ptr->begin();
	  
	  while(it!=this->ptr->end() and not conte) 
	  {
		  conte=(*it==e);
		  ++it;
	  }
	  
	  return conte;
  }

  int cj_enters::max() const
  /*Pre: Cert.*/
  /*Post: Enter màxim del conjunt*/
  {
	int max=0;

	list<int>::const_iterator it = this->ptr->begin();

	if (this->card()>0) max=this->ptr->front();

	while(it!=this->ptr->end()) 
	{
		if (*it>max) max=(*it);
		++it;
	}

	return max;

  }
  int cj_enters::min() const
  /*Pre: Cert.*/
  /*Post: Enter mínim del conjunt*/
  {
  	int min=0;

	list<int>::const_iterator it = this->ptr->begin();

	if (this->card()>0) min=this->ptr->front();

	while(it!=this->ptr->end()) 
	{
		if (*it<min) min=(*it);
		++it;
	}

	return min;
  }

  int cj_enters::card() const
  /*Pre: Cert.*/
  /*Post: Número d'elements que té el conjunt*/
  {
	  return this->ptr->size();
  }

  bool cj_enters::operator==(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es igual al del p.i, false en cas contrari*/
  {
	  bool es_igual = true;
	  list<int>::const_iterator it = B.ptr->begin();
	  
	  while(it!=B.ptr->end() and es_igual) 
	  {
		  es_igual=this->conte(*it);
		  ++it;
	  }
	  
	  return es_igual;
  }
  bool cj_enters::operator!=(const cj_enters& B) const
  /*Pre: Conjunt d'enters.*/
  /*Post: true si el conjunt B es diferent al del p.i, true en cas contrari*/
  {
  	return not (this->ptr==B.ptr);
  }

  void cj_enters::print(ostream& os) const
  /*Pre: Cert.*/
  /*Post: Canal estandard de sortida*/
  {
	  list<int>::const_iterator it = this->ptr->begin();
	  
	  cout << "[";

	  while(it!=this->ptr->end()) 
	  {
		  cout << (*it);
		  ++it;
		  if (it!=this->ptr->end()) cout << ", ";
	  }

	  cout << "]" << endl;
  }

