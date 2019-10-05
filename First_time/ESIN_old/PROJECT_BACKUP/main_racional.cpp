#include <iostream>
#include "racional.hpp"
#include <string>
using namespace std;

int main(){
	//cout << "Introdueix el numerador i denominador del primer racional -> "<<endl;
	int n1,d1,n2,d2;
	//cin >> n >> d;
	//racional a (n,d);
	//cout << "Introdueix el numerador i denominador del segon racional -> "<<endl;
	//cin >> n >> d;
	//racional b (n,d);
	//cout << "Escriu la operacio que desitgis: + - * / == != < <= > >="<<endl;

	
	string c;
	while (cin >> n1 >> d1 >> n2 >> d2 >> c){
		racional a(n1,d1);
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

	}

	//racional a (17,4);
	//racional b (2,9);
	//racional c = a-b;





}