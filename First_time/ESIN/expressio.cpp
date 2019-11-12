#include "expressio.hpp"
#include <stack>
#include <list>
#include <sstream> 
#include <math.h> 
using namespace std;

typename list<token>::const_iterator citer;
typename list<token>::iterator iter;


void conversion(string &str, int num) {
	//Pre: str ha d'estar buit
	//Post: str té num transformat a string
	bool n = num < 0;
	stack<char> st;

	if (num<0) num = -num;
	do {
    int digit = num % 10;
    st.push('0' + digit);
    num /= 10;
	} while (num > 0);

	if (n) st.push(char('-'));

	while (st.size()>0) {
		str += st.top();
		st.pop();
	}

}



string dep = "";
void expressio::pintar(node* ptr)
//Pre: Cert
//Post: Res.
{
  string d1=dep;
  if (ptr==NULL)
    cout<<".";
  else {

		string str="";


		if (ptr->info.tipus()==token::CT_ENTERA){
			conversion(str,ptr->info.valor_enter());
			
		} 
		else if (ptr->info.tipus()==token::SUMA) str = "+";
		else if (ptr->info.tipus()==token::RESTA) str =  "-";
		else if (ptr->info.tipus()==token::MULTIPLICACIO) str =  "*";
		else if (ptr->info.tipus()==token::DIVISIO) str =  "/";
		else if (ptr->info.tipus()==token::OBRIR_PAR) str = "(";
		else if (ptr->info.tipus()==token::TANCAR_PAR) str =  ")";
		else if (ptr->info.tipus()==token::CANVI_DE_SIGNE) str = "--";
		else if (ptr->info.tipus()==token::SQRT) str = "sqrt()";
		else if (ptr->info.tipus()==token::EXPONENCIACIO) str = "^";
		else if (ptr->info.tipus()==token::VARIABLE) str = (ptr->info.identificador_variable());
		else if (ptr->info.tipus()==token::CT_RACIONAL){
		 conversion (str,ptr->info.valor_racional().num());
		 str+="/";
		 conversion (str,ptr->info.valor_racional().denom());
		}
		else if (ptr->info.tipus()==token::CT_REAL){
			std::ostringstream os;
			os << ptr->info.valor_real();
			str = os.str();
		}
		else if (ptr->info.tipus()==token::EVALF)str = "EVALF";
		else if (ptr->info.tipus()==token::CT_E)str = "CT_E";




    cout<< "["<< str <<"]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    pintar(ptr->fd);
    cout<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    pintar(ptr->fe);
  }
  dep=d1;
}

void expressio::pinta(node* ptr) {
	//Pre: Cert
	//Post: Res.
	dep = "";
	pintar(ptr);
	cout << endl << "Arbre de mida: " << size << endl;
}

void expressio::infixa_a_postifxa (list<token> &t, const list<token> &l) {
	//Pre: Cert
	//Post: Llista de tokens t té tokens de forma postfixa

	stack<token> s;
	list<token>::const_iterator it = l.begin();
	while (it != l.end()){
		token::codi c = (*it).tipus();


		if (c == token::CT_ENTERA or c == token::CT_REAL or c == token::CT_RACIONAL or c == token::CT_E){
			t.push_back((*it));
		}
		else if (c == token::VARIABLE){
			t.push_back((*it));

		}
		else if (c == token::OBRIR_PAR or c == token::CANVI_DE_SIGNE or c == token::SQRT or c == token::EXPONENCIACIO or c == token::EVALF){
			s.push((*it));

		}
		else if (c == token::TANCAR_PAR){

		if (s.size()>0){
			while (s.size()>0 and s.top().tipus()!=token::OBRIR_PAR){
				token t1 = s.top();
				s.pop();
				t.push_back(t1);
			}
		}
			//if (s.size()>0)	if (s.size()>0 and s.top().tipus()==token::OBRIR_PAR)
			if ((s.size()>0) and (s.top().tipus()==token::OBRIR_PAR)) s.pop();
			else throw error (ErrorSintactic);

		}

		else if (c == token::SUMA or c == token::RESTA
						or c == token::MULTIPLICACIO or c == token::DIVISIO){

					if (s.size()>0){
						while ((s.size()>0) and (s.top().tipus() != token::OBRIR_PAR) and ((s.top() > (*it)) or (s.top() == (*it)))){
							
							token t1 = s.top();
							s.pop();
							t.push_back(t1);

						}
					}
				s.push((*it));
			}
						++it;
	}
	//FINALISIMO
	while (s.size()>0){
		token t1 = s.top();
		s.pop();
		t.push_back(t1);
	}

}

expressio::expressio(const token t) throw(error){
	//Pre:Cert
	//Post: Hi ha una nova expressio amb una còpia del token t
	if (t.tipus() != token::NULLTOK and t.tipus() != token::CT_ENTERA and t.tipus() != token::CT_RACIONAL
	and t.tipus() != token::CT_REAL and t.tipus() != token::CT_E and
	t.tipus() != token::VARIABLE and t.tipus() != token::VAR_PERCENTATGE) throw error (ErrorSintactic);

	root = new node;
	root->info = t;
	root->fe = root->fd = NULL;
	size = 1;


}

