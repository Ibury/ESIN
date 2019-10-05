#ifndef _DICC_HPP_
#define _DICC_HPP_

using std::pair;

template <typename Clau, typename Valor>
class dicc {

public:
    /*Constructora. Crea un diccionari buit.*/
    dicc() throw(error);

    /*Les tres grans.*/
    dicc(const dicc &d) throw(error);

    dicc& operator=(const dicc &d) throw(error);

    ~dicc() throw();

    /*Afegeix el parell <k, v> al diccionari si no hi havia cap
    parell amb la clau k; en cas contrari substitueix el valor
    antic per v.*/
    void insereix(const Clau &k, const Valor &v) throw(error);

    /*Elimina el parell <k, v> si existeix un parell que té com a
    clau k; no fa res en cas contrari.*/
    void elimina(const Clau &k) throw();

    /*Retorna cert si i només si el diccionari conté un parell amb la
    clau donada.*/
    bool existeix(const Clau &k) const throw();

    /*Retorna el valor associat a la clau donada en cas que existeixi
    un parell amb la clau k; llança una excepció si la clau no
    existeix.*/
    Valor consulta(const Clau &k) const throw(error);

    list<Clau> consulta_claus() const throw(error); //NUEVOOOOOO
private:
  list<pair<Clau, Valor> > lcv;
};

#include "diccionari.cpp"
#endif
