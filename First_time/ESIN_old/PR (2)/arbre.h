#ifndef ARBRE_H 
#define ARBRE_H

#include <string>
#include <cstdlib>
#include <iostream>


/// -----------------------------------------
///
///  Declaració operacions tipus ARBRE BINARI
///
/// -----------------------------------------

template <class T> 
class arbre { 
 
 private:
   T info;
   arbre<T> *dret;
   arbre<T> *esquerre;
   void clone(const arbre<T>&);

 public:
   //constructors
   arbre();
   /* Pre: cert */
   /* Post: el resultat és un arbre sense cap element */
   arbre(const T &,const arbre<T> &,const arbre<T> &);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos 
       subarbres */
   arbre(const T &);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos 
       subarbres buits*/
   arbre(const arbre<T> &);
   /* Pre: cert */
   /* Post: el resultat és una còpia de l'arbre rebut */
    
    
   //destructor: esborra automàticament els objectes locals
   //en sortir d'un àmbit de visibilitat
   ~arbre();
    
    
    //modificadors
    void a_buit();
    /* Pre: cert */
    /* Post: el paràmetre implícit no té cap element */     
    arbre<T>& operator=(const arbre<T>&);  
    /* Pre: cert */
    /* Post: operació d'assignació d'arbres  */ 
       
   //consultors
   const T& arrel() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és l'arrel del paràmetre implícit */
   const arbre<T>& fd() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és el fill dret del p.i. original */
   const arbre<T>& fe() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és el fill esquerre del p.i. original */
   bool es_buit() const;
   /* Pre: cert */
   /* Post: el resultat indica si el p.i. és buit o no */
   bool es_fulla() const;
   /* Pre: cert */
   /* Post: el resultat indica si el p.i. és una fulla (el fill esquerra i dret són buits) */
   
   //Escriptura/Lectura
   
   template <class U> friend std::ostream& operator<<(std::ostream &, const arbre<U> &);   
   
};


/// ------------------------------------------
///
///  Codificació operacions tipus ARBRE BINARI
///
/// ------------------------------------------


//constructors ----------------------
template <class T>
arbre<T>::arbre()
/* Pre: cert */
/* Post: el resultat és un arbre sense cap element */
{
  dret = NULL;
  esquerre = NULL;
}

template <class T>
arbre<T>::arbre(const T& x, const arbre<T>& a1, const arbre<T>& a2)
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, a1 com a fill
esquerre i a2 com a fill dret */
{
  info = x;
  esquerre = new arbre<T>; esquerre->clone(a1);
  dret = new arbre<T>; dret->clone(a2);
}

template <class T>
arbre<T>::arbre(const T &x)
/* Pre: cert */
/* Post: el resultat és un arbre amb un element i dos subarbres buits*/
{
  info = x;
  dret = new arbre<T>;
  esquerre = new arbre<T>;
}

template <class T>
arbre<T>::arbre(const arbre<T>& t)
/* Pre: cert */
/* Post: el resultat és una còpia de t */
{
  clone(t);
}


//destructor ----------------------
template <class T>
arbre<T>::~arbre() {
  if (dret != NULL) dret->~arbre();
  if (esquerre != NULL) esquerre->~arbre();
}



//modificadors ----------------------
template <class T>
void arbre<T>::a_buit()
/* Pre: cert */
/* Post: el paràmetre implícit no té cap element */  
{
  if (dret != NULL) dret = NULL;
  if (esquerre != NULL) esquerre = NULL;
}  

template <class T>
arbre<T>& arbre<T>::operator=(const arbre<T>& t) {
  if (this != &t) {
    clone(t);
  }
  return (*this);
}

//consultors ----------------------
template <class T>
bool arbre<T>::es_buit() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
{
  return (dret==NULL && esquerre==NULL);
}

template <class T>
bool arbre<T>::es_fulla() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. és una fulla (el fill esquerra i dret són buits) */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'es_fulla' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return (dret->es_buit() && esquerre->es_buit());
}

template <class T>
const arbre<T> &  arbre<T>::fd() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill dret del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'fd' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return (*dret);
}

template <class T>
const arbre<T> &  arbre<T>::fe() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill esquerre del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'fe' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return (*esquerre);
}

template <class T>
const T& arbre<T>::arrel() const {
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és l'arrel del paràmetre implícit */
  if (this->es_buit()) {
    std::cout<<"ERROR - Operació 'arrel' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return info;
}

//clone (operació auxiliar privada) ----------------------
template <class T>
void arbre<T>::clone(const arbre<T>& t) {

  if (not t.es_buit()) this->info = t.info;

  if (t.dret!=NULL) {
    this->dret = new arbre<T>;  
    this->dret->clone(*t.dret); 
  }
  else this->dret=NULL;

  if (t.esquerre!=NULL) {
    this->esquerre = new arbre<T>;
    this->esquerre->clone(*t.esquerre);  
  }
  else this->esquerre=NULL;

}

//Escriptura
std::string dep=""; 
template <class U>
std::ostream& operator<<(std::ostream& os , const arbre<U> &x) 
{
  std::string d1=dep;
  if (x.es_buit()) 
    os<<".";
  else {
    os<< "["<<x.arrel()<<"]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    os<< x.fd();
    os<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    os<< x.fe();
  }
  dep=d1;
  return os;
}

#endif
