#include "token.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "sstream"
using namespace std;

token::token() 
/*Pre: Cert.*/
/*Post: Crea un token enter de valor 0.*/
{
    tn = "0";
}


token::token(int i) 
    /*Pre: El paràmetre ha de ser un enter */
    /*Post: Crea un objecte token a partir d'un enter.*/
{
    stringstream convert;
    convert << i;
    tn = convert.str();
}


token::token(bool b)
/*Pre: El paràmetre ha de ser un booleà*/
/*Post: Crea un objecte token a partir*/
{
    if (b) tn = "T";
    else tn = "F";
}


token::token(string s)
/*Pre: El paràmetre ha de ser un string.*/
/*Post: Crea un objecte token a partir d'un string.*/
{
    tn = s;
}


bool token::es_operador_unari() const 
/*Pre: Cert.*/
/*Post: Retorna un booleà si i només si p.i és unari.*/
{
    bool ho_es = false;
    if (tn=="not" or tn=="!") ho_es=true;
    return ho_es;
}


bool token::es_operador_binari() const 
/*Pre: Cert.*/
/*Post: Retorna un booleà si i només si p.i és binari.*/
{
    bool es_op_bin=false;
    if ((tn=="and" or tn=="or" or tn=="==" or tn=="!=" or tn=="/" or tn=="**" or tn=="-" or tn=="*" or tn=="+" or tn=="^")) es_op_bin = true;
    return es_op_bin;
}


bool token::es_operador_commutatiu() const
/*Pre: Cert.*/
/*Post: Retorna un booleà si i només si p.i és commutatiu.*/
{   
    bool ho_es = false;
    if (tn=="+" or tn=="*" or tn=="==" or tn=="!=" or tn=="and" or tn=="or") ho_es = true;
    return ho_es;
}


bool token::es_boolea() const
/*Pre: p.i = "T" or "F" */
/*Post: TRUE si p.i == "T" sino FALSE*/
{    
    bool es_bool = false;
    if (tn=="T" or tn=="F") es_bool=true;
    return es_bool;
}


bool token::es_enter() const
/*Pre: Cert*/
/*Post: Retorna TRUE si el p.i és una constant entera i FALS si no ho és.*/
{
    bool es_enter=false;
    string s = to_string();
    if ((tn[0]>='0' and tn[0]<='9') or (tn[0]=='-' and s.size()>1)) es_enter=true;
    return es_enter;
}


bool token::es_variable() const
/*Pre: Cert*/
/*Post: Retorna TRUE si el p.i és una variable.*/
{
    bool es_var=false;
    if (not es_enter() and not es_boolea() and not es_operador_commutatiu() and not es_operador_binari() and not es_operador_unari()) es_var=true;
    return es_var;
}


int token::to_int() const
/*Pre: Cert.*/
/*Post: p.i castejat a enter.*/
{
    string s = tn;
    int n = std::atoi(s.c_str());
    return n;
}


bool token::to_bool() const
/*Pre: p.i == "T" o p.i == "F"*/
/*Post: TRUE si p.i == "T" sino si p.i == "F", FALSE .*/
{  
    bool res;
    if (tn == "T") res = true;
    else if (tn == "F") res = false;
    return res;
}


string token::to_string() const
/*Pre: Cert.*/
/*Post: p.i. en string*/
{    
    return tn;
}


bool token::operator==(const token &t) const
/*Pre: El paràmetre ha de ser un token.*/
/*Post: TRUE si el token del p.i i el paràmetre són iguals.*/
{
    return t.tn == this->tn;
}


bool token::operator!=(const token &t) const
/*Pre: El paràmetre ha de ser un token.*/
/*Post: TRUE si el token del p.i i el paràmetre són diferents.*/
{
    return t.tn != this->tn;
}


bool token::operator==(const char s[]) const
/*Pre: El paràmetre ha de ser un string o dit d'una altre manera, un vector de char */
/*Post: TRUE si el vector de char és igual al string del p.i */
{
    return s == this->tn;
}


bool token::operator!=(const char s[]) const
/*Pre: El paràmetre ha de ser un string o dit d'una altre manera, un vector de char */
/*Post: TRUE si el vector de char és diferent al string del p.i*/
{
    return s != this->tn;
}


istream& operator>>(istream& is, token &t)
/*Pre: Cert.*/
/*Post: Llegex del canal d'entrada el contingut del token.*/
{
    is >> t.tn;
    return is;
}


ostream& operator<<(ostream& os, const token &t)
/*Pre: Cert.*/
/*Post: Mostra al canal de sortida el contingut del token.*/
{    
    os<<t.tn;
    return os;
}