#include "token.hpp"
#include <iostream>

token::token(codi cod) throw(error) {
/*
	PRE:	codi no pot ser una constant ni una variable
	POST: nou objecte token
*/

	if(cod == CT_ENTERA or cod == CT_RACIONAL or cod == CT_REAL or cod == VARIABLE) throw error(ConstructoraInadequada);
	this->cod = cod;
}

token::token(int n) throw(error) {
/*
	PRE:	codi enter
	POST: nou objecte token
*/

	this->cod = CT_ENTERA;
	this->n = n;
}

token::token (const racional & r) throw(error) {
/*
	PRE:	codi racional
	POST: nou objecte token
*/

	this->cod = CT_RACIONAL;
	this->r = r;
}

token::token(double x) throw(error) {
/*
	PRE:	codi real
	POST: nou objecte token
*/
	this->cod = CT_REAL;
	this->x = x;
}

token::token(const string &var_name) throw(error) {
/*
	PRE:	string variable no pot contindre numero ni simbols que no sigui guió baix
	POST: nou objecte token
*/
	if (not comprovaVariable(var_name)) throw error(IdentificadorIncorrecte);
	this->cod = VARIABLE;
	this->var_name = var_name;
}

token::token(const token &t) throw(error) {
/*
	PRE:	token
	POST: nou objecte token igual al del paràmetre de la funció
*/
	cod = t.cod;
	r = t.r;
	var_name = t.var_name;
	x = t.x;
	n = t.n;

}

token& token::operator=(const token & t) throw(error) {
/*
	PRE:	token
	POST: el p.i es igual al token del paràmetre de la funció
*/

	cod = t.cod;
	r = t.r;
	var_name = t.var_name;
	x = t.x;
	n = t.n;

	return *this;
}

token::~token() throw(){}

token::codi token::tipus() const throw() {
/*
	PRE:	true
	POST: codi del token
*/
	return this->cod;
}

int token::valor_enter() const throw(error) {
/*
	PRE:	true
	POST: valor enter de la constant entera
*/
	if (cod!=CT_ENTERA) throw error (ConsultoraInadequada);
	return n;
}

racional token::valor_racional() const throw(error) {
/*
	PRE:	true
	POST: valor racional de la constant racional
*/
	if (cod!=CT_RACIONAL) throw error (ConsultoraInadequada);
	return this->r;
}

double token::valor_real() const throw(error) {
/*
	PRE:	true
	POST: valor real de la constant real
*/
	if (cod!=CT_REAL) throw error (ConsultoraInadequada);
	return x;
}

string token::identificador_variable() const throw(error) {
/*
	PRE:	true
	POST: valor de la variable, (nom de la variable)
*/
	if (cod!=VARIABLE) throw error (ConsultoraInadequada);
	return this->var_name;
}

bool token::operator==(const token & t) const throw() {
/*
	PRE:	token
	POST: true si el token t i el p.i son iguals
*/
	bool iguals = true;

	if (cod == t.cod) {
		if (this->cod == CT_ENTERA) {
			iguals = valor_enter() == t.valor_enter();
		}else if(this->cod == CT_RACIONAL) {
			iguals = valor_racional() == t.valor_racional();
		}else if (this->cod == CT_REAL) {
			iguals = valor_real() == t.valor_real();
		}else if (this->cod == VARIABLE) {
			iguals = this->var_name == t.var_name;
		}
	}else{
		iguals = false;
	}

	return iguals;
}

bool token::operator!=(const token & t) const throw() {
/*
	PRE:	token
	POST: true si el token t i el p.i son diferents
*/
	return not (token::operator==(t));
}

int token::nivell() const {
/*
	PRE:	true
	POST: nivell de prioritat de cada tipus de token
*/
	int level = 0;

	if (cod == EXPONENCIACIO) level = 5;
	else if (cod == SIGNE_POSITIU or cod == CANVI_DE_SIGNE) level = 4;
	else if (cod == MULTIPLICACIO or cod ==  DIVISIO) level = 3;
	else if (cod == SUMA or cod == RESTA) level = 2;
	else if (cod == EXP or cod == LOG) level = 1;
	else if (cod == OBRIR_PAR or cod == TANCAR_PAR) level = 0;
	else if (cod == ASSIGNACIO or cod == DESASSIGNACIO or cod == BYEBYE) level = 0;
	else if (cod == CT_ENTERA or cod == CT_REAL or cod == CT_RACIONAL) level = 0;
	else if (cod == VARIABLE or cod == VAR_PERCENTATGE) level = 0;
	else if (cod == EXPONENCIACIO or cod == EXP or cod == LOG) level = 0;
	else if (cod == SQRT or cod == EVALF) level = 0;

	return level;
}


bool token::operator>(const token & t) const throw(error) {
/*
	PRE:	token
	POST: true si el p.i és més prioritari que el token t
*/

	int nivpi = nivell(), nivp = t.nivell();

	if (nivpi == 0 or nivp == 0) throw error (PrecedenciaEntreNoOperadors);

	bool ho_es = false;

	if (nivpi > nivp) ho_es = true;

	return ho_es;
}

bool token::operator<(const token & t) const throw(error) {
/*
	PRE:	token
	POST: true si el p.i és menys prioritari que el token t
*/
	return (not (token::operator>(t))) and (nivell()!=t.nivell());
}

void token::easytolower(char &in){
/*
	PRE:	caracter
	POST: caracter in el transforma a minuscules si es una lletra
*/
	if(in<='Z' && in>='A')
	in-=('Z'-'z');
}


bool token::comprovaVariable(const string &var) {
/*
	PRE:	variable
	POST: true si la variable compleix el requisits de contindre només guió baix, lletres i/o no ser una paraula reservada.
*/
	unsigned int i=0;

	string aux = var;
	bool es_var = true;

	for (unsigned int i=0; i<aux.size(); ++i) {
		easytolower(aux[i]);
	}

	if (aux == "unassign" or aux == "e" or aux == "sqrt" or aux == "log" or aux == "exp" or aux == "evalf" or aux == "byebye") es_var = false;

	while (i<var.size() and es_var) {

		if (not((var[i]>='a' or var[i]<='z') and (var[i]>='A' or var[i]<='Z'))) {

			if (var[i]!='_') {
				es_var = false;
			}
		}
		++i;
	}

	return es_var;
}
