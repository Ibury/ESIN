#include <iostream>
#include "variables.hpp"
using namespace std;



int main(){
  variables var;

  list<token> l;
  token t;

  t = token (int(2));
  l.push_back(t);
  t = token (token::MULTIPLICACIO);
  l.push_back(t);
  t = token (int(4));
  l.push_back(t);

  expressio e(l);

  var.assign("var_",e);

  var.valor("var_").simplify();
}
