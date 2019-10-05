#ifndef _QUEUE_HPP
#define _QUEUE_HPP
#include <cstddef>
#include <string>
using namespace std;

class queue
{
private:
  struct node
  {
    string info;
    node *seg;
  };
  node *_queue;

  node *copiar(node *n, node *fi, node *ini);

public:
  // Construeix una cua buida.
  queue();

  // Tres grans: constructora per còpia, operador d'assignació i destructora.
  queue(const queue &q);
  queue &operator=(const queue &q);
  ~queue() throw();

  // Afegeix un element al final de la cua.
  void push(const string &x);

  // Treu el primer element de la cua. Llança un error si la cua és buida.
  void pop();

  // Obté el primer element de la cua. Llança un error si la cua és buida.
  const string &first() const;

  // Consulta si la cua és buida o no.
  bool empty() const throw();

  static const int CuaBuida = 310;
};
#endif

queue::queue() : _queue(NULL)
{
}

queue::queue(const queue &c) : _queue(NULL)
{
  if (c._queue != NULL)
  {
    _queue = new node;
    try
    {
      _queue->info = c._queue->info;
      _queue->seg = copiar(c._queue->seg, c._queue, _queue);
    }
    catch (...)
    {
      delete (_queue);
      throw;
    }
  }
}

queue::node *queue::copiar(node *n, node *fi, node *ini)
{
  node *aux;
  if (n != fi)
  {
    aux = new node;
    try
    {
      aux->info = n->info;
      aux->seg = copiar(n->seg, fi, ini);
    }
    catch (...)
    {
      delete aux;
      throw;
    }
  }
  else
  {
    aux = ini;
  }
  return aux;
}

queue &queue::operator=(const queue &q)
{
  if (this != &q)
  {
    queue qaux(q);
    node *naux = _queue;
    _queue = qaux._queue;
    qaux._queue = naux;
  }
  return *this;
}

queue::~queue() throw()
{
  if (_queue != NULL)
  {
    node *fi = _queue;
    _queue = _queue->seg;
    while (_queue != fi)
    {
      node *aux = _queue;
      _queue = _queue->seg;
      delete aux;
    }
    delete (_queue);
  }
}

void queue::push(const string &x)
{
  node *p = new (node);
  try
  {
    p->info = x;
  }
  catch (...)
  {
    delete p;
    throw;
  }
  if (_queue == NULL)
  {
    p->seg = p; // cua amb un únic element que s’apunta
  }             // a sí mateix
  else
  {
    p->seg = _queue->seg;
    _queue->seg = p;
  }
  _queue = p;
}

void queue::pop()
{
  if (_queue == NULL)
  {
    throw CuaBuida;
  }
  node *p = _queue->seg;
  if (p == _queue)
  {
    _queue = NULL; // desencuem una cua que tenia un únic
  }                // element
  else
  {
    _queue->seg = p->seg;
  }
  delete (p);
}

const string &queue::first() const
{
  if (_queue == NULL)
  {
    throw CuaBuida;
  }
  return (_queue->seg->info);
}

bool queue::empty() const throw()
{
  return (_queue == NULL);
}

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
  string line;
  int n;
  unsigned int i = 0;
  vector<queue> v;

  cin >> n;

  if (n > 0)
  {
    vector<queue> v(n);
    cin.ignore();

    while (getline(cin, line) and i < n)
    {
      istringstream ss(line);

      string x;

      while (ss >> x)
      {
        v[i].push(x);
      }
      ++i;
    }

    cout << "SORTIDES" << endl
         << "--------" << endl;

    while (getline(cin, line))
    {
      istringstream ss(line);

      string x;

      while (ss >> x)
      {
        if (x == "ENTRA")
        {
          string nombre;
          int num;
          ss >> nombre;
          ss >> num;

          if (num > 0 and num <= n)
          {
            v[num - 1].push(nombre);
          }
        }
        else if (x == "SURT")
        {
          int num;
          ss >> num;

          if (num > 0 and num <= n)
          {
            if (not v[num - 1].empty())
            {
              cout << v[num - 1].first() << endl;
              v[num - 1].pop();
            }
          }
        }
      }
    }

    cout << endl
         << "CONTINGUTS FINALS" << endl
         << "-----------------" << endl;

    for (int i = 0; i < n; ++i)
    {
      cout << "cua " << (i + 1) << ":";
      if (not v[i].empty())
        cout << " ";

      while (not v[i].empty())
      {
        cout << v[i].first();
        v[i].pop();
        if (not v[i].empty())
          cout << " ";
      }
      cout << endl;
    }
  }
}