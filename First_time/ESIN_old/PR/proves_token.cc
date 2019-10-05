#include <iostream>
#include "token.h"
#include <sstream>
#include <string>
#include <queue>
using namespace std;

int main() {
	string s;
	queue<token> st;
	cout<<"============================="<<endl;
	
	//INV: Mentre hi hagi dades al canal d'entrada.
	while (getline(cin,s)){

		istringstream ss(s);
		string p;
		while (ss >> p){
			
			token t (p);
			st.push(t);
			
			cout<<"TOKEN: "<<t<<endl;
			cout<<"És un operador unari: "<<t.es_operador_unari()<<endl;
			cout<<"És un operador binari: "<<t.es_operador_binari()<<endl;
			cout<<"És un operador commutatiu: "<<t.es_operador_commutatiu()<<endl;
			cout<<"És un valor booleà: "<<t.es_boolea()<<endl;
			cout<<"És un valor enter: "<<t.es_enter()<<endl;
			cout<<"És una variable: "<<t.es_variable()<<endl;
			cout<<"Valor string: "<<t.to_string()<<endl;
			if (st.size()==2){
				
				token l = st.front();
				st.pop();
				cout<<st.front()<<" i "<<st.front()<<" són iguals: "<< (st.front()==st.front()) <<endl;
				cout<<st.front()<<" i "<<l<<" són iguals: "<< (st.front()==l) <<endl;
				cout<<st.front()<<" i "<<st.front()<<" són diferents: "<< (st.front()!=st.front()) <<endl;
				cout<<st.front()<<" i "<<l<<" són diferents: "<< (st.front()!=l) <<endl;

			}
		
		
			cout<<"============================="<<endl;
		}


	}

}
