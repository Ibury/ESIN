#ifndef _QUEUE_HPP
#define _QUEUE_HPP
#include <cstddef>
using namespace std;

class queue {
private: 
  struct node {
    int info;
    node* seg;
  };
  node* _queue;

  node* copiar(node* n, node* fi, node* ini);

public:
  // Construeix una cua buida.
  queue();

  // Tres grans: constructora per còpia, operador d'assignació i destructora.
  queue(const queue &q);
  queue& operator=(const queue &q);
  ~queue() throw();

  // Afegeix un element al final de la cua. 
  void push(const int &x);

  // Treu el primer element de la cua. Llança un error si la cua és buida.
  void pop();

  // Obté el primer element de la cua. Llança un error si la cua és buida.
  const int& first() const;

  // Consulta si la cua és buida o no.
  bool empty() const throw();

  static const int CuaBuida = 310;
};
#endif
