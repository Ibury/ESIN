#include <iostream>
using namespace std;

// ---------- ARBRE -------------------------------------------------------------

template <typename Elem>
arbbin<Elem>::arbbin() throw(error){
//Pre: Cert
//Post: Crea un arbbin : Arbbin
//Cost: Θ(1)
_arrel = NULL;
cont = 0;

}

template <typename Elem>
arbbin<Elem>::~arbbin() throw(){
//Pre: Cert
//Post: Destrueix l'objecte arbbin del p.i
//Post: Θ(1)
	destrueix_node(_arrel);
}

template<typename Elem>
void arbbin<Elem>::destrueix_node(node* origen){
//Pre: Cert
//Post: Tots els nodes següents d'origen queden esborrats
//Cost: Θ(n)
	if (origen!=NULL){
		destrueix_node(origen->f_dret);
		destrueix_node(origen->f_esq);
		delete origen;
	}	
}

template<typename Elem>
arbbin<Elem>::arbbin (const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error){
//Pre: Cert
//Post: Es crea un arbre a partir d'un Elem x i arbres fills esquerra i dret respectivament.
//Post: Θ (n)
	
	_arrel = new node;
	
	try {
		_arrel->f_esq = copia_node(fesq._arrel);
		_arrel->f_dret = copia_node(fdret._arrel);
		_arrel->info = x;
	}
	catch(error){
		destrueix_node(_arrel); //Borrem els nodes que hem creat
		throw;
	}
	cont = fesq.cont + fdret.cont + 1;
}

template<typename Elem>
typename arbbin<Elem>::arbbin::iterador arbbin<Elem>::arrel() const throw(){
//Pre: Cert
//Post: Retorna un iterador a l'arrel de l'arbre del p.i
//Cost: Θ (1)

	iterador it;
	if (!this) throw error (arbbin<Elem>::iterador::IteradorNul);	
	it.pite = _arrel;	
	
	return it;
}

template<typename Elem>
nat arbbin<Elem>::size() const throw(){
//Pre: Cert
//Post: Retorna el tamany de l'arbre
//Cost: Θ (1)
	return cont;
}

template<typename Elem>
arbbin<Elem>::arbbin::arbbin(const arbbin& a) throw(error){
//Pre: Cert
//Post: Crea un arbbin amb la mateixa informacio que l'arbbin a
//Cert: Θ(n)
	_arrel = copia_node (a._arrel);
	cont = a.cont;
}

template<typename Elem>
typename arbbin<Elem>::node* arbbin<Elem>::copia_node(const node* origen){
//Pre: Cert
//Post: Retorna un punter a un node que te la mateixa T info que origen
//Cost: Θ(n)
	node* desti = NULL;
	if (origen != NULL){
		desti = new node;
		try {
			desti->info = origen->info;
			desti->f_dret = copia_node(origen->f_dret);
			desti->f_esq = copia_node(origen->f_esq);
		}

		catch(error){
			destrueix_node(desti);
			throw;
		}
	}

	return desti;
}

template<typename Elem>
typename arbbin<Elem>::arbbin& arbbin<Elem>::operator=(const arbbin& a) throw(error){
//Pre: Cert
//Post: El p.i passa a apuntar a una copia de l'arbre a
//Cost: Θ (n)

	arbbin<Elem> arbre (a);
	node* aux = _arrel;
	_arrel = arbre._arrel;
	cont = arbre.cont;
	arbre._arrel = aux;
	cont = a.cont;
	return *this;

}

// ---------------------- ITERADOR -----------------------------------------

template <typename Elem>
arbbin<Elem>::iterador::iterador() throw(error){
//Pre: Cert
//Post: L'iterador del p.i queda apuntant a NULL
//Cost Θ(1)
	pite = NULL;	
}

template <typename Elem>
arbbin<Elem>::iterador::~iterador() throw(){
//Pre: Cert
//Post: L'iterador del p.i queda apuntant a NULL
//Cost: Θ (1)
	pite = NULL;
}

template <typename Elem>
arbbin<Elem>::iterador::iterador(const iterador& it) throw(error){
//Pre: Cert
//Post: L'iterador del p.i queda apuntant on apunta l'iterador it
//Cost: Θ(1)
	pite = it.pite;
		
}
template <typename Elem>
typename arbbin<Elem>::iterador& arbbin<Elem>::iterador::operator=(const iterador& it) throw(error){
//Pre:Cert
//Post:L'iterador del p.i queda apuntant on apunta l'iterador it
//Cost: Θ(1)
	pite = it.pite;
	return *this;

}

template <typename Elem>
Elem arbbin<Elem>::iterador::operator*() const throw(error){
//Pre: Cert
//Post: Retorna un Elem que pertany a l'iterador del p.i. Si l'iterador es null retorna error
//Cost:
	if (pite==NULL) throw error (IteradorNul);
	return pite->info;
}

template<typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_esq() const throw(error){
//Pre: Cert
//Post: Retorna un iterador al fill esquerra del iterador p.i
//Cost: Θ(1)
	
	iterador it;
	if (pite==NULL) throw error (IteradorNul);
	it.pite = pite->f_esq;
	return it;

}

template<typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_dret() const throw(error){
//Pre: Cert
//Post: Retorna un iterador al fill dret del iterador p.i
//Cost: Θ(1)

	iterador it;
	if (pite==NULL) throw error (IteradorNul);
	it.pite = pite->f_dret;
	return it;
	
}

template<typename Elem>
arbbin<Elem>::iterador::operator bool() const throw(){
//Pre:Cert
//Post: Retorna cert si el punter de l'iterador NO apunta a NULL.
//Cost (1)
	return (pite!=NULL);
}