expressio::expressio(const list<token> & l) throw(error){
	//Pre: Cert.
	//Post: Existeix e:Expressio, e és un arbre de punters de tokens.

	if (l.size() < 1 ) throw error (ErrorSintactic);

	//INFIXA A POSTFIXA

	list<token> t;
	infixa_a_postifxa(t,l);

	print_list(t);

	root = llegeix(t.begin(),t.end());
}

void expressio::elimina_nodes(node* &ptr) {
	if (ptr!=NULL) {
		
		elimina_nodes(ptr->fe);
		elimina_nodes(ptr->fd);
		delete ptr;
		--size;
	}
}

expressio::node* expressio::copia_expressio(const node* ptr) throw()
//PRE: Node a copiar. En la primera crida a la funció, ptr és el primer node (l'arrel de l'arbre).
//POST: Copia l'arbre desde el fons fins l'arrel.
{
	node* ptra=NULL;

	if (ptr != NULL) {

		
		try {
			ptra = new node;
			ptra->info = ptr->info;
			ptra->fe = copia_expressio(ptr->fe);
			ptra->fd = copia_expressio(ptr->fd);
			
		}catch(error) {
			delete ptra;
			throw;
		}
	}

	return ptra;
}

expressio::expressio(const expressio & e) throw(error){
	//Pre: Cert.
	//Post: l'objecte expressio del p.i és una còpia de e:Expressio.

	size = e.size;
	root = copia_expressio(e.root);

}

expressio & expressio::operator=(const expressio & e) throw(error){
	//Pre: Cert
	//Post: l'objecte expressio del p.i és una còpia de e:Expressio.

	expressio ex(e);

	node* n = root;
	root = ex.root;
	size = ex.size;

	ex.root = n;

	return *this;

}


expressio::operator bool() const throw(){
	//Pre: Cert
	//Post: Retorna cert si l'expressio és buida.
	return size==0;
}

bool expressio::operator==(const expressio & e) const throw(){
	//Pre: Cert
	//Post: Retorna cert si l'expressio del p.i és igual a l'expressio e:Expressio.

	bool iguals = true;

	if (size != e.size)	iguals = false;
	else iguals = equal(root,e.root);

	return iguals;
}

bool expressio::operator!=(const expressio & e) const throw(){
	//Pre: Cert
	//Post: Retorna cert si l'expressio del p.i és diferent a l'expressio e:Expressio.
	return not (expressio::operator==(e));
}

void expressio::vars(list<string> & l) const throw(error){
	//Pre: Cert
	//Post: Retorna cert si l'expressio del p.i és diferent a l'expressio e:Expressio.

	recull_variables(l,root);
}

void expressio::apply_substitution(const string & v, const expressio & e) throw(error){
	//Pre: Cert
	//Post: Substitueix les aparicions de la variable v per una còpia d'e:Expressio.

	// CAS Directe
	if ((root->info).tipus() == token::VARIABLE){
		if ((root->info).identificador_variable() == v){
			expressio u (e);
			*this = u;
		}
	}

	else get_allocation(v,e,root,root,true);


	pintar(root);
	cout << endl;
}

void expressio::get_allocation (const string &v, const expressio &e, node* n,node* act,bool b){
	//Pre: Cert
	//Post: Substitueix les aparicions de la variable v per una còpia d'e:Expressio.

	if (n!=NULL){
		if ((n->info).tipus() == token::VARIABLE){

			if ((n->info).identificador_variable() == v){
				//get_allocation(v,e,n->fd,n,false); SOBREN
				//get_allocation(v,e,n->fe,n,true); SOBREN

				if (b){
					act->fe = copia_expressio(e.root);
					size+=e.size;
				}

				else {
					act->fd = copia_expressio(e.root);
					size+=e.size;
				}
				delete n;
				size--;
			}
		}

		else {
			get_allocation(v,e,n->fd,n,false); // FIll dret -> FALSE
			get_allocation(v,e,n->fe,n,true); // Fill esuqerra -> TRUE
		}
	}
}

void expressio::simplify_one_step() throw(error){
	//Pre: Cert
	//Post: Simplifica un pas l'expressio del p.i
	 
}

void expressio::simplify() throw(error){
	//Pre: Cert
	//Post: Simplifica l'expressio del p.i
	simplificar(root);
	pinta(root);
}

