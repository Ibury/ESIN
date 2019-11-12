template <typename T>
conjunt<T>::conjunt() throw(error){

    node* nou = new node;
    first = nou;
    first->next = NULL;
    first->bef = NULL;
    last = first; // NOVA LINEA
	  cont = 0;
}

template <typename T>
conjunt<T>::conjunt(const conjunt& B) throw(error){

    //DECLARACIONS INICIALS
    node* nou = new node;
    first = nou;
    first->next = NULL;
    first->bef = NULL;
    last = first; // NOVA LINEA
    cont = 0;

    node* baux = B.first;
    node* aaux = first;
    while (baux->next!=NULL){
      node* nou = new node;
      nou->info = baux->next->info;
      nou->next = NULL;
      aaux->next = nou;
      nou->bef = aaux;
      cont++;
      baux = baux->next;
      aaux = aaux->next;

    }
    last = aaux; // NOVA LINEA -> ACABA RECORREGUT I PILLA LULTIM
}

template <typename T>
conjunt<T>& conjunt<T>::operator=(const conjunt& B) throw(error){

  /*conjunt a (B);
  node* aux = a.first;
  a.first = first;
  first = aux;
  return *this;
  */
  if (*this!=B){
    conjunt a (B);
    node* aux = first;
    node* aux2 = last; // NOVA LINEA
    int icont = cont;
    first = a.first;
    last = a.last; // NOVA LINEA
    cont = a.cont;
    a.first = aux;
    a.last = aux2; // NOVA LINEA
    a.cont = icont;
  }

  return *this;
}

template <typename T>
conjunt<T>::~conjunt() throw(){

  node* aux = first;
  while (aux->next!=NULL){
 		node* pdel = aux;
 		aux = aux->next;
 		delete pdel;
  }
 	delete aux;

}

template <typename T>
void conjunt<T>::insereix(const T& x) throw(error){
  	if (cont==0){
  		node* nou = new node;
  		nou->info = x ;
  		nou->next = NULL;
  		nou->bef = first;
  		first->next = nou;
      last = nou; // NOVA LINEA
  		cont++;
  	}
  	else {

  		bool hi_es = false;
  		node* aux = first;
  		while (aux->next!=NULL and not hi_es){
  			if (aux->next->info < x){
  				aux = aux->next;
  			}
  			else if (aux->next->info==x) hi_es = true;
  			else {
  				node* nou = new node;
  				nou->info = x;

  				nou->bef = aux;
  				nou->next = aux->next;
  				aux->next->bef = nou;
  				aux->next = nou;
          last = nou; // NOVA LINEA
  				cont++;
  				hi_es = true;
  			}

  		}
  		if (!hi_es){
  			node* nou = new node;
  			nou->info = x;
  			aux->next = nou;
  			nou->next = NULL;
  			nou->bef = aux;
        last = nou; // NOVA LINEA
  			cont++;
  		}
  	}
}

template <typename T>
void conjunt<T>::unir(const conjunt& B) throw(error){

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
        last = aaux; // NOVA LINIA
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
      last = aaux; // NOVA LINIA
   		cont++;
   	}


}

template <typename T>
void conjunt<T>::intersectar(const conjunt& B) throw(error){

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
          last = aaux; // LINIA NOVA
   			}
   		}
   	}

    last = aaux; // LINIA NOVA

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

template <typename T>
void conjunt<T>::restar(const conjunt& B) throw(error){

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
        last = aaux; // NOVA LINIA
        }
      }

   		else aaux = aaux->next;

  }


}

template <typename T>
conjunt<T> conjunt<T>::operator+(const conjunt& B) const throw(error){

    conjunt a (*this);
  	a.unir(B);
  	return a;

}
template <typename T>
conjunt<T> conjunt<T>::operator*(const conjunt& B) const throw(error){


    conjunt a (*this);
  	a.intersectar(B);
  	return a;
}
template <typename T>
conjunt<T> conjunt<T>::operator-(const conjunt& B) const throw(error){

    conjunt a (*this);
	  a.restar(B);
	  return a;
}


template <typename T>
int conjunt<T>::card() const throw(){
  return cont;
}


template <typename T>
T conjunt<T>::min() const throw(error){
  return first->next->info;


}

template <typename T>
T conjunt<T>::max() const throw(error){
  return last->info;
}

template <typename T>
bool conjunt<T>::conte(const T& x) const throw(){

    bool hi_es = false;
    node* aux = first;
    while (aux->next!=NULL and not hi_es){
    	if (aux->next->info==x) hi_es = true;
    	else aux=aux->next;
    }
    return hi_es;

}

template <typename T>
bool conjunt<T>::operator==(const conjunt& B) const throw(){


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

template <typename T>
bool conjunt<T>::operator!=(const conjunt& B) const throw(){

    return not conjunt::operator==(B);

}



template <typename T>
void conjunt<T>::print(ostream& os) const throw(){
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
