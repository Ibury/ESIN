
#ifndef _RACIONAL_HPP
#define _RACIONAL_HPP
#include <esin/error>
#include <esin/util>

using std::string;

class racional {
public:

  explicit racional(int n=0, int d=1) throw(error);

  racional(const racional & r) throw(error);
  racional & operator=(const racional & r) throw(error);
  ~racional() throw();

  int num() const throw();
  int denom() const throw();
  int part_entera() const throw();
  racional residu() const throw();

  racional operator+(const racional & r) const throw(error);
  racional operator-(const racional & r) const throw(error);
  racional operator*(const racional & r) const throw(error);
  racional operator/(const racional & r) const throw(error);

  bool operator==(const racional & r) const throw();
  bool operator!=(const racional & r) const throw();
  bool operator<(const racional & r) const throw();
  bool operator<=(const racional & r) const throw();
  bool operator>(const racional & r) const throw();
  bool operator>=(const racional & r) const throw();

  static const int DenominadorZero = 21;

private:
  #include "racional.rep"
};
#endif
