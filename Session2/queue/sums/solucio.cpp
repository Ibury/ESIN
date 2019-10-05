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

queue::queue() : _queue(NULL) {   
}

queue::queue(const queue &c) : _queue(NULL) {
  if (c._queue != NULL) {
    _queue = new node;
    try {
      _queue->info = c._queue->info;
      _queue->seg = copiar(c._queue->seg, c._queue, _queue);
    }
    catch (...) {
      delete(_queue);
      throw;
    }
  }
}

queue::node* queue::copiar(node* n, node* fi, node* ini) {
  node* aux;
  if (n != fi) {
    aux = new node;
    try {
      aux->info = n->info;
      aux->seg = copiar(n->seg, fi, ini); 
    }
    catch (...) {
      delete aux;
      throw;
    }
  }
  else {
    aux = ini;
  }
  return aux;
}

queue& queue::operator=(const queue &q) {
  if (this != &q) {
    queue qaux(q);
    node* naux = _queue;
    _queue = qaux._queue;
    qaux._queue = naux;
  }
  return *this;
}

queue::~queue() throw() {
  if (_queue != NULL) {
    node* fi = _queue;
    _queue = _queue->seg;
    while (_queue != fi) {
      node* aux = _queue;
      _queue = _queue->seg;
      delete aux;
    }
    delete(_queue);
  }
}

void queue::push(const int &x) {
  node* p = new(node); 
  try {
    p->info = x;
  }
  catch (...) {
    delete p;
    throw;
  }
  if (_queue == NULL) {
    p->seg = p;  // cua amb un únic element que s’apunta 
  }              // a sí mateix
  else {
    p->seg = _queue->seg;
    _queue->seg = p;
  }
  _queue = p;
}

void queue::pop() { 
  if (_queue==NULL) {
    throw CuaBuida;
  }
  node* p = _queue->seg;
  if (p == _queue) {
    _queue = NULL; // desencuem una cua que tenia un únic 
  }              // element
  else {  
    _queue->seg = p->seg;
  }
  delete(p);
}

const int& queue::first() const
{
  if (_queue==NULL) { 
    throw CuaBuida;
  }
  return (_queue->seg->info);
}

bool queue::empty() const throw() {  
  return (_queue==NULL);
}

#include <iostream>
#include <sstream>

using namespace std;

/*
int reverseQueue(queue *q)
//PRE: Cua
//POST: Suma total de tots elements més inversió de la cua.
{
    int sum = 0;

    if (not q->empty())
    {

        int val = q->first();

        q->pop();

        sum += reverseQueue(q) + val;

        q->push(val);
    }

    return sum;
}

void remove_older_previous_sum(queue *q, queue *out)
//PRE: Cua
//POST: Nova cua amb els elements menors a la suma dels X anterios elements.
{
    int total = reverseQueue(q);

    while (not q->empty())
    {
        int val = q->first();
        q->pop();

        total -= val;

        if (val <= total)
            out->push(val);
    }
}
*/

void remove_older_previous_sum(queue *q, queue *out)
//PRE: Cua
//POST: Nova cua amb els elements menors a la suma dels X anterios elements.
{
    int total = 0;

    while (not q->empty())
    {
        int val = q->first();
        q->pop();

        if (val <= total)
            out->push(val);

        total += val;
    }
}

void printQueue(queue q)
{
    while (not q.empty())
    {
        cout << q.first();

        q.pop();

        if (not q.empty())
            cout << " ";
    }

    cout << endl;
}

int main()
{
    string line;
    int x;

    while (getline(cin, line))
    {
        istringstream ss(line);

        queue *q = new queue;

        while (ss >> x)
        {
            q->push(x);
        }

        queue *modified = new queue;

        remove_older_previous_sum(q, modified);

        printQueue(*modified);
    }
}