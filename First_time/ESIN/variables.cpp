#include "variables.hpp"


variables::variables() throw(error)
/*
  PRE:  true
  POST: nou objecte variables
*/
{

}

variables::variables(const variables & v) throw(error)
/*
  PRE:  variable
  POST: nou objecte variable amb mateix contingut que el paràmetre
*/
{
  d = v.d;
}

variables & variables::operator=(const variables & v) throw(error)
/*
  PRE:  variable
  POST: p.i es igual al paràmetre que rep la funció
*/
{
  variables va(v);

  va.d = d;
  d = v.d;

  return *this;
}
variables::~variables() throw(error)
{

}

void variables::assign(const string & v, const expressio & e) throw(error)
/*
  PRE:  variable i la seva expressió
  POST: inserció si no existeix en el diccionari (clau,valor) i si existeix reemplaça el valor.
*/
{
  d.insereix(v,e);
}

void variables::unassign(const string & v) throw()
/*
  PRE:  variable string
  POST: elimina la expressió de la variable v
*/
{
  d.elimina(v);
}

expressio variables::valor(const string & lv) const throw(error)
/*
  PRE:  variable string
  POST: valor de la variable
*/
{
  return d.consulta(lv);
}

void variables::dump(list<string> & l) const throw(error)
/*
  PRE:  llista buid d'strings
  POST: omple la llista amb totes les variables que conté la classe en el diccionari.
*/
{
  l = d.consulta_claus();
}
