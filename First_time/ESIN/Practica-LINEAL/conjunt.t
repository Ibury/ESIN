template <typename T>
conjunt<T>::conjunt() throw(error){
//Pre: Cert.
//Post: El p.i té paràmetres assignats
//Cost: ϴ(1)
  node* nou = new node;
  try {
  first = nou;
  first->next = NULL;
  first->bef = NULL;
  last = first;
  cont = 0;
  }
  catch(error){ //Error de memoria
    delete nou;
    throw;
  }
}

template <typename T>
conjunt<T>::conjunt(const conjunt& B) throw(error){
//Pre: Cert.
//Post: Es crea una copia del p.i
//Cost: ϴ(1)

  node* nou = new node;
  try{
    first = nou;
    first->next = NULL;
    first->bef = NULL;
    last = first;
    cont = 0;
  }

  catch(error){ //Error de memoria
    delete nou;
    throw;
  }

  node* baux = B.first;
  node* aaux = first;
  while (baux->next!=NULL){
    node* nou = new node;
    try{
      nou->info = baux->next->info;
      nou->next = NULL;
      nou->bef = aaux;
    }
    catch(error){ //Error de memòria
      delete nou;
      throw;
    }
    
    aaux->next = nou;    
    cont++;
    baux = baux->next;
    aaux = aaux->next;
  }
  last = aaux; 
}

template <typename T>
conjunt<T>& conjunt<T>::operator=(const conjunt& B) throw(error){
//Pre: Cert
//Post: Asigna al p.i una còpia de B.
//Cost: ϴ(1)

  conjunt a (B);
  node* aux = first;
  first = a.first;
  cont = a.cont;
  a.first = aux;
  last = a.last;
  return *this;
}

template <typename T>
conjunt<T>::~conjunt() throw(){
//Pre: Cert
//Post: Es destrueix l'objecte conjunt
//Post: ϴ(n)

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
//Pre: Cert.
//Post: El p.i passa a contenir el parametre x de manera ordenada si no hi es.
//Cost: ϴ(n)

  	if (cont==0){
  		node* nou = new node;
  		try{
        nou->info = x ;
    		nou->next = NULL;
    		nou->bef = first;
      }
      catch(error){
        delete nou;
        throw;
      }
  		first->next = nou;
      last = nou; 
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
  				try{
            nou->info = x;
    				nou->bef = aux;
    				nou->next = aux->next;
          }
          catch(error){
            delete nou;
            throw;
          }
  				aux->next->bef = nou;
  				aux->next = nou;
          cont++;
  				hi_es = true;
  			}

  		}

  		if (!hi_es){
  			node* nou = new node;
  			try{
          nou->info = x;        
          nou->next = NULL;
          nou->bef = aux;
        }
        catch(error){
          delete nou;
          throw;
        }
  			aux->next = nou;
        last = nou;
  			cont++;
  		}
  	}
}

template <typename T>
void conjunt<T>::unir(const conjunt& B) throw(error){
//Pre: Cert.
//Post: Els elements del p.i i el B queden units al p.i(excepte els elements repetits)
//Cost: ϴ(n)

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
 			try{
        nou->info = baux->next->info;
   			nou->next = aaux->next;
   			nou->bef = aaux;
      }
      catch(error){
        delete nou;
        throw;
      }
 			aaux->next->bef = nou;
 			aaux->next = nou;
 			cont++;
 			baux = baux->next;
 			aaux = aaux->next;
 		}
 	}

 	while (baux->next != NULL){

 		node* nou = new node;
 		try{
      nou->info = baux->next->info;
   		nou->next = NULL;
   		nou->bef = aaux;
    }
    catch(error){
      delete nou;
      throw;
    }
 		aaux->next = nou;
 		aaux = aaux->next;
 		baux = baux->next;
    last = aaux; 
 		cont++;
 	}
}