void expressio::simplificar(node* &ptr ) {
	//Pre: Cert
	//Post: Simplifica l'expressio del p.i

	if (ptr != NULL){
		simplificar(ptr->fd);
		simplificar(ptr->fe);

		if (ptr->info.tipus() == token::CT_RACIONAL){
			
			if (ptr->info.valor_racional().denom()==1){
				ptr->info = token (int(ptr->info.valor_racional().num()));
				
			}
		}

		// ------------------- CASOS OPERADORS _-----------------------------------

		
			
		if (ptr->info.tipus() == token::SUMA){
			if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fe->info).valor_enter() == 0){ // s
				node* feaux = ptr->fe;

				node* aux = ptr;

				node* prova = ptr->fd;

				node* basura = ptr; // PROVA

				ptr = copia_expressio(ptr->fd);					

				delete aux;
				delete feaux;

				elimina_nodes(prova); // TOT BORRAT OKEY
				size-=2;

				delete basura;


			}

			else if ((ptr->fd->info).tipus() == token::CT_ENTERA and (ptr->fd->info).valor_enter() == 0){ // copiapega
				node* feaux = ptr->fd;

				node* aux = ptr;

				node* prova = ptr->fe;

				ptr = copia_expressio(ptr->fe);					

				delete aux;
				delete feaux;

				elimina_nodes(prova);
				size-=2;


			}

			else if (equal(ptr->fe,ptr->fd)){ // Cas 2 * Expressio
				node* borra = ptr->fe;
				ptr->info = token (token::MULTIPLICACIO);
				ptr->fe = new node;
				ptr->fe->fe = ptr->fe->fd = NULL;
				ptr->fe->info = token(2);
				// Esborrar basura
				elimina_nodes(borra);

				
				

			}

			else if ((ptr->fd->info).tipus() == token::CANVI_DE_SIGNE){ // Simplificar cas (d) : E + -(E)
				node* borra1 = ptr->fd;
				ptr->fd = ptr->fd->fd; // Acotem espais
				ptr->info = token (token::RESTA);

				delete borra1;
				//
			}

			else if ((ptr->fe->info).tipus() == token::CANVI_DE_SIGNE){ // Simplificar cas (e) : (-E') + E -> E - E'
				node* borra1 = ptr->fe; // Conte el canvi de signe
				ptr->fe = ptr->fe->fe;
				ptr->info = token (token::RESTA);

				node* aux = ptr->fe;
				ptr->fe = ptr->fd;
				ptr->fd = aux; // SWAP

				delete borra1;


			}

			// CASOS TURBIS

			else if ((ptr->fe->info).tipus() == token::MULTIPLICACIO and (ptr->fd->info).tipus() == token::MULTIPLICACIO){ 
				if (equal(ptr->fe->fd,ptr->fd->fd)){// Assegurem que els E son iguals // Cas (f)
					ptr->info = token (token::MULTIPLICACIO);
					node* borra1 = ptr->fd; // Borrar *
					node* borra2 = ptr->fe->fd; // Borrar E

					ptr->fe->fd = ptr->fd->fe;
					ptr->fe->info = token (token::SUMA);
					ptr->fd = ptr->fd->fd;

					// Passar la neteja

					delete borra1;
					--size;

					elimina_nodes(borra2); // Aquest pot tenirne encadenats.


				}

				else if (equal(ptr->fe->fd,ptr->fd->fe)){// Cas (g)

					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::SUMA);
					node* borra2 = ptr->fe->fd;
					ptr->fe->fd = ptr->fd->fd;
					node* borra = ptr->fd;
					ptr->fd = ptr->fd->fe;
					ptr->fd->fe = ptr->fd->fd = NULL;

					delete borra;
					--size;

					elimina_nodes(borra2);

				} 


				else if (equal(ptr->fe->fe,ptr->fd->fd)){ // Cas (h)

					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::SUMA);
					node* borra2 = ptr->fe->fe; //borra tot
					node* borra = ptr->fd;
					ptr->fe->fe = ptr->fe->fd; // SWAP
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd = ptr->fd->fd;
					ptr->fd->fe = NULL;
					ptr->fd->fd = NULL;

					delete borra;
					--size;
					elimina_nodes(borra2);


				}

				else if (equal(ptr->fe->fe,ptr->fe->fe)){ // Cas (i)

					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::SUMA);
					node* borra2 = ptr->fe->fe;
					node* borra = ptr->fd;
					ptr->fe->fe = ptr->fe->fd; // SWAP
					ptr->fe->fd = ptr->fd->fd;
					ptr->fd = ptr->fd->fe;
					ptr->fd->fe = NULL;
					ptr->fd->fe = NULL;

					delete borra;
					--size;
					elimina_nodes(borra2);


				}

				

			}

			else if ((ptr->fe->info).tipus() == token::DIVISIO and (ptr->fd->info).tipus() == token::DIVISIO){
				if (equal(ptr->fe->fd,ptr->fd->fd)){ // Cas(j)
					ptr->info = token (token::DIVISIO);
					ptr->fe->info = token (token::SUMA);
					node* borra2 = ptr->fe->fd;
					node* borra = ptr->fd;
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd = ptr->fd->fd;
					ptr->fd->fe = NULL;
					ptr->fd->fd = NULL;

					delete borra;
					--size;
					elimina_nodes(borra2);

				}
			}


			// CASOS TRIVIALS


			else if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fd->info).tipus() == token::CT_ENTERA){ // Cas 1. Dos enters
				ptr->info = token ((ptr->fe->info).valor_enter() + (ptr->fd->info).valor_enter());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;
				
			} 

			else if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fd->info).tipus() == token::CT_RACIONAL){ // Cas 2. Racional i enter
				ptr->info = token (racional(racional((ptr->fe->info).valor_enter())+(ptr->fd->info).valor_racional()));
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;
			}

			else if ((ptr->fd->info).tipus() == token::CT_ENTERA and (ptr->fe->info).tipus() == token::CT_RACIONAL){ // Cas 2. Racional i enter
				ptr->info = token (racional(racional((ptr->fd->info).valor_enter())+(ptr->fe->info).valor_racional()));
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;

			}

			else if ((ptr->fe->info).tipus() == token::CT_RACIONAL and (ptr->fd->info).tipus() == token::CT_RACIONAL){ // Cas 3. Racional i racional
				token r (racional(ptr->fe->info.valor_racional() + ptr->fd->info.valor_racional()));
				
				if (r.valor_racional().num() % r.valor_racional().denom() == 0) r = token (r.valor_racional().num() / r.valor_racional().denom());
			
				ptr->info = r;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}

			else if ((ptr->fe->info).tipus() == token::CT_REAL or (ptr->fd->info).tipus() == token::CT_REAL){ // Cas 4. Reals
				ptr->info = token (ptr->fe->info.valor_real() + ptr->fd->info.valor_real());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}







		} // ACABA CAS SUMA

		else if (ptr->info.tipus() == token::RESTA){

			if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fe->info).valor_enter() == 0){ // cas (a)

				node* borra = ptr->fe;
				node* borra2 = ptr->fd;
				ptr->info = token (token::CANVI_DE_SIGNE);
				ptr->fe = copia_expressio(ptr->fd);

				ptr->fd = NULL;
				delete borra;
				--size;

				elimina_nodes(borra2); 

				// ES POT FER SENSE COSTOS COM AQUESTS CREC ----- REVISAR PERO ALMENYS FUNCIONA	(PROVAT 1 CAS)				

			}

			else if ((ptr->fd->info).tipus() == token::CT_ENTERA and (ptr->fd->info).valor_enter() == 0){ // cas (b)

				node* borra = ptr->fd;
				node* pare = ptr;
				ptr = ptr->fe;
				size-=2;
				delete pare;
				delete borra;

			}



			else if (equal(ptr->fe,ptr->fd)){ // Cas (c)

				ptr->info = token (0);
				elimina_nodes(ptr->fe); // Ja decrementa el size
				elimina_nodes(ptr->fd);
				ptr->fe = NULL;
				ptr->fd = NULL;

			}

			else if ((ptr->fd->info).tipus() == token::CANVI_DE_SIGNE){ // Cas (d)
				ptr->info = token (token::SUMA);
				node* borra = ptr->fd;
				ptr->fd = ptr->fd->fe;
				--size;
				delete borra;

			} 

			// CASOS TURBIS

			else if ((ptr->fe->info).tipus() == token::MULTIPLICACIO and (ptr->fd->info).tipus() == token::MULTIPLICACIO){
				if (equal(ptr->fe->fd,ptr->fd->fd)){ // Cas(e)
					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::RESTA);
					node* borra = ptr->fe->fd;
					node* borra2 = ptr->fd;
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd = ptr->fd->fd;

					--size;
					delete borra2;
					elimina_nodes(borra);


				}

				else if (equal(ptr->fe->fd,ptr->fd->fe)){ // Cas (f)
					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::RESTA);
					node* borra = ptr->fe->fd;
					node* borra2 = ptr->fd;
					ptr->fe->fd = ptr->fd->fd;
					ptr->fd = ptr->fd->fe;

					--size;
					delete borra2;
					elimina_nodes(borra);

				}

				else if (equal(ptr->fe->fe,ptr->fd->fd)){ // Cas(g)
					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::RESTA);
					node* borra = ptr->fe->fe;
					node* borra2 = ptr->fd;
					ptr->fe->fe = ptr->fe->fd;
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd = ptr->fd->fd;

					--size;
					delete borra2;
					elimina_nodes(borra);

				}

				else if (equal(ptr->fe->fe,ptr->fd->fe)){ // Cas (h)
					ptr->info = token (token::MULTIPLICACIO);
					ptr->fe->info = token (token::RESTA);
					node* borra = ptr->fe->fe;
					node* borra2 = ptr->fd;
					ptr->fe->fe = ptr->fe->fd;
					ptr->fe->fd = ptr->fd->fd;
					ptr->fd = ptr->fd->fe;

					--size;
					delete borra2;
					elimina_nodes(borra);

				}
			}

			else if ((ptr->fe->info).tipus() == token::DIVISIO and (ptr->fd->info).tipus() == token::DIVISIO){
				if (equal(ptr->fe->fd,ptr->fd->fd)){
					ptr->info = token (token::DIVISIO);
					ptr->fe->info = token (token::RESTA);
					node* borra = ptr->fe->fd;
					node* borra2 = ptr->fd;
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd = ptr->fd->fd;

					--size;
					delete borra2;
					elimina_nodes(borra);

				}
			}


			// CASOS TRIVIALS



			else if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fd->info).tipus() == token::CT_ENTERA){ // 2 enters
				ptr->info = token ((ptr->fe->info).valor_enter() - (ptr->fd->info).valor_enter());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;
			}

			else if ((ptr->fe->info).tipus() == token::CT_ENTERA and (ptr->fd->info).tipus() == token::CT_RACIONAL){ // Cas 2. Racional i enter
				ptr->info = token (racional(racional((ptr->fe->info).valor_enter())-(ptr->fd->info).valor_racional()));
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;
			}

			else if ((ptr->fd->info).tipus() == token::CT_ENTERA and (ptr->fe->info).tipus() == token::CT_RACIONAL){ // Cas 3. Enter i racional
				ptr->info = token (racional(racional((ptr->fd->info).valor_enter())-(ptr->fe->info).valor_racional()));
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = ptr->fd = NULL;
				size-=2;

			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL and ptr->fd->info.tipus() == token::CT_RACIONAL){ // Cas 4. Dos racionals
				token r (racional(ptr->fe->info.valor_racional() - ptr->fd->info.valor_racional()));
				
				if (r.valor_racional().num() % r.valor_racional().denom() == 0) r = token (r.valor_racional().num() / r.valor_racional().denom());
			
				ptr->info = r;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;


			}

			else if (ptr->fe->info.tipus() == token::CT_REAL or ptr->fd->info.tipus() == token::CT_REAL){ // Tots casos reals
				ptr->info = token (ptr->fe->info.valor_real() - ptr->fd->info.valor_real());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}

			








		} // ACABA CAS RESTA

		else if (ptr->info.tipus() == token::MULTIPLICACIO){

			if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fe->info.valor_enter() == 1){ // Cas(a)
				node* borra = ptr;
				delete borra->fe;
				ptr = borra->fd;
				delete borra;
				size-=2;
			}

			else if (ptr->fd->info.tipus() == token::CT_ENTERA and ptr->fd->info.valor_enter() == 1) { // Cas (b)

				node* borra = ptr;
				delete borra->fd;				
				ptr = borra->fe;
				delete borra;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fe->info.valor_enter() == 0){ // Cas (c)

				elimina_nodes(ptr->fe);
				elimina_nodes(ptr->fd);
				ptr->info = token (0);
				ptr->fe = NULL;
				ptr->fd = NULL;

			}

			else if (ptr->fd->info.tipus() == token::CT_ENTERA and ptr->fd->info.valor_enter() == 0){ // Cas (d)

				elimina_nodes(ptr->fe);
				elimina_nodes(ptr->fd);
				ptr->info = token (0);
				ptr->fe = NULL;
				ptr->fd = NULL;
			}

			else if (equal(ptr->fe,ptr->fd)){ // Cas (e)
				ptr->info = token (token::EXPONENCIACIO);
				ptr->fd->info = token (2);

			}

			else if (ptr->fd->info.tipus() == token::CANVI_DE_SIGNE and !equal(ptr->fe,ptr->fd->fe)){ // Cas (f)
				node* aux = ptr->fd;
				ptr->fd = ptr->fd->fe;
				aux->fd = NULL;
				aux->fe = ptr;
				ptr = aux;
			}

			else if (ptr->fe->info.tipus() == token::CANVI_DE_SIGNE and !equal(ptr->fe->fe,ptr->fd)){ // Cas(g)
				node* aux = ptr->fe;
				ptr->fe = ptr->fe->fe;
				aux->fe = ptr;
				aux->fd = NULL;
				ptr = aux;

			}

			else if (ptr->fd->info.tipus() == token::DIVISIO and !equal(ptr->fe,ptr->fd->fd) and 
					ptr->fd->fe->info.tipus() == token::CT_ENTERA and ptr->fd->fe->info.valor_enter() == 1){ // Cas (h)
				
				delete ptr->fd->fe;
				ptr->fd->fe = ptr->fe;
				node* borra = ptr;
				ptr = ptr->fd;
				delete borra;
				size-=2;
				

			}

			else if (ptr->fe->info.tipus() == token::DIVISIO and !equal(ptr->fe->fd,ptr->fd) and 
				ptr->fe->fe->info.tipus() == token::CT_ENTERA and ptr->fe->fe->info.valor_enter() == 1){ // Cas (i)

				delete ptr->fe->fe;
				ptr->fe->fe = ptr->fd;
				node* borra = ptr;
				ptr = ptr->fe;
				delete borra,
				size-=2;

			}

			else if (ptr->fe->info.tipus() == token::EXPONENCIACIO and ptr->fd->info.tipus() == token::EXPONENCIACIO and
				equal(ptr->fe->fd,ptr->fd->fd) and !equal(ptr->fe->fe,ptr->fe->fd) and !equal(ptr->fd->fe,ptr->fe->fe)){ // Cas(j)

					ptr->info = token (token::EXPONENCIACIO);
					ptr->fe->info = token (token::MULTIPLICACIO);
					elimina_nodes(ptr->fe->fd);
					ptr->fe->fd = ptr->fd->fe;
					ptr->fd->fe = NULL;
					node* aux = ptr->fd;
					ptr->fd = ptr->fd->fd;
					delete aux;
					--size;



				}

			else if (ptr->fe->info.tipus() == token::EXPONENCIACIO and ptr->fd->info.tipus() == token::EXPONENCIACIO and
				equal(ptr->fe->fe,ptr->fd->fe) and !equal(ptr->fe->fe,ptr->fe->fd) and !equal (ptr->fe->fd,ptr->fd->fd)){ //Cas(k)

				ptr->info = token (token::EXPONENCIACIO);
				ptr->fd->info = token (token::SUMA);
				elimina_nodes(ptr->fd->fe);
				ptr->fd->fe = ptr->fe->fd;
				ptr->fe->fd = NULL;
				node* aux = ptr->fe;
				ptr->fe = ptr->fe->fe;
				delete aux;
				--size;



			}


			// CASOS TRIVIALS

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fd->info.tipus() == token::CT_ENTERA){ //Cas 1. Enter i enter
				ptr->info = token (ptr->fe->info.valor_enter() * ptr->fd->info.valor_enter());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fd->info.tipus() == token::CT_ENTERA and ptr->fe->info.tipus() == token::CT_RACIONAL){ // Cas2. Enter i racional
				

				token t(racional(ptr->fe->info.valor_racional().num()*ptr->fd->info.valor_enter(),ptr->fe->info.valor_racional().denom()));
				if (t.valor_racional().num() % t.valor_racional().denom() == 0){
					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				}

				else ptr->info = t;

				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fd->info.tipus() == token::CT_RACIONAL and ptr->fe->info.tipus() == token::CT_ENTERA){ //Cas3. Racional i enter
				

				token t(racional(ptr->fd->info.valor_racional().num()*ptr->fe->info.valor_enter(),ptr->fd->info.valor_racional().denom()));
				if (t.valor_racional().num() % t.valor_racional().denom() == 0){
					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				}

				else ptr->info = t;

				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL and ptr->fd->info.tipus() == token::CT_RACIONAL){ // Cas4. Racional i racional
				token t(racional(ptr->fe->info.valor_racional()*racional(ptr->fd->info.valor_racional())));
				if (t.valor_racional().num() % t.valor_racional().denom() == 0){

					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				}
				else ptr->info = t;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_REAL or ptr->fd->info.tipus() == token::CT_REAL){ // Agrupa tots els casos reals - NO CONFIRMAT
		
				ptr->info = token(ptr->fe->info.valor_real()*ptr->fd->info.valor_real());
				pinta(ptr);
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;


			}





		} // ACABA MULTIPLICACIO

		else if (ptr->info.tipus() == token::DIVISIO){

			if (ptr->fd->info.tipus() == token::CT_ENTERA and ptr->fd->info.valor_enter()==0) throw error (DivPerZero); // Cas (a)

				

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fe->info.valor_enter()==0){ // Cas(b)
				elimina_nodes(ptr->fd);
				ptr->fd = NULL;
				node* borra = ptr;			
				ptr = ptr->fe;
				delete borra;
				--size;

			}

			else if (ptr->fd->info.tipus() == token::CT_ENTERA and ptr->fd->info.valor_enter()==1){ // Cas (c)
				
				node* borra = ptr;
				node* borra2 = ptr->fd;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				delete borra2;
				size-=2;

			}

			 if (equal(ptr->fe,ptr->fd)){ // Cas(d)

				node* borra = ptr;
				node* borra2 = ptr->fe;
				ptr = ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
				elimina_nodes(borra2);				

			}

			else if (ptr->fd->info.tipus() == token::CANVI_DE_SIGNE and !(equal(ptr->fe,ptr->fd->fe))){ // Cas(e)

				node* _fd = ptr;
				node* aux = ptr->fd;
				_fd->fd = ptr->fd->fe;
				ptr->fd->fe = NULL;

				ptr = aux;
				ptr->fe = _fd;
				ptr->fd = NULL;

			}

			else if (ptr->fd->info.tipus() == token::DIVISIO and !(equal(ptr->fe,ptr->fd->fd))){ // Cas (f)
				ptr->info = token (token::MULTIPLICACIO);
				node* aux = ptr->fd;
				ptr->fd = ptr->fd->fd;
				aux->fd = NULL;

				elimina_nodes(aux);

			}

			else if (ptr->fd->info.tipus() == token::EXPONENCIACIO and ptr->fe->info.tipus() == token::EXPONENCIACIO){



				if (equal(ptr->fe->fd,ptr->fd->fd) and !equal(ptr->fe->fe,ptr->fd->fe)){ // Cas (g)
					
					ptr->info = token (token::EXPONENCIACIO);
					ptr->fe->info = token (token::DIVISIO);

					node* aux = ptr->fd;
					ptr->fd = ptr->fd->fd;
					elimina_nodes(ptr->fe->fd);
					ptr->fe->fd = NULL;
					ptr->fe->fd = aux->fe;
					delete aux;
					--size;
				}

				if (equal(ptr->fe->fe,ptr->fd->fe) and !equal(ptr->fe->fd,ptr->fd->fd)){ // Cas (h)

					ptr->info = token(token::EXPONENCIACIO);
					ptr->fd->info = token(token::RESTA);

					node* c = ptr->fe;
					ptr->fe = ptr->fe->fe;
					elimina_nodes(ptr->fd->fe);
					ptr->fd->fe = c->fd;

					delete c;
					--size;
				} 

			}
			// CASOS TRIVIALS

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fd->info.tipus() == token::CT_ENTERA){ // Cas 1. Dos enters
				if (ptr->fe->info.valor_enter() % ptr->fd->info.valor_enter() == 0){
					ptr->info = token (ptr->fe->info.valor_enter() / ptr->fd->info.valor_enter());
				}
				else ptr->info = token (racional(ptr->fe->info.valor_enter(),ptr->fd->info.valor_enter()));
				
				
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fd->info.tipus() == token::CT_RACIONAL){ // Cas2. Enter i racional
				token t (racional(racional(ptr->fe->info.valor_enter(),1) / ptr->fd->info.valor_racional()));
				if (t.valor_racional().num() % t.valor_racional().denom() == 0)
					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				else ptr->info = t;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL and ptr->fd->info.tipus() == token::CT_ENTERA){ // Cas3. Racional i enter
				token t (racional(ptr->fe->info.valor_racional()) / racional(ptr->fd->info.valor_enter(),1));
				if (t.valor_racional().num() % t.valor_racional().denom() == 0)
					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				else ptr->info = t;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL and ptr->fd->info.tipus() == token::CT_RACIONAL){ // Cas4.Dos racionals
				token t (ptr->fe->info.valor_racional() / ptr->fd->info.valor_racional());
				if (t.valor_racional().num() % t.valor_racional().denom() == 0)
					ptr->info = token (t.valor_racional().num() / t.valor_racional().denom());
				else ptr->info = t;
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_REAL or ptr->fd->info.tipus() == token::CT_REAL){ // Casos amb reals
				ptr->info = token (ptr->fe->info.valor_real() / ptr->fd->info.valor_real());
				delete ptr->fe;
				delete ptr->fd;
				ptr->fe = NULL;
				ptr->fd = NULL;
				size-=2;

			}
			
		} // ACABA DIVISIO

		else if (ptr->info.tipus() == token::CANVI_DE_SIGNE){
			if ((ptr->fe->info).tipus() == token::CANVI_DE_SIGNE){				
				node* borra = ptr->fe;
				node* borra2 = ptr;
				ptr = ptr->fe->fe;
				delete borra;
				delete borra2;
				size-=2;
			}

			else if (ptr->fe->info.tipus() == token::CT_ENTERA){
				node* borra = ptr;
				ptr = ptr->fe;
				--size;
				ptr->info = token (ptr->info.valor_enter() * -1);
				delete borra;

			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL){
				node* borra = ptr;
				ptr = ptr->fe;
				--size;
				ptr->info = token (racional(ptr->info.valor_racional().num()*-1,ptr->info.valor_racional().denom()));
				delete borra;
			}

			else if (ptr->fe->info.tipus() == token::CT_REAL){
				node* borra = ptr;
				ptr = ptr->fe;
				--size;
				ptr->info = token (double(ptr->info.valor_real()*-1));
				delete borra;
			}

		}

		else if (ptr->info.tipus() == token::SIGNE_POSITIU){
			node* borra = ptr;
			ptr = ptr->fe;
			--size;
			delete borra;

		}

		else if (ptr->info.tipus() == token::SQRT){
			if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fe->info.valor_enter()<0) throw error (SqrtDeNegatiu); // Cas (a)

			else if (ptr->fe->info.tipus() == token::CT_ENTERA and ptr->fe->info.valor_enter() == 0){ // Cas(b)
				node* aux = ptr;
				ptr = aux->fe;
				delete aux;
				--size;
			}

			else if (ptr->fe->info.tipus() == token::CT_REAL){ //Cas(b)
				node* borra = ptr;
				ptr=ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
				ptr->info = token(sqrt(ptr->info.valor_real()));

				

			}

			else {
				ptr->info = token (token::EXPONENCIACIO);
				ptr->fd = new node;
				ptr->fd->fe = NULL;
				ptr->fd->fd = NULL;
				ptr->fd->info = token (racional(1,2));
				++size;
			}




		}

		else if (ptr->info.tipus() == token::EVALF){
			if (ptr->fe->info.tipus() == token::CT_REAL){ // Cas 1. Real
				node* borra = ptr;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;

			}

			else if (ptr->fe->info.tipus() == token::CT_ENTERA){ // Cas2. Enter
				node* borra = ptr;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
				ptr->info = token (double(ptr->info.valor_enter()));


			}

			else if (ptr->fe->info.tipus() == token::CT_RACIONAL){ // Cas3. Racional
				node* borra = ptr;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
				ptr->info = token(ptr->info.valor_real());

			}

			else if (ptr->fe->info.tipus() == token::CT_E){ //Cas4.E
				node* borra = ptr;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
				ptr->info = token(double(2.718281828));


			}

			else if (ptr->fe->info.tipus() == token::VARIABLE) { // Cas5.Variable
				node* borra = ptr;
				ptr = ptr->fe;
				ptr->fe = NULL;
				ptr->fd = NULL;
				delete borra;
				--size;
			}

			else { 




			}


		}


		
	}
}


