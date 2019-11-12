#include <iostream>
#include "expressio.hpp"
using namespace std;



int main(){
  list<token> l;
  token t (string ("v"));
  l.push_back(t);

  expressio e (l);


  expressio p (token(int(8)));
  e.apply_substitution(string("v"),p);

}
