
#ifndef _MATH_SESSIO_HPP
#define _MATH_SESSIO_HPP
#include <list>
#include <esin/error>
#include <esin/util>
#include "token.hpp"  
#include "expressio.hpp"  
#include "variables.hpp"
#include "math_io.hpp"

using std::list;

class math_sessio {
public:

  math_sessio() throw(error);

  math_sessio(const math_sessio & es) throw(error);
  math_sessio & operator=(const math_sessio & es) throw(error);
  ~math_sessio() throw(error);

  void execute(const list<token> & lin, list<token> & lout) throw(error);

  bool end_of_session() const throw();

  void dump(list<string> & l) const throw(error);

  void apply_all_substitutions(expressio & e) const throw(error);

  static const int SintComandaIncorrecta  = 51;
  static const int AssigAmbCirculInfinita = 52;

private:
  #include "math_sessio.rep"
};
#endif
