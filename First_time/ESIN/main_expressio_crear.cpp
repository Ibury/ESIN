#include <iostream>
#include "expressio.hpp"
#include <list>
using namespace std;

void imprimeix_llista_var (const list<string> s){
  list<string>::const_iterator it = s.begin();
  while (it != s.end()){
    string s = (*it);
    cout << s <<" ";
    ++it;
  }
  cout << endl;

}



int main(){

  /*token t (int(4));
  list<token> l;
  l.push_back(t);
  t = token (token::MULTIPLICACIO);
  l.push_back(t);
  t = token (int(2));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (token::OBRIR_PAR);
  l.push_back(t);
  t = token (int(12));
  l.push_back(t);
  t = token (token::DIVISIO);
  l.push_back(t);
  t = token (int(3));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);
  t = token (token::RESTA);
  l.push_back(t);
  t = token (int(5));
  l.push_back(t);

  expressio e(l);

  e.simplify();

  l.clear();
  t = token (token::OBRIR_PAR);
  l.push_back(t);
  t = token (int(6));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);
  t = token (token::MULTIPLICACIO);
  l.push_back(t);
  t = token (int(8));
  l.push_back(t);
  t = token (token::MULTIPLICACIO);
  l.push_back(t);
  t = token (token::OBRIR_PAR);
  l.push_back(t);
  t = token (int(7));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);

  e = expressio(l);

  e.simplify();

  t = token(token::OBRIR_PAR);
  l.clear();
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);

  e = expressio(l);

  e.simplify();*/

  list<token> l;



  /*token y (token::CANVI_DE_SIGNE);
  l.push_back(y);
  y = token (token::EXPONENCIACIO);
  l.push_back(y);
  y = token (token::SQRT);
  l.push_back(y);
  y = token (int(3));
  l.push_back(y);
  expressio x (l);

  l.clear();
  token t (string("HOLA"));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (string("CAMERA"));
  l.push_back(t);


  expressio e(l);
  list<string> llista;
  e.vars(llista);

  cout << "IMPRIMIM LLISTA"<<endl;
  imprimeix_llista_var(llista);

  // SUBSTITUCIONS
  string s = "HOLA";


  e.apply_substitution(s,x);*/

  token t (token::OBRIR_PAR);
  l.push_back(t);
  t = token (string ("v"));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (token::OBRIR_PAR);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);
  t = token (token::SUMA);
  l.push_back(t);
  t = token (string("v"));
  l.push_back(t);
  t = token (token::TANCAR_PAR);
  l.push_back(t);


  expressio e (l);

  l.clear();
  t = token (int(8));
  l.push_back(t);
  t = token (token::MULTIPLICACIO);
  l.push_back(t);
  t = token (int(5));
  l.push_back(t);

  expressio k (l);

  //expressio k (l);

  string j = "v";
  e.apply_substitution(j,k);








}
