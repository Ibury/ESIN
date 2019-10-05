

#ifndef _EXPRESSIO_HPP
#define _EXPRESSIO_HPP
#include <list>
#include <stack>
#include <string>
#include <esin/error>
#include <esin/util>   
#include "token.hpp"
#include "racional.hpp"

using std::list;
using std::string;

class expressio {
public:

  expressio(const token t = token()) throw(error);

  expressio(const list<token> & l) throw(error);

  expressio(const expressio & e) throw(error);
  expressio & operator=(const expressio & e) throw(error);
  ~expressio() throw(error);

  operator bool() const throw();

  bool operator==(const expressio & e) const throw();
  bool operator!=(const expressio & e) const throw();

  void vars(list<string> & l) const throw(error);

  void apply_substitution(const string & v, const expressio & e) throw(error);

  void simplify_one_step() throw(error);

  void simplify() throw(error);

  void list_of_tokens(list<token> & lt) throw(error);

  static const int ErrorSintactic   = 31;
  static const int NegatElevNoEnter = 32;
  static const int DivPerZero       = 33;
  static const int LogDeNoPositiu   = 34;
  static const int SqrtDeNegatiu    = 35;

private:
  #include "expressio.rep"
};
#endif
