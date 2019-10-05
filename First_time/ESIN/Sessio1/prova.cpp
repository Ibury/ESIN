#include <iostream>
#include "cj_enters.hpp"
using namespace std;

int main(){

cj_enters a;
int t;
cin >> t;


while (t!=66){
 a.insereix(t);
 cin >> t;
}



cj_enters b;
cin >> t;
while (t!=66){
	b.insereix(t);
	cin >> t;
}



cout<<"PRINT DEL MAIN :"<<endl;
a.print(std::cout);
b.print(std::cout);

cout << "SON IGUALS : "<<(a==b)<<endl;
cout << "SON DIFERENTS : "<<(a!=b)<<endl;






}