bool expressio::equal(const node* a, const node* b) const{
	//Pre: Cert
	//Post: Retorna cert si el node a és igual al node b

	bool eq = false;

	if (a == NULL and b == NULL) eq = true;
	else if ((a == NULL) xor (b == NULL)) eq = false;
	else if (a->info.tipus() != b->info.tipus()) eq = false;
	else if (a->info != b->info) eq = false;
	else {
		eq = equal(a->fe,b->fe) and equal(a->fd,b->fd);
	}

	return eq;
}

expressio::node* expressio::llegeix (list<token>::const_iterator it, list<token>::const_iterator fi){
	//Pre: Cert
	//Post: H ha un nou arbre de punters

	node* nou = NULL;

	stack<node*> s;
	size = 0;

	while (it != fi){
		token::codi c = (*it).tipus();

		if (c == token::CT_ENTERA or c == token::CT_RACIONAL or c == token::CT_REAL or c == token::CT_E){
			nou = new node;
			nou->info = ((*it));
			nou->fd = nou->fe = NULL;
			s.push(nou);
			size++;

		}
		else if (c == token::VARIABLE){
			nou = new node;
			nou->info = ((*it));
			nou->fd = nou->fe = NULL;
			s.push(nou);
			size++;

		}
		else if (c == token::CANVI_DE_SIGNE or c == token::SQRT or c==token::EVALF){ // CONVENI SERA EL FILL ESQUERRA
			if (s.size() < 1) throw error (ErrorSintactic);
			else{
				nou = new node;
				nou->info = ((*it));
				nou->fd = NULL;
				// TREIEM PILA
				node* a1 = s.top();
				s.pop();
				nou->fe = a1;
				s.push(nou);
				++size;

			}
		}
		else if (c == token::OBRIR_PAR) throw error(ErrorSintactic); // SE DETECTA ERROR
		else if (c == token::SUMA or c == token::RESTA or c == token::MULTIPLICACIO or c == token::DIVISIO or c == token::EXPONENCIACIO){
			if (s.size() < 2) throw error(ErrorSintactic);
			else{
				node* a2 = s.top();
				s.pop();
				node* a1 = s.top();
				s.pop();
				nou = new node;
				nou->info = ((*it));
				nou->fe = a1;
				nou->fd = a2;
				size++;

				s.push(nou);
			}
		}
		++it;
	}

	if (s.size()==1){
		
	}
	else{
		throw error(ErrorSintactic);
	}
	return s.top();
}


