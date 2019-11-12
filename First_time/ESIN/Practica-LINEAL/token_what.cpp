#include <iostream>
#include <list>
#include "token.hpp"
using namespace std;

int main(){
	token t(token::SUMA);
	list<token> l;
	l.push_back(t);
	cout << "Codi -> "<<t.tipus()<<endl;

	list<token>::const_iterator it = l.begin();
	cout << "2n Codi -> "<<(*it).tipus()<<endl;

	vector<token> v ;
	v.push_back(t);
	cout << "3r Codi -> "<<v[0].tipus()<<endl;

	cout << "4t Codi -> "<<t.tipus()<<endl;

}