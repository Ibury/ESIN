#include <iostream>
#include "expressio.hpp"
using namespace std;

int main(){
	token t(token::SUMA);
	cout << "Tipus t -> "<<t.tipus()<<endl;
	list<token> l;
	l.push_back(t);

	//PROVES MAIN

	list<token>::const_iterator it = l.begin();

	token prova(*it);

	cout << "TIPUS HEHE XD -> "<<prova.tipus()<<endl;

	expressio s(l);




}