expressio::~expressio() throw(error){
	//Pre: Cert
	//Post: S'ha borrat els nodes del p.i
	elimina_nodes(root);
	
}

void expressio::print_list (const list<token> &l){
	//Pre: Cert
	//Post: Res
	list<token>::const_iterator it = l.begin();
	while (it != l.end()){
		token t = (*it);
		if (t.tipus()==token::CT_ENTERA)cout << (t.valor_enter())<<" ";
		else if (t.tipus()==token::SUMA) cout << "+ ";
		else if (t.tipus()==token::RESTA) cout << "- ";
		else if (t.tipus()==token::MULTIPLICACIO) cout << "* ";
		else if (t.tipus()==token::DIVISIO) cout << "/ ";
		else if (t.tipus()==token::OBRIR_PAR) cout << "( ";
		else if (t.tipus()==token::TANCAR_PAR) cout << ") ";
		else if (t.tipus()==token::CANVI_DE_SIGNE) cout << "-- ";
		else if (t.tipus()==token::SQRT) cout << "sqrt()";
		else if (t.tipus()==token::EXPONENCIACIO) cout << "^";
		else if (t.tipus()==token::VARIABLE) cout << (t.identificador_variable())<<" ";
		else if (t.tipus()==token::CT_RACIONAL) cout << "["<<(t.valor_racional().num())<<" / "<<(t.valor_racional().denom())<<"] ";
		else if (t.tipus()==token::CT_REAL){
			std::ostringstream os;
			os << t.valor_real();
			string str = os.str();
			cout << str;
		}
		else if (t.tipus()==token::EVALF) cout <<" EVALF ";
		else if (t.tipus()==token::CT_E) cout <<" CT_E ";

		++it;
	}
	cout << endl;

}

