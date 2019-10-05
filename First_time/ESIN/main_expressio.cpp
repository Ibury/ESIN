#include <iostream>
#include "expressio.hpp"
#include <sstream>
using namespace std;

void ensenam (list<token> lt){
	
}

int main(){



	list<token> l;
	

	
	/*token t (string("t"));
	l.push_back(t);
	t = token (token::DIVISIO);
	l.push_back(t);
	t = token (string("r"));
	l.push_back(t);
	t = token (token::RESTA);
	l.push_back(t);
	t = token (string("k"));
	l.push_back(t);
	t = token (token::DIVISIO);
	l.push_back(t);
	t = token (string("r"));
	l.push_back(t);*/

	/*token t (string("v"));
	l.push_back(t);
	t = token (token::EXPONENCIACIO);
	l.push_back(t);
	t = token (string("l"));
	l.push_back(t);
	t = token (token::DIVISIO);
	l.push_back(t);
	t = token (string("v"));
	l.push_back(t);
	t = token (token::EXPONENCIACIO);
	l.push_back(t);
	t = token (string("h"));
	l.push_back(t);*/

	
	
	token t (string("v"));
	l.push_back(t);
	t = token (token::SUMA);
	l.push_back(t);
	t = token (token::OBRIR_PAR);
	l.push_back(t);
	t = token (token::CANVI_DE_SIGNE);
	l.push_back(t);
	t = token (string("v"));
	l.push_back(t);
	t = token (token::TANCAR_PAR);
	l.push_back(t);
	
	list<token> lt;


	expressio e (l);

	e.list_of_tokens(lt);


	ensenam(lt);





	/*

	l.clear();
	t = token (3);
	l.push_back(t);
	t = token (token::SUMA);
	l.push_back(t);
	t = token (2);
	l.push_back(t);


	expressio r(l);

	e.apply_substitution("s",r);
*/



	//e.simplify();
	




}
