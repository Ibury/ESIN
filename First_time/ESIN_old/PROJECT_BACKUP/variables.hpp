

#ifndef _VARIABLES_HPP
#define _VARIABLES_HPP
#include <list>
#include <string>
#include <esin/error>
#include <esin/util>   
#include "expressio.hpp"

using std::list;
using std::string;

class variables {
public:

  variables() throw(error);

  variables(const variables & v) throw(error);
  variables & operator=(const variables & v) throw(error);
  ~variables() throw(error);

  void assign(const string & v, const expressio & e) throw(error);

  void unassign(const string & v) throw();

  expressio valor(const string & lv) const throw(error);

  void dump(list<string> & l) const throw(error);

private:
  #include "variables.rep"
};
#endif
