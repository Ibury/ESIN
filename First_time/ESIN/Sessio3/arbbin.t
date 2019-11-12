#include <iostream>
using namespace std;

// ---------- ARBRE -------------------------------------------------------------

template <typename Elem>
arbbin<Elem>::arbbin() throw(error){
_arrel = new node;
_arrel->f_esq = NULL;
_arrel->f_dret = NULL;
cont = 0;

}

template <typename Elem>
arbbin<Elem>::~arbbin() throw(){
	destrueix_node(_arrel);

}
template<typename Elem>
void arbbin<Elem>::destrueix_node(node* origen){
	if (origen!=NULL){
		destrueix_node(origen->f_dret);
		destrueix_node(origen->f_esq);
		delete origen;

	}	

}


template<typename Elem>
arbbin<Elem>::arbbin (const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error){
	
	_arrel = new node;
	_arrel->f_esq = copia_node(fesq._arrel);
	_arrel->f_dret = copia_node(fdret._arrel);
	_arrel->info = x;
	cont = fesq.cont + fdret.cont + 1;


}

template<typename Elem>
typename arbbin<Elem>::arbbin::iterador arbbin<Elem>::arrel() const throw(){
	iterador it;
	it.pite = _arrel;
	return it;

}

template<typename Elem>
nat arbbin<Elem>::size() const throw(){
	return cont;

}

template<typename Elem>
arbbin<Elem>::arbbin::arbbin(const arbbin& a) throw(error){
	_arrel = copia_node (a._arrel);
	cont = a.cont;
}

template<typename Elem>
typename arbbin<Elem>::node* arbbin<Elem>::copia_node(const node* origen){
	node* desti = NULL;
	if (origen != NULL){
		desti = new node;
		desti->info = origen->info;
		desti->f_dret = copia_node(origen->f_dret);
		desti->f_esq = copia_node(origen->f_esq);
	}

	return desti;
}




template<typename Elem>
typename arbbin<Elem>::arbbin& arbbin<Elem>::operator=(const arbbin& a) throw(error){

	arbbin<Elem> arbre (a);
	node* aux = _arrel;
	_arrel = arbre._arrel;
	cont = arbre.cont;
	arbre._arrel = aux;
	return *this;

}



// ---------------------- ITERADOR -----------------------------------------

template <typename Elem>
arbbin<Elem>::iterador::iterador() throw(error){
	pite = NULL;	
}

template <typename Elem>
arbbin<Elem>::iterador::~iterador() throw(){
	delete pite;
	pite = NULL;
}

template <typename Elem>
arbbin<Elem>::iterador::iterador(const iterador& it) throw(error){
	pite = it.pite;
		
}
template <typename Elem>
typename arbbin<Elem>::iterador& arbbin<Elem>::iterador::operator=(const iterador& it) throw(error){
	pite = it.pite;
	return *this;

}

template <typename Elem>
Elem arbbin<Elem>::iterador::operator*() const throw(error){
	if (pite==NULL) throw error (IteradorNul);
	return pite->info;
}

template<typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_esq() const throw(error){
	
	iterador it;
	if (pite->f_esq!=NULL){
		//std::cout << "GO ";
		it.pite = pite->f_esq;
	}
	else {
		//std::cout<<"ELSE";
		throw error (IteradorNul);		
	}
	return it;

}

template<typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_dret() const throw(error){

	iterador it;
	if (pite->f_dret!=NULL) it.pite = pite->f_dret;
	else throw error (IteradorNul);
	return it;
	
}

template<typename Elem>
arbbin<Elem>::iterador::operator bool() const throw(){

	return (pite!=NULL);
}


//------HUFFMAN----------

void codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error){
	
}
