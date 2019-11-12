#include "racional.hpp"
#include <esin/error>
#include <esin/util>
#include <iostream>
using namespace std;

 racional::racional(int n, int d) throw(error){
 	//Pre:Cert
 	//Post: Hi ha un p.i = r:Racional
 	if (d==0) throw error (DenominadorZero);

  if (d<0){
    d = -d;
    n = -n;
  }


  this->n = n;
  this->d = d;

  get_simplified();

 }

racional::racional(const racional & r) throw(error){
	//Pre:Cert
 	//Post: Hi ha un nou r:Racional que es igual a r.

  n = r.n;
  d = r.d;

}
racional & racional::operator=(const racional & r) throw(error){
	//Pre:Cert
 	//Post: Hi ha un nou r:Racional que es igual a r.
  n = r.n;
  d = r.d;
  return *this;

}
racional::~racional() throw(){

}

int racional::num() const throw(){
	//Pre:Cert
 	//Post: Retorna el numerador del racional
  return n;

}
int racional::denom() const throw(){
	//Pre:Cert
 	//Post: Retorna el denominador del racional
  return d;

}
int racional::part_entera() const throw(){
	//Pre:Cert
 	//Post: Retorna la part enetera del racional

   return n/d;

}
racional racional::residu() const throw(){
	//Pre:Cert
 	//Post: Retorna el residu del racional
  racional r;
  r.n = n % d;
  if (d<0) r.d = -d;
  else r.d = d;
  return r;
}

racional racional::operator+(const racional & r) const throw(error){	
	//Pre:Cert
 	//Post: Retorna un racional que ve de sumar el p.i i r
	
  racional nou;


   if (this->d == r.d){
    nou.d = d;
    nou.n = this->n + r.n;
  }

  else {
    int den = this->d * r.d;

    nou.n = ((den / this->d)* this->n) + ((den / r.d)* r.n);
    nou.d = den;

    nou.get_simplified();


  }
  nou.mostra_res();

  return nou;

}

racional racional::operator-(const racional & r) const throw(error){

	//Pre:Cert
 	//Post: Retorna un racional que ve de restar el p.i i r

  racional nou;


   if (this->d == r.d){
    nou.d = d;
    nou.n = this->n + r.n;
  }

  else {
    int den = this->d * r.d;

    nou.n = ((den / this->d)* this->n) - ((den / r.d)* r.n);
    nou.d = den;

    nou.get_simplified();
    nou.mostra_res();

  }

  return nou;
}


racional racional::operator*(const racional & r) const throw(error){
	//Pre:Cert
 	//Post: Retorna un racional que ve de multiplicar el p.i i r
  //racional raux(r);


  racional fi (this->n * r.n, this->d * r.d);
  fi.get_simplified();
  fi.mostra_res();


  return fi;

}


racional racional::operator/(const racional & r) const throw(error){
	//Pre:Cert
 	//Post: Retorna un racional que ve de dividir el p.i i r

  racional fi (this->n * r.d, this->d * r.n);
  fi.get_simplified();
  fi.mostra_res();

  return fi;
}



bool racional::operator==(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és igual a r


  return (this->n == r.n and this->d == r.d);
}


bool racional::operator!=(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és diferent a r
  return not racional::operator==(r);
}


bool racional::operator<(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és mes petit que  r
  double f1 = (this->n / this->d), f2 = (r.n / r.d);

  return (f1<f2);
}


bool racional::operator<=(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és mes petit o igual que  r
  return (racional::operator<(r) or racional::operator==(r));
}


bool racional::operator>(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és mes gran que  r
  return not racional::operator<=(r);
}


bool racional::operator>=(const racional & r) const throw(){
	//Pre:Cert
 	//Post: Retorna cert si el p.i és mes gran que o igual r
  return (racional::operator>(r) or racional::operator==(r));
}

void racional::get_simplified (){
	//Pre:Cert
 	//Post: Res
  bool e = false;
  if (n<0){
    e = true;
    n = -n;
  }

  if (n % d == 0){
    n = n / d;
    d = 1;
  }

  

  else {
    int b = 2;
    while (b<=n){
      if ((d % b == 0) and (n % b == 0)){
        
        d = d / b;
        n = n / b;
        
      }
      ++b;
    }

  }

  if (e) n = -n;
}
