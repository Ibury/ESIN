#include "cj_enters.hpp"
#include <iostream>

// CONSTRUCTORS 


cj_enters::cj_enters(){
//Pre : No rep res.
//Post : Crea un objecte de la classe cj_enters com a p.i
//Cost θ (n)
	node* nou = new node;
	first  = nou;
	first->next = NULL;
	first->bef = NULL;  	
	cont = 0;
 }


cj_enters::cj_enters(const cj_enters &cj){
//Pre : Cert.
//Post : Crea un objecte còpia de cj com a p.i
//Cost n

	cj_enters a;
	node* aux = cj.first;
	while (aux->next!=NULL){
		a.insereix(aux->next->info);
		aux = aux->next;
	}
	first = a.first;
	cont = a.cont;
}


cj_enters::~cj_enters(){
//Pre: No rep res.
//Post : Destrueix el p.i node per node
//Cost n

  node* aux = first;
  while (aux->next!=NULL){
 		node* pdel = aux;
 		aux = aux->next;
 		delete pdel;
  }
 	delete aux;
}

  
cj_enters& cj_enters::operator=(const cj_enters &cj){
//Pre : Cert.
//Post : Retorna una referència al p.i
//Cost θ (n)

	cj_enters a (cj);
	first = a.first;
	cont = a.cont;
  return *this;
}

void cj_enters::insereix(int e){
//Pre : e ha de ser un enter.
//Post: No retorna res.
//Cost n

  	if (cont==0){
  		node* nou = new node;
  		nou->info = e;
  		nou->next = NULL;
  		nou->bef = first;
  		first->next = nou;
  		cont++;
  	}

  	else {

  		bool hi_es = false;
  		node* aux = first;
  		while (aux->next!=NULL and not hi_es){
  			if (aux->next->info < e){
  				aux = aux->next;
  			}
  			else if (aux->next->info==e) hi_es = true;
  			else {

  				node* nou = new node;
  				nou->info = e;
  				
  				nou->bef = aux;
  				nou->next = aux->next;
  				aux->next->bef = nou;
  				aux->next = nou;
  				cont++;
  				hi_es = true;
  			}
  			
  		}

  		if (!hi_es){
  			node* nou = new node;
  			nou->info = e;
  			aux->next = nou;
  			nou->next = NULL;
  			nou->bef = aux;
  			cont++;
  		}

  	}
 }

void cj_enters::unir(const cj_enters& B){
//Pre: Cert.
//Post: No retorna res.
//Cost n

 	node* aaux = first;
 	node* baux = B.first;

 	while (aaux->next!=NULL and baux->next!=NULL){
 		
 		if (aaux->next->info < baux->next->info){
 			aaux = aaux->next;
 		}

 		else if (aaux->next->info == baux->next->info){
 			aaux = aaux->next;
 			baux = baux->next;
 		}

 		else { 			
 			node* nou = new node;
 			nou->info = baux->next->info;
 			nou->next = aaux->next;
 			nou->bef = aaux;
 			aaux->next->bef = nou;
 			aaux->next = nou;
 			cont++;
 			baux = baux->next;
 			aaux = aaux->next; 			
 		}
 	}

 	while (baux->next != NULL){
 		
 		node* nou = new node;
 		nou->info = baux->next->info;
 		nou->next = NULL;
 		nou->bef = aaux;
 		aaux->next = nou;
 		aaux = aaux->next;
 		baux = baux->next;
 		cont++;
 	}
 }

 void cj_enters::intersectar(const cj_enters& B){
//Pre: Cert.
//Post: No retorna res.
//Cost n

 	node* aaux = first;
 	node* baux = B.first;

 	while (aaux->next!=NULL and baux->next!=NULL){
 		
 		if (aaux->next->info > baux->next->info){
 			baux = baux->next;
 		}
 		else if (aaux->next->info == baux->next->info){
 			baux = baux->next;
 			aaux = aaux->next;
 		}
 		else {

 			node* erase = aaux->next;
 			if (erase->next != NULL){
        node* aaux2 = erase->next;
        aaux->next = aaux2;
	 			aaux2->bef = aaux;
	 			--cont;
        delete erase;
 			}
      else {
 				aaux->next = NULL;
 				baux = baux->next;
 				delete erase;
 				cont--;
 			}
 		}
 	}	

 	node* erase = NULL;

 	if (aaux->next!=NULL){
 	 erase = aaux->next;
 	 aaux->next = NULL;
 	 --cont; 

 	while (erase->next != NULL){
 		node* erase2 = erase;
 		erase = erase->next;
 		delete erase2;
 		--cont;
 	}

 	delete erase; 	
 	}
 }

 void cj_enters::restar(const cj_enters& B){
//Pre: Cert.
//Post: Modifica el p.i eliminant els elements que es troben en a i b
//Cost n

 	node* aaux = first;
 	node* baux = B.first; 	

 	while (aaux->next!=NULL and baux->next!=NULL){
 		
 		if (aaux->next->info > baux->next->info){
 			baux = baux->next;
 		}
 		else if (aaux->next->info == baux->next->info){ 			
 			node* erase = aaux->next;
 			if (erase->next!=NULL){
 				erase = aaux->next;
 			node* aaux2 = erase->next;
 			
 			aaux->next = aaux2;
 			aaux2->bef = aaux;
 			--cont; 			
 			delete erase;

 			baux = baux->next;
 		}

 		else {
 			aaux->next = NULL;
 			baux = baux->next;
 			delete erase;
 			--cont;

 		}
 			
 		}
 		else { 			
 			aaux = aaux->next;
 		}
 	}
 }

