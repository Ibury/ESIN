#include "racional.hpp"
#include <esin/error>
#include <esin/util>
#include <iostream>
using namespace std;

 racional::racional(int n, int d) throw(error){
 	if (d==0) throw error (DenominadorZero);

  if (d<0){
    d = -d;
    n = -n;
  } 

 	
  this->n = n;
  this->d = d;

  get_simplified();

  if (this->n!=0 or this->d!=1) mostra_res();

 }

racional::racional(const racional & r) throw(error){
  n = r.n;
  d = r.d;

}
racional & racional::operator=(const racional & r) throw(error){
  n = r.n;
  d = r.d;
  return *this;

}
racional::~racional() throw(){

}

int racional::num() const throw(){
  return n;

}
int racional::denom() const throw(){
  return d;

}
int racional::part_entera() const throw(){
  return n/d;

}
racional racional::residu() const throw(){
  racional r;
  r.n = n % d;
  r.d = d;
  return r;
}

racional racional::operator+(const racional & r) const throw(error){
	// Fem copies de cada un

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
  //racional raux(r);

  
  racional fi (this->n * r.n, this->d * r.d);
  fi.get_simplified();
  fi.mostra_res();


  return fi;

}


racional racional::operator/(const racional & r) const throw(error){

  racional fi (this->n * r.d, this->d * r.n);
  fi.get_simplified();
  fi.mostra_res();

  return fi;
}



bool racional::operator==(const racional & r) const throw(){
  //racional c_r (r);
  //c_r.get_simplified();
  return (this->n == r.n and this->d == r.d);
}


bool racional::operator!=(const racional & r) const throw(){
  return not racional::operator==(r);
}


bool racional::operator<(const racional & r) const throw(){
  double f1 = (this->n / this->d), f2 = (r.n / r.d);

  return (f1<f2); 
}


bool racional::operator<=(const racional & r) const throw(){
  return (racional::operator<(r) or racional::operator==(r));
}


bool racional::operator>(const racional & r) const throw(){
  return not racional::operator<=(r);
}


bool racional::operator>=(const racional & r) const throw(){
  return (racional::operator>(r) or racional::operator==(r));
}

void racional::get_simplified (){

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
      else ++b;
    }

  }
}

void racional::mostra_res (){
	cout << "---"<<endl;
	cout << "|"<<n<<"|"<<endl;
	cout << "---"<<endl;
	cout <<"|"<<d<<"|"<<endl;
	cout << "---"<<endl;
}
/*
int gcd (int a, int b){
  int r,i;
 
  while (b!=0){
    r = a % b;
    a = b;
    b = r;
  }
  return a;

}*/
