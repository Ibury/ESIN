#include <iostream>
#include "token.hpp"
using namespace std;

int main(){
	/*racional r (5,1);

	token t(r);

	racional l (2,3);

	token s (l);

	cout << (t == s) <<endl;

	token p = s;*/

	int n;
	string var_name;
	double x;
	int num, den;
	racional r;

	token te;
	token::codi cod;
	cod = token::codi::NULL_TOKEN;
	te = token(cod);

	cout << "El token es de tipus: " << te.tipus() << endl;

	string c;
	while (cin >> c){
		token t;
		/*racional a(n1,d1);
		racional b(n2,d2);
		racional r;
		if (c=="+") r = a + b;
		else if (c=="-") r = a - b;
		else if (c=="*") r = a * b;
		else if (c=="/") r = a / b;
		else if (c=="==") cout << "a == b -> "<<(a==b)<<endl;
		else if (c=="!=") cout << "a != b -> "<<(a!=b)<<endl;
		else if (c=="<") cout << "a < b -> "<<(a<b)<<endl;
		else if (c=="<=") cout << "a <= b -> "<<(a<=b)<<endl;
		else if (c==">") cout << "a > b -> "<<(a>b)<<endl;
		else if (c==">=") cout << "a >= b -> "<<(a>=b)<<endl;
		cout << "Escriu la operacio que desitgis: + - * / == != < <= > >="<<endl;
		*/

		if (c=="ENUM") {
			cin >> n;
			token::codi cod = (token::codi)n;
			t = token(cod);
		}else if(c=="INT") {
			cin >> n;
			t = token(n);
		}else if(c=="RACIONAL") {
			cin >> num >> den;
			r = racional(num,den);
			t = token(r);
		}else if(c=="REAL") {
			cin >> x;
			t = token(x);
		}else if(c=="VARIABLE") {
			cin >> var_name;
			t = token(var_name);
			cout << t.identificador_variable() << endl;
		}

		cout << "El token es de tipus: " << t.tipus() << endl;
	}
}