#include <iostream>
using namespace std;

class token {
    private:

        string tn;
    
    public:
   
   // CONSTRUCTORS
    
    token();
    /*Pre: Cert.*/
    /*Post: Crea un token enter de valor 0.*/
    
    token(int i);
    /*Pre: El paràmetre ha de ser un enter */
    /*Post: Crea un objecte token a partir d'un enter.*/
    
    token(bool b);
    /*Pre: Cert*/
    /*Post: Crea un objecte token a partir d'un booleà.*/
   
    token(string s);
    /*Pre: El paràmetre ha de ser un string.*/
    /*Post: Crea un objecte token a partir d'un string.*/
    
    
    // CONSULTORS
    
    
    bool es_operador_unari() const;
    /*Pre: Cert.*/
    /*Post: Retorna un booleà si i només si p.i és unari.*/
    
    bool es_operador_binari() const;
    /*Pre: Cert.*/
    /*Post: Retorna un booleà si i només si p.i és binari.*/
   
    bool es_operador_commutatiu() const;
   /*Pre: Cert.*/
    /*Post: Retorna un booleà si i només si p.i és commutatiu.*/
   
    bool es_boolea() const;
    /*Pre: p.i = "T" or "F" */
    /*Post: TRUE si p.i == "T" sino FALSE*/

    bool es_enter() const;
    /*Pre: Cert*/
    /*Post: Retorna TRUE si el p.i és una constant entera i FALS si no ho és.*/
   
    bool es_variable() const;
    /*Pre: Cert*/
    /*Post: Retorna TRUE si el p.i és una variable.*/
   
    int to_int() const;
    /*Pre: Cert.*/
    /*Post: p.i castejat a enter.*/
  
    bool to_bool() const;
    /*Pre: p.i == "T" o p.i == "F"*/
    /*Post: TRUE si p.i == "T" sino si p.i == "F", FALSE .*/
   
    string to_string() const;
    /*Pre: Cert.*/
    /*Post: p.i. en string*/
    
    
    
    // MÈTODES D'OPERANTS PER A L'OBJECTE
    
    bool operator==(const token &t) const;          
    /*Pre: El paràmetre ha de ser un token.*/
    /*Post: TRUE si el token del p.i i el paràmetre són iguals.*/
    
    bool operator!=(const token &t) const;
    /*Pre: El paràmetre ha de ser un token.*/
    /*Post: TRUE si el token del p.i i el paràmetre són diferents.*/
    
    bool operator==(const char s[]) const;
    /*Pre: El paràmetre ha de ser un string o dit d'una altre manera, un vector de char */
    /*Post: TRUE si el vector de char és igual al string del p.i */
   
    bool operator!=(const char s[]) const;
    /*Pre: El paràmetre ha de ser un string o dit d'una altre manera, un vector de char */
    /*Post: TRUE si el vector de char és diferent al string del p.i*/
    
    
    //Lectura i escriptura (CANAL ESTÀNDAR)
  
    friend istream& operator>>(istream& is, token &t);
    /*Pre: Cert.*/
    /*Post: Llegex del canal d'entrada el contingut del token.*/
    
    friend ostream& operator<<(ostream& os, const token &t);
    /*Pre: Cert.*/
    /*Post: Mostra al canal de sortida el contingut del token.*/
    
    
    
    
};