cj_enters cj_enters::operator+(const cj_enters& B) const{
//Pre: Cert.
//Post: Retorna un objecte cj_enters amb la unió del p.i i B
//Cost θ (n)

	cj_enters a (*this);
	a.unir(B);
	return a;
}

cj_enters cj_enters::operator*(const cj_enters& B) const{
//Pre: Cert
//Post: Retorna un objecte cj_enters amb la intersecció del p.i B
//Cost θ (n)

  cj_enters a (*this);
	a.intersectar(B);
	return a;
}
  
cj_enters cj_enters::operator-(const cj_enters& B) const{
//Pre: Cert
//Post: Retorna un objecte cj_enters amb la resta del p.i i B
//Cost θ (n)

  cj_enters a (*this);
	a.restar(B);
	return a;
}

bool cj_enters::conte(int e) const{
//Pre: e ha de ser un enter
//Post: Retorna un bool respecte si el p.i conté e
//Cost n

  bool hi_es = false;
  node* aux = first;
  while (aux->next!=NULL and not hi_es){
  	if (aux->next->info==e) hi_es = true;
  	else aux=aux->next;
  }
  return hi_es;
 }
 

int cj_enters::max() const{
//Pre: El conjunt del p.i no està buit.
//Post: Retorna l'enter màxim del p.i
//Cost n

  node* aux = first->next;
 	
 	while (aux->next != NULL) aux = aux->next;	

 	return aux->info;
}

int cj_enters::min() const{
//Pre: El conjunt del p.i no està buit..
//Post: Retorna l'enter mínim del p.i
//Cost θ (n)
  return first->next->info;
}

int cj_enters::card() const{
//Pre: No rep res.
//Post: Retorna l'enter cardinal del p.i
//Cost θ (n)

 	return cont;
 }

bool cj_enters::operator==(const cj_enters& B) const{
//Pre: Cert.
//Post: Si el p.i és igual a B retorna cert i vicevers.
//Cost n

 	bool es_igual = false;
 	node* aux = first;
 	node* aux2 = B.first;
 	if (cont==B.cont){
 		while (aux->next!=NULL and not es_igual){
 			if (aux->next->info != aux2->next->info) es_igual = true;
 			else {
 				aux = aux->next;
 				aux2 = aux2->next;
 			}
 		}
 	}

 	else es_igual = true;

 	return not es_igual;
 }

bool cj_enters::operator!=(const cj_enters& B) const{
//Pre: Cert
//Post Si el p.i és diferent a B retorna cert i viceversa
//Cost θ (n)
 	return not cj_enters::operator==(B);
}

void cj_enters::print(ostream& os) const{
//Pre: Cert
//Post: Escriu per pantalla el p.i des del first* fins a l'últim element de la llista dinàmica
//Cost n

  os << "[";
	node* aux = first;
	int i = 0;

	while (aux->next != NULL){
		os <<(aux->next->info);
		if (i<cont-1) os << " ";
		aux = aux->next;
		++i;
  }
	os << "]";
}

 



 


















 




