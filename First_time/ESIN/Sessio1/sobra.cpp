cj_enters& cj_enters::operator=(const cj_enters &cj){

  	delete first,last,actual; // Borrem previ
  	cj_enters a;
  	node* aux = cj.first->seg; // Inicialitzem al principi de cj.
  	while (aux!=cj.last){
  		//insereix(aux->info);
  		
  		a.insereix(aux->info);
  		aux=aux->seg;
  	}

  	first = a.first;
  	last =a.last;
  	actual=a.actual;
  	cont = a.cont;


  	



  }
  
  void cj_enters::insereix(int e){
  	node* nou = new node;
  	nou->info = e;

  	if (cont==0){
  		nou->seg = last;
  		first->seg = nou;
  		actual = nou;  		
  		cont++; // Augmentem contador.
  	}

  	else {

  		actual->seg = nou;
  		nou->seg = last;
  		actual = nou;
  		cont++;


  	}  	

  }
  
  void cj_enters::unir(const cj_enters& B){

  	node* aux = B.first->seg;
  	while (aux!=B.last){
  		if (!conte(aux->info)){
  			insereix(aux->info);
  			aux=aux->seg;
  		} 
  		else aux=aux->seg;
  	}


  } 
  void cj_enters::intersectar(const cj_enters& B){

  	node* aux = this->first->seg; //Primer element del P.I
  	node* auxc = this->first; //ALTO COMENÇA A LELEMENT FANTASMA
  	while (aux!=this->last){
  		node* aux2 = B.first->seg;
  		bool hi_es = false;
  		while (aux2!=B.last and not hi_es){
  			if (aux->info==aux2->info) hi_es = true;
  			else aux=aux->seg;
  		}

  		if (!hi_es){
  			auxc->seg = aux->seg;
  			auxc=aux;
  			aux=aux->seg;

  		}

  		else {
  			auxc = auxc->seg;
  			aux = aux->seg;
  		}

  	}









  }
  void cj_enters::restar(const cj_enters& B){}

  cj_enters cj_enters::operator+(const cj_enters& B) const{

  	
  	

  	


  }
  cj_enters cj_enters::operator*(const cj_enters& B) const{}
  cj_enters cj_enters::operator-(const cj_enters& B) const{}

  bool cj_enters::conte(int e) const{

  	bool hi_es = false;

  	node* aux = first->seg;
  	while (aux!=last and not hi_es){
  		
  		if (aux->info==e) hi_es = true;
  		else aux=aux->seg;
  	}
  	return hi_es;
  }

  int cj_enters::max() const{

  	int max = first->seg->info;
  	node* aux = first->seg;
  	while (aux!=last){
  		if (aux->info > max) max = aux->info;
  		else aux=aux->seg;
  	}

  	

  	return max;


  }
  int cj_enters::min() const{

  	int min = first->seg->info;
  	node* aux = first->seg;
  	while (aux!=last){
  		if (aux->info < min) min = aux->info;
  		else aux=aux->seg;
  	}

  	

  	return min;


  }

  int cj_enters::card() const{
  	return cont;
  }

  bool cj_enters::operator==(const cj_enters& B) const{

  	node* aux = first->seg;
  	node* aux2 = B.first->seg;

  	bool are_equal = true;

  	if (this->cont==B.cont){
  		while (aux!=last and are_equal){
  			if (aux->info != aux2->info) are_equal = false;
  			else {
  				aux = aux->seg;
  				aux2 = aux2->seg;
  			}
  		}

  	}

  	else are_equal=false;

  	return are_equal;

  	


  }
  bool cj_enters::operator!=(const cj_enters& B) const{

  	/*node* aux = first->seg;
  	node* aux2 = B.first->seg;

  	bool are_equal = true;

  	if (this->cont==B.cont){
  		while (aux!=last and are_equal){
  			if (aux->info != aux2->info) are_equal = false;
  			else {
  				aux = aux->seg;
  				aux2 = aux2->seg;
  			}
  		}

  	}

  	else are_equal=false;

  	return not are_equal;
*/

	node* aux = first->seg;
  	node* aux2 = B.first->seg;

  	bool are_diff = false;

  	if (this->cont==B.cont){

  		while (aux!=last and not are_diff){
  			if (aux->info!=aux2->info) are_diff = true;
  			else {
  				aux = aux->seg;
  				aux2 = aux2->seg;
  			}
  		}


  	}
  	else are_diff = true;

  	return are_diff;


  }

  void cj_enters::print(ostream& os) const{
  	if (cont>0){
  		os << "[ ";
  		node* aux = first->seg;
  		
  		while (aux!=last){
  		
  			os << aux->info<< " ";
  			aux = aux->seg;

  		}

  		os << "]";

  	}
  	os << endl;

  }

 /* cj_enters::node* cj_enters::copia_llista (const node* origen){






  }*/