void expressio::recull_variables(list<string> & l,const node* n) const{
	//Pre: Cert
	//Post: La llista l té tots les variables de l'expressio p.i
	if (n != NULL){
		if ((n->info).tipus()==token::VARIABLE and !(existence_variable(l,n))){
			l.push_back((n->info).identificador_variable());
		}
		recull_variables(l,n->fe);
		recull_variables(l,n->fd);
	}
}

bool expressio::existence_variable (const list<string> &l,const node* &n) const
//Pre: n no ha de ser null
//Post: Retorna cert si existeix i fals si no existeix en la llista la variable del node n
{
	bool hi_es = false;
	list<string>::const_iterator it = l.begin();
	while (it != l.end() and !hi_es){

		if ((*it) == n->info.identificador_variable()) hi_es = true;
		else ++it;
	}
	return hi_es;

}

  void expressio::list_of_tokens(list<token> & lt) throw(error){
  	//Pre: Cert
	//Post: lt te els tokens del p.i en postifxa (operacions) i infixa (CANVI_SIGNE)
  	get_operations (lt,root);

  }

  void expressio::get_operations (list<token> & lt,node* n) const{
  	//Pre: Cert
	//Post: lt te els tokens del p.i en postifxa (operacions) i infixa (CANVI_SIGNE)
  	if (n != NULL){
  		if (n->info.tipus() == token::SUMA or n->info.tipus() == token::RESTA or n->info.tipus() == token::MULTIPLICACIO
  			or n->info.tipus() == token::DIVISIO){
  			get_operations(lt,n->fe);
  			lt.push_back(n->info);
  			get_operations(lt,n->fd);
  		}

  		else if (n->info.tipus() == token::CT_ENTERA or n->info.tipus() == token::CT_REAL or n->info.tipus() == token::CT_RACIONAL
  			or n->info.tipus() ==token::CT_E or n->info.tipus() == token::NULLTOK or n->info.tipus() == token::VARIABLE){
  			lt.push_back(n->info);
  		}

  		else if (n->info.tipus() == token::CANVI_DE_SIGNE or n->info.tipus() == token::SIGNE_POSITIU or
  			n->info.tipus() == token::SQRT){
  			
  			lt.push_back(n->info);
  			lt.push_back(token(token::OBRIR_PAR));
  			get_operations(lt,n->fe);
  			lt.push_back(token(token::TANCAR_PAR));
  		}
  	}


  }


