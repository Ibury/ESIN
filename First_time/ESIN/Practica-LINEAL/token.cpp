#include "token.hpp"
#include <iostream>

token::token(codi cod) throw(error) {

	if(cod == CT_ENTERA or cod == CT_RACIONAL or cod == CT_REAL or cod == VARIABLE) throw error(ConstructoraInadequada);
	this->cod = cod;
}

token::token(int n) throw(error) {

	this->cod = CT_ENTERA;
	this->n = n;
}

token::token (const racional & r) throw(error) {

	this->cod = CT_RACIONAL;
	this->r = r;
}

token::token(double x) throw(error) {

	this->cod = CT_REAL;
	this->x = x;
}

token::token(const string &var_name) throw(error) {
	if (not comprovaVariable(var_name)) throw error(IdentificadorIncorrecte);
	this->cod = VARIABLE;
	this->var_name = var_name;
}

token::token(const token &t) throw(error) {
	cod = t.cod;
	r = t.r;
	var_name = t.var_name;
	x = t.x;
	n = t.n
}

token & token::operator=(const token & t) throw(error) {

	token nou;

	nou.cod = this->cod;
	nou.r = this->r;
	nou.var_name = this->var_name;
	nou.x = this->x;
	nou.n = this->n;

	this->cod = t.cod;
	this->r = t.r;
	this->var_name = t.var_name;
	this->x = t.x;
	this->n = t.n;

	return *this;
}

token::~token() throw(){}

token::codi token::tipus() const throw() {
	return this->cod;
}

int token::valor_enter() const throw(error) {
	if (cod!=CT_ENTERA and cod !=CT_REAL and cod != CT_RACIONAL) throw error (ConsultoraInadequada);

	int res;
	if (cod == CT_ENTERA)res = n;
	else if (cod == CT_REAL) res = x;
	else if (cod == CT_RACIONAL) res = r.part_entera();
	return res;

}

racional token::valor_racional() const throw(error) {
	if (cod!=CT_RACIONAL) throw error (ConsultoraInadequada);
	return this->r;
}

double token::valor_real() const throw(error) {
	if (cod!=CT_REAL and cod!=CT_ENTERA and cod!=CT_RACIONAL) throw error (ConsultoraInadequada);

	double t;

	if (cod == CT_ENTERA) t = double (n);
	else if (cod == CT_RACIONAL) t = r.num () / r.denom();
	else if (cod == CT_REAL) t = x;
	return t;
}

string token::identificador_variable() const throw(error) {
	if (cod!=VARIABLE) throw error (ConsultoraInadequada);
	return this->var_name;
}

bool token::operator==(const token & t) const throw() {
	bool iguals = true;

	if (this->cod == CT_ENTERA) {
		iguals = valor_enter() == t.valor_enter();
	}else if(this->cod == CT_RACIONAL) {
		iguals = valor_racional() == t.valor_racional();
	}else if (this->cod == CT_REAL) {
		iguals = valor_real() == t.valor_real();
	}else if (this->cod == VARIABLE) {
		iguals = this->var_name == t.var_name;
	}

	return (this->cod == t.cod and iguals);
}

bool token::operator!=(const token & t) const throw() {
	return not (token::operator==(t));
}

bool token::operator>(const token & t) const throw(error) {
	if ((cod != CANVI_DE_SIGNE and cod != SIGNE_POSITIU and cod != MULTIPLICACIO and cod != DIVISIO and cod != SUMA and cod != RESTA)
		or (t.cod != CANVI_DE_SIGNE and t.cod != SIGNE_POSITIU and t.cod != MULTIPLICACIO and t.cod != DIVISIO and t.cod != SUMA and t.cod != RESTA)) throw error (PrecedenciaEntreNoOperadors);
	bool ho_es = false;

	if (cod == CANVI_DE_SIGNE or cod == SIGNE_POSITIU){
		if (t.cod == MULTIPLICACIO or t.cod == DIVISIO or t.cod == SUMA or t.cod == RESTA) ho_es = true;
	}

	else if (cod == MULTIPLICACIO or cod == DIVISIO){
		if (t.cod == SUMA or t.cod == RESTA) ho_es = true;
	}

	return ho_es;
}
bool token::operator<(const token & t) const throw(error) {

	return (not (token::operator>(t))) and cod != t.cod;
}

void token::easytolower(char &in){
	if(in<='Z' && in>='A')
	in-=('Z'-'z');
}


bool token::comprovaVariable(const string &var) {
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
