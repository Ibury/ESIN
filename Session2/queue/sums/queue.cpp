#include "queue.hpp"

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