

#ifndef _TOKEN_HPP
#define _TOKEN_HPP
#include <string>
#include <esin/error>
#include <esin/util>
#include "racional.hpp"

class token {
public:

  enum codi {NULLTOK,
             CT_ENTERA, CT_RACIONAL, CT_REAL, CT_E,
             VARIABLE, VAR_PORCENTATGE,
             SUMA, RESTA, MULTIPLICACIO, DIVISIO, EXPONENCIACIO,
             CANVI_DE_SIGNE, SIGNE_POSITIU,
             SQRT, EXP, LOG, EVALF,
             OBRIR_PAR, TANCAR_PAR, COMA,
             ASSIGNACIO, DESASSIGNACIO, BYEBYE};

  explicit token(codi cod = NULLTOK) throw(error);
  explicit token(int n) throw(error);
  explicit token(const racional & r) throw(error);
  explicit token(double x) throw(error);
  explicit token(const string & var_name) throw(error);

  token(const token & t) throw(error);
  token & operator=(const token & t) throw(error);
  ~token() throw();

  codi tipus() const throw();
  int valor_enter() const throw(error);
  racional valor_racional() const throw(error);
  double valor_real() const throw(error);
  string identificador_variable() const throw(error);

  bool operator==(const token & t) const throw();
  bool operator!=(const token & t) const throw();

  bool operator>(const token & t) const throw(error);
  bool operator<(const token & t) const throw(error);

  static const int IdentificadorIncorrecte      = 11;
  static const int ConstructoraInadequada       = 12;
  static const int ConsultoraInadequada         = 13;
  static const int PrecedenciaEntreNoOperadors  = 14;

private:
  #include "token.rep"
};
#endif
