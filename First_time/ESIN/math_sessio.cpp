#include "math_sessio.hpp"

math_sessio::math_sessio() throw(error)
/*
  PRE:  true
  POST: Crea una nova sessio activa i assigna a la variable tant per cent una expressio buida.
*/
{
  expressio e;
  vars.assign("%",e);
  sessio = true;
}

math_sessio::math_sessio(const math_sessio & es) throw(error)
/*
  PRE:  math_sessio
  POST: Crea una nova sessio igual a la del paràmetre de la funció.
*/
{
  vars = es.vars;
}

math_sessio & math_sessio::operator=(const math_sessio & es) throw(error)
/*
  PRE:  math_sessio
  POST: La sessió del p.i és igual a la del paràmetre de la funció.
*/
{
  math_sessio ma(es);

  ma.vars = vars;
  vars = es.vars;

  return *this;
}

math_sessio::~math_sessio() throw(error)
{

}
void math_sessio::execute(const list<token> & lin, list<token> & lout) throw(error)
/*
  PRE:  llista de tokens i llista buida.
  POST: Omple la llista l amb els tokens de la sessio activa
*/
{
  bool err = false;

  list<token>::const_iterator it = lin.begin();

  if (((*it).tipus() == token::DESASSIGNACIO) and (lin.size() < 2 or it != lin.begin() or (*(++it)).tipus() != token::VARIABLE)) err = true;
  if (((*it).tipus() == token::BYEBYE) and (lin.size() > 1 or it != lin.begin())) err = true;
  if (((*it).tipus() == token::ASSIGNACIO) and (lin.size() < 2 or it == lin.begin() or lin.front().tipus() != token::VARIABLE)) err = true;

  if (err) throw error(SintComandaIncorrecta);

  if ((*it).tipus() == token::EVALF) {
    ++it;
    ++it;
    expressio e(vars.valor((*it).identificador_variable()));
    e.simplify();
    e.list_of_tokens(lout);
  }else if ((*it).tipus() == token::VARIABLE and (*(++it)).tipus() == token::ASSIGNACIO) {
    string v = (*it).identificador_variable();
    ++it;
    ++it;
    expressio e(lin);
    e.simplify();
    vars.assign(v,e);
  }else if ((*it).tipus() == token::DESASSIGNACIO) {
    ++it;
    vars.unassign((*it).identificador_variable());
  }else if ((*it).tipus() == token::BYEBYE) {
     sessio = false;
  }

}
bool math_sessio::end_of_session() const throw()
/*
  PRE:  true
  POST: true si la sessio es activa, false en cas contrari
*/
{
  return sessio;
}
void math_sessio::dump(list<string> & l) const throw(error)
/*
  PRE:  llista buida
  POST: Omple la llista l amb els tokens de la sessio activa
*/
{
  //FALTA LIST_OF_TOKENS EN CLASSE EXPRESSIONS
  /*list<string> c;
  vars.dump(c);

  list<string>::iterator it = c.begin();

  while (it != c.end()) {
    l.push_back((*it)+" = "+math_io::tostring(vars.valor((*it)).list_of_tokens()));
    ++it;
  }*/

}
void math_sessio::apply_all_substitutions(expressio & e) const throw(error)
/*
  PRE:  expressio no buida
  POST: Substitueix a totes les variables de l'expressio e, la expressio que contenen aquestes variables.
*/
{

}
