#include "conjunt.hpp"
using namespace std;

int main(){
  conjunt <int> a;
  int t;
  cout << "Introdueix conjunt A : "<<endl;
  cin >> t;
  while (t!=10){
     a.insereix(t);
     cin >> t;
   }
a.print(cout);
cout << "MAX : "<<(a.max())<<endl;
cout << "MIN : "<<(a.min())<<endl;

conjunt<int> b;
cout << "Introdueix conjunt B : "<<endl;
cin >> t;
while (t!=10){
   b.insereix(t);
   cin >> t;
 }
b.unir(a);
cout << "A QUEDA : "<<endl;
a.print(cout);
cout << "B QUEDA : "<<endl;
b.print(cout);
}
