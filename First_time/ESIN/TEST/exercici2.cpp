// File: exercici1.cpp
// Subject: Programa principal de l'exercici 1

#include <iostream>

using namespace std;

#include "cj_enters.hpp"

// Defineix un operador de sortida para cj_enters
ostream& operator<< (ostream& os, cj_enters& cj) {
  cj.print(os);
  return os;
}

// Defineix un operador d'entrada per cj_enters
istream& operator>> (istream& is, cj_enters& cj) {
  int n;
  do {
    is >> n;
    if (n != 0) {
      cj.insereix( n );
    }
  } while (n != 0);
  return is;
}

// Programa principal que demana un cj_enters (una sequencia 
// d'enters acabada en zero) i comprova si un enter donat pertany 
// o no a aquest conjunt.
int main () {
  cj_enters cj;
  cout << "Introdueix el primer conjunt (0 indica el final del cj):" << endl;
  cin >> cj;
  cout << "El conjunt es:" << endl;
  cout << cj;

  /*cj_enters cj2;
  cout << "Introdueix el segon conjunt (0 indica el final del cj):" << endl;
  cin >> cj2;
  cout << "El conjunt es:" << endl;
  cout << cj2;


  cout << "El conjunt A i B son iguals:" << ((cj==cj2)?" SI":" NO") << endl;

  cout << "El conjunt A i B son diferents:" << ((cj!=cj2)?" SI":" NO") << endl;

*/

  //cout << "Element " << num << (cj.conte(num)?" SI":" NO");
  //cout << " esta present en el conjunt." << endl;
  /*cj_enters cj2;
  cout << "Introdueix el segon conjunt (0 indica el final del cj):" << endl;
  cin >> cj2;
  cout << "El conjunt es:" << endl;
  cout << cj2;
  cout <<endl<< "Unió de conjunts" << endl;
  cj.unir(cj2);
  cout << "El conjunt resultant es:" << endl;
  cout << cj;*/

  cj_enters cj3;
  cout << "Introdueix el tercer conjunt (0 indica el final del cj):" << endl;
  cin >> cj3;
  cout << "El conjunt es:" << endl;
  cout << cj3;

  cout <<endl<< "Cardinal conjunto: " <<cj.card() << endl;

  cout <<endl<< "Intersecció de conjunts" << endl;
  cj.intersectar(cj3);
  cout << "El conjunt resultant es:" << endl;
  cout << cj;

  cj_enters cj4;
  cout << "Introdueix el quart conjunt (0 indica el final del cj):" << endl;
  cin >> cj4;
  cout << "El conjunt es:" << endl;
  cout << cj4;

  cout <<endl<< "Resta de conjunts" << endl;
  cj.restar(cj4);
  cout << "El conjunt resultant es:" << endl;
  cout << cj;

}