template <typename T>
void conjunt<T>::intersectar(const conjunt& B) throw(error){
//Pre: Cert
//Post: Al p.i queden els elements repetits del p.i i de B
//Cost: ϴ(n)

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
        last = aaux;
  		}
  	}
  }

  last = aaux;
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
//Pre: Cert.
//Post: El p.i passa a tenir tots els elements de p.i menys els que estan repetits amb B
//Cost ϴ(n)

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
        last = aaux; 
      }
    }
   	else aaux = aaux->next;
  }
}

template <typename T>
conjunt<T> conjunt<T>::operator+(const conjunt& B) const throw(error){
//Pre: Cert
//Post: Es crida al metode unir amb una copia del p.i i el conjunt B
//Cost: ϴ(n) - ϴ(2*n)
  conjunt a (*this);
	a.unir(B);
	return a;
}

template <typename T>
conjunt<T> conjunt<T>::operator*(const conjunt& B) const throw(error){
//Pre: Cert
//Post: Es crida al metode intersectar amb una copia del p.i i el conjunt B
//Cost: ϴ(n) - ϴ(2*n)
  conjunt a (*this);
	a.intersectar(B);
	return a;
}

template <typename T>
conjunt<T> conjunt<T>::operator-(const conjunt& B) const throw(error){
//Pre: Cert
//Post: Es crida al metode restar amb una copia del p.i i el conjunt B
//Cost: ϴ(n) - ϴ(2*n)
  conjunt a (*this);
  a.restar(B);
  return a;
}


template <typename T>
int conjunt<T>::card() const throw(){
//Pre: Cert
//Post: Retorna el cardinal del conjunt
//Cost: ϴ(1)
  return cont;
}


template <typename T>
T conjunt<T>::min() const throw(error){
//Pre: El conjunt del p.i no pot estar buit
//Post: Retorna el minim valor del conjunt
//Cost ϴ(1)
  if (cont==0) throw error(NoMinMaxEnConjBuit);
  return first->next->info;
}

template <typename T>
T conjunt<T>::max() const throw(error){
//Pre: El conjunt del p.i no pot estar buit
//Post: Retorna el maxim valor del conjunt
//Cost ϴ(1)
  if (cont==0) throw error(NoMinMaxEnConjBuit);
  return last->info;
}

template <typename T>
bool conjunt<T>::conte(const T& x) const throw(){
//Pre: Cert
//Post: Retorna cert si el conjunt (p.i) conte l'element x, sino retorna fals
//Cost: ϴ(n)

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
//Pre: Cert
//Post: Retorna cert si el conjunt (p.i) te el mateix cardinal i elements que B, sino retorna fals
//Cost: ϴ(n)

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
//Pre: Cert
//Post: Retorna cert si el conjunt del (p.i) te diferent cardinal i/o elements que B, sino retona fals
//Cost ϴ(1)
  return not conjunt::operator==(B);
}



template <typename T>
void conjunt<T>::print(ostream& os) const throw(){
//Pre: Cert.
//Post: Treu per pantalla el conjunt node per node
//Cost ϴ(n)
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

//PROVES:
template <typename T>
void conjunt<T>::esborra_nodes(node* n){
  if (n!=NULL){
    esborra_nodes(n=n->next);
    delete n;
  }
}

template<typename T>
void conjunt<T>::encripta (const string &s, const int k){
  node* nou = new node;
  nou->next = nou->bef = NULL;
  nou->info = k;
  if (s.size()>0){
    node *n = new node;
    n->info = 2*(s[0]*k);
    n->next = NULL;
    n->bef = nou;
    nou->next = n;

    for (unsigned int i = 1;i<s.size();++i){
      node *b = new node;
      b->info = (s[i]+s[i-1])*k;
      b->next = NULL;
      b->bef = n;
      n->next = b;
      n = n->next;
    }
  }

  node* borra = first;
  first = nou;
  esborra_nodes(borra);

}