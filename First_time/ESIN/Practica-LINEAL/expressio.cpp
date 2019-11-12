#include "expressio.hpp"
#include <stack>
#include <list>
using namespace std;

typename list<token>::const_iterator citer;
typename list<token>::iterator iter;


expressio::expressio(const token t) throw(error){
	if (t.tipus() != token::NULLTOK and t.tipus() != token::CT_ENTERA and t.tipus() != token::CT_RACIONAL
	and t.tipus() != token::CT_REAL and t.tipus() != token::CT_E and
	t.tipus() != token::VARIABLE and t.tipus() != token::VAR_PORCENTATGE) throw error (ErrorSintactic);

	root = new node;
	root->info = t;
	root->fe = root->fd = NULL;



}

expressio::expressio(const list<token> & l) throw(error){
	if (l.size() < 1 ) throw error (ErrorSintactic);


	root = llegeix(l.begin(),l.end());

}

expressio::expressio(const expressio & e) throw(error){
	//expressio n;
	//n.s = e.s;


}
/*expressio & expressio::operator=(const expressio & e) throw(error){
	this->s = e.s;
	return *this;

}

expressio::operator bool() const throw(){
	//if (l.size() == 0) return true;
	//else return false;
}

bool expressio::operator==(const expressio & e) const throw(){
	bool iguals = true;

	if (size != e.size)
		iguals = false;
	else
		iguals = equal(root,e.root);

	return iguals;
}

bool expressio::operator!=(const expressio & e) const throw(){
	return not (expressio::operator==(e));
}

void expressio::vars(list<string> & l) const throw(error){
	read_prefix(l,root);
}

void expressio::apply_substitution(const string & v, const expressio & e) throw(error){

}

void expressio::simplify_one_step() throw(error){

}

void expressio::simplify() throw(error){

}

void expressio::list_of_tokens(list<token> & lt) throw(error){
	read_infix(lt,root);
}

void expressio::read_prefix(list<string> & l, node* ptr) {

	if (ptr != NULL) {
		if (ptr->info.tipus() == token::VARIABLE) l.push_back(ptr->info.identificador_variable());
		read_prefix(l, ptr->fe);
		read_prefix(l, ptr->fd);
	}
}

void expressio::read_infix(list<token> & lt, node* ptr) {

	if (ptr != NULL) {
		read_prefix(lt, ptr->fe);
		lt.push_back(ptr->info);
		read_prefix(lt, ptr->fd);
	}
}

bool expressio::equal(const node* &a, const node* &b) const{

	bool eq = false;

	if (a == NULL and b == NULL) eq = true;
	else if (a == NULL xor b == NULL) eq = false;
	else if (a->info != b->info) eq = false;
	else {
		eq = (equal(a->fe,b->fe)) and (equal(a->fd,b->fd));
	}

	return eq;
}
*/
expressio::node* expressio::llegeix (list<token>::const_iterator it, list<token>::const_iterator fi){

node* nou = NULL;
	if (it != fi){
		nou = new node;

		codi t = *(it).tipus();



		//if ((*it).tipus == SUMA or (*)) {

		//}







	}

		return nou;
}

expressio::~expressio() throw(error){

}
