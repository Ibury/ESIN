#ifndef _ARBBIN_HPP_
#define _ARBBIN_HPP_

#include <esin/error>
#include <esin/util>

using util::nat;

template <typename Elem>
class arbbin {
private:
	struct node{
		node* f_esq;
		node* f_dret;
		//node* pare -> OPCIONAL
		Elem info;
	};
	node* _arrel;		
  nat cont;

  node* copia_node(const node* origen);
  void destrueix_node(node* origen);


public:

  friend class iterador;

  class iterador {

    friend class arbbin;

  public:
    iterador() throw(error);
         
    iterador(const iterador& it) throw(error);
    iterador& operator=(const iterador& it) throw(error);
    ~iterador() throw();
         
    Elem operator*() const throw(error);
         
    iterador fill_esq() const throw(error);
         
    iterador fill_dret() const throw(error);
         
    operator bool() const throw();
         
    static const int IteradorNul = 11;

  private:
	node* pite; // INSEGUR
  };

arbbin() throw(error);

arbbin(const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error);

arbbin(const arbbin& a) throw(error);
arbbin& operator=(const arbbin& a) throw(error);
~arbbin() throw();

nat size() const throw();

iterador arrel() const throw();
};
#include "arbbin.t"
#endif
