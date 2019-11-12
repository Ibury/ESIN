#include "expressio.hpp"
#include <stack>
#include <list>
using namespace std;

typename list<token>::const_iterator citer;
typename list<token>::iterator iter;


void conversion(string &str, int num) {
	stack<char> st;
	do {
    int digit = num % 10;
    st.push('0' + digit);
    num /= 10;
	} while (num > 0);

	while (st.size()>0) {
		str += st.top();
		st.pop();
	}

}

string dep = "";
void expressio::pintar(node* ptr)
{
  string d1=dep;
  if (ptr==NULL)
    cout<<".";
  else {

		string str="";


		if (ptr->info.tipus()==token::CT_ENTERA) conversion(str,ptr->info.valor_enter());
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
	dep = "";
	pintar(ptr);
	cout << endl << "Arbre de mida: " << size << endl;
}

void expressio::infixa_a_postifxa (list<token> &t, const list<token> &l) {

	stack<token> s;
	list<token>::const_iterator it = l.begin();
	while (it != l.end()){
		token::codi c = (*it).tipus();


		if (c == token::CT_ENTERA or c == token::CT_REAL or c == token::CT_RACIONAL){
			t.push_back((*it));
		}
		else if (c == token::VARIABLE){
			t.push_back((*it));

		}
		else if (c == token::OBRIR_PAR or c == token::CANVI_DE_SIGNE or c == token::SQRT or c == token::EXPONENCIACIO){
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
						while ((s.size()>0) and ((s.top() > (*it)) or (s.top() == (*it)))){
							cout << "El token actual ("<<(*it).tipus()<<") less priority than "<<(s.top().tipus())<<endl;
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
	if (t.tipus() != token::NULLTOK and t.tipus() != token::CT_ENTERA and t.tipus() != token::CT_RACIONAL
	and t.tipus() != token::CT_REAL and t.tipus() != token::CT_E and
	t.tipus() != token::VARIABLE and t.tipus() != token::VAR_PERCENTATGE) throw error (ErrorSintactic);

	root = new node;
	root->info = t;
	root->fe = root->fd = NULL;
	size = 1;


}

expressio::expressio(const list<token> & l) throw(error){

	if (l.size() < 1 ) throw error (ErrorSintactic);

	//INFIXA A POSTFIXA

	list<token> t;
	infixa_a_postifxa(t,l);

	cout << "Tamany = "<<t.size()<<endl;

	print_list(t);

	root = llegeix(t.begin(),t.end());

	pinta(root);
}

void expressio::elimina_nodes(node* ptr) {
	if (ptr!=NULL) {
		elimina_nodes(ptr->fd);
		elimina_nodes(ptr->fe);
		delete ptr;
		ptr=NULL;
	}
}

expressio::node* expressio::copia_expressio(const node* ptr) throw()
//COST: Θ(2^n)
//PRE: Node a copiar. En la primera crida a la funció, ptr és el primer node (l'arrel de l'arbre).
//POST: Copia l'arbre desde el fons fins l'arrel.
{
	node* ptra=NULL;

	if (ptr != NULL) {

		ptra = new node;
		try {
			ptra->fe = copia_expressio(ptr->fe);
			ptra->fd = copia_expressio(ptr->fd);
			ptra->info = ptr->info;
		}catch(error) {
			delete ptra;
			throw;
		}
	}

	return ptra;
}

expressio::expressio(const expressio & e) throw(error){

	size = e.size;
	root = copia_expressio(e.root);

}

expressio & expressio::operator=(const expressio & e) throw(error){

	expressio ex(e);

	node* n = root;
	root = ex.root;
	size = ex.size;

	ex.root = n;

	return *this;

}


expressio::operator bool() const throw(){
	return size==0;
}

bool expressio::operator==(const expressio & e) const throw(){
	bool iguals = true;

	if (size != e.size)	iguals = false;
	else iguals = equal(root,e.root);

	return iguals;
}

bool expressio::operator!=(const expressio & e) const throw(){
	return not (expressio::operator==(e));
}

void expressio::vars(list<string> & l) const throw(error){

	recull_variables(l,root);
}

void expressio::apply_substitution(const string & v, const expressio & e) throw(error){

	// CAS Directe
	if ((root->info).tipus() == token::VARIABLE){
		if ((root->info).identificador_variable() == v){
			expressio u (e);
			*this = u;
		}
	}

	else 	get_allocation(v,e,root,root,true);


	pintar(root);
	cout << endl;
	cout << "SIZE -> "<<size<<endl;
}

void expressio::get_allocation (const string &v, const expressio &e, node* n,node* act,bool b){

	if (n!=NULL){
		if ((n->info).tipus() == token::VARIABLE){

			if ((n->info).identificador_variable() == v){
				get_allocation(v,e,n->fd,n,false);
				get_allocation(v,e,n->fe,n,true);

				if (b){
					expressio u(e); // SWAAAP
					act->fe = e.root;
					size+=u.size;
				}

				else {
					expressio u(e);
					act->fd = e.root;
					size+=u.size;
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

}

void expressio::simplify() throw(error){
	simplificar(root);
	cout << "Arbre simplificat"<<endl;
	pinta(root);
}

void expressio::simplificar(node* ptr ) {
	if (ptr != NULL and (ptr->fe != NULL and ptr->fd != NULL)) {

		if (ptr->fd != NULL) simplificar(ptr->fd);
		if (ptr->fe != NULL) simplificar(ptr->fe);

		token::codi c = ptr->info.tipus();
		if (c == token::SUMA or c == token::RESTA or c == token::DIVISIO or c == token::MULTIPLICACIO) {
				if ((ptr->fe->info.tipus() == token::CT_ENTERA or ptr->fe->info.tipus() == token::CT_REAL or
						 ptr->fe->info.tipus() == token::CT_RACIONAL) and (ptr->fd->info.tipus() == ptr->fe->info.tipus())) {

						if (c == token::SUMA) {
											token tk(ptr->fe->info.valor_enter()+ptr->fd->info.valor_enter());
											ptr->info = tk;
						}else if(c == token::RESTA) {
											token tk(ptr->fe->info.valor_enter()-ptr->fd->info.valor_enter());
											ptr->info = tk;
						}else if(c == token::MULTIPLICACIO) {
											token tk(ptr->fe->info.valor_enter()*ptr->fd->info.valor_enter());
											ptr->info = tk;
						}else if(c == token::DIVISIO) {
											token tk(ptr->fe->info.valor_enter()/ptr->fd->info.valor_enter());
											ptr->info = tk;
						}

						delete ptr->fe;
						delete ptr->fd;
						ptr->fe = NULL;
						ptr->fd = NULL;
						size -=2;
				}
		} //ELSE IF SQRT or EVALF or EXP or LOG etc...
	}
}

/*
void expressio::list_of_tokens(list<token> & lt) throw(error){
	read_infix(lt,root);
}
*/
/*void expressio::read_prefix(list<string> & l, node* ptr) {

	if (ptr != NULL) {
		if (ptr->info.tipus() == token::VARIABLE) {
			bool trobat = false;

			list<token>::const_iterator it = l.begin();

			while (it != l.end() and not trobat) {
				if ((*it) == ptr->info.identificador_variable()) trobat = true;
			}
			if (not trobat) l.push_back(ptr->info.identificador_variable());
		}
		read_prefix(l, ptr->fe);
		read_prefix(l, ptr->fd);
	}
}*/
/*
void expressio::read_infix(list<token> & lt, node* ptr) {

	if (ptr != NULL) {
		read_prefix(lt, ptr->fe);
		lt.push_back(ptr->info);
		read_prefix(lt, ptr->fd);
	}
}
*/
bool expressio::equal(const node* a, const node* b) const{

	bool eq = false;

	if (a == NULL and b == NULL) eq = true;
	else if (a == NULL xor b == NULL) eq = false;
	else if (a->info != b->info) eq = false;
	else {
		eq = equal(a->fe,b->fe) and equal(a->fd,b->fd);
	}

	return eq;
}

expressio::node* expressio::llegeix (list<token>::const_iterator it, list<token>::const_iterator fi){

	// ABANS DE TOT -> IDEA : la stack sera de punters node, i anirem montantlos entre ells fins que quedi un.
	// ES NECESSITA TENIR UNA LLISTA DE PUNTERS DE NODES I AQUESTA ESTARA EN POSTORDRE.
	node* nou = NULL;

	stack<node*> s;
	size = 0;

	while (it != fi){
		token::codi c = (*it).tipus();

		if (c == token::CT_ENTERA){
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
		else if (c == token::CANVI_DE_SIGNE or c == token::SQRT or c == token::EXPONENCIACIO){ // CONVENI SERA EL FILL ESQUERRA
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
		else if (c == token::SUMA or c == token::RESTA or c == token::MULTIPLICACIO or c == token::DIVISIO){
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

				cout <<endl<<endl<< "FUSION -> ";
				pinta(nou);

				s.push(nou);
			}
		}
		++it;
	}

	if (s.size()==1){
		 cout << "HI HA UN ARBRE"<<endl;

		// node* pare = s.top();
		// s.pop();
	}else{
		throw error(ErrorSintactic);
		cout << "NO OK, size = "<<s.size()<<endl;
		cout << "ARBOL 1 -> "<<endl;

		node* primer = s.top();
		s.pop();
		node* segon = s.top();
		pinta(primer);
		pinta(segon);

	}
	return s.top();
}


expressio::~expressio() throw(error){
	elimina_nodes(root);
}

void expressio::print_list (const list<token> &l){
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
		else if (t.tipus()==token::VARIABLE) cout << (t.identificador_variable());
		++it;
	}
	cout << endl;

}

void expressio::recull_variables(list<string> & l,const node* n) const{
	if (n != NULL){
		if ((n->info).tipus()==token::VARIABLE){
			l.push_back((n->info).identificador_variable());
		}
		recull_variables(l,n->fe);
		recull_variables(l,n->fd);
	}
}
