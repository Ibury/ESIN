
#ifndef _MATH_IO_HPP
#define _MATH_IO_HPP
#include <list>
#include <string>
#include <esin/error>
#include <esin/util>
#include "token.hpp"  

using std::list;
using std::string;

namespace math_io {

  void scan(const string & s, list<token> & lt) throw(error);

  string tostring(const list<token> & lt);

  const int ErrorLexic = 61;
};
#endif
