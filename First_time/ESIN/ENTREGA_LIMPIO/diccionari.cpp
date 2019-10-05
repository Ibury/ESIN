
/*Les tres grans.*/
template <typename Clau, typename Valor>
dicc<Clau,Valor>::dicc() throw(error)
{

}

template <typename Clau, typename Valor>
dicc<Clau,Valor>::dicc(const dicc &d) throw(error)
{
  lcv = d.lcv;
}

template <typename Clau, typename Valor>
dicc<Clau,Valor>& dicc<Clau,Valor>::operator=(const dicc &d) throw(error)
{
  dicc di(d);

  di.lcv = lcv;
  lcv = d.lcv;

  return *this;
}

template <typename Clau, typename Valor>
dicc<Clau,Valor>::~dicc() throw()
{

}

/*Afegeix el parell <k, v> al diccionari si no hi havia cap
parell amb la clau k; en cas contrari substitueix el valor
antic per v.*/
template <typename Clau, typename Valor>
void dicc<Clau,Valor>::insereix(const Clau &k, const Valor &v) throw(error)
{
  pair<Clau, Valor> cv = make_pair(k,v);
  typename list<pair<Clau,Valor> >::iterator itp = lcv.begin();
  bool trobat = false;

  while (itp != lcv.end() and not trobat) {
    if ((*itp).first == k) trobat = true;
    else ++itp;
  }
  if (trobat) (*itp).second = cv.second;
  else lcv.insert(lcv.end(),cv);
}

/*Elimina el parell <k, v> si existeix un parell que té com a
clau k; no fa res en cas contrari.*/
template <typename Clau, typename Valor>
void dicc<Clau,Valor>::elimina(const Clau &k) throw()
{
  typename list<pair<Clau,Valor> >::iterator itp = lcv.begin();
  bool trobat = false;

  while (itp != lcv.end() and not trobat) {
    if ((*itp).first == k) {
      trobat = true;
      lcv.erase(itp);
    } else {
      ++itp;
    }
  }
}

/*Retorna cert si i només si el diccionari conté un parell amb la
clau donada.*/
template <typename Clau, typename Valor>
bool dicc<Clau,Valor>::existeix(const Clau &k) const throw()
{
  typename list<pair<Clau,Valor> >::iterator itp = lcv.begin();
  bool trobat = false;

  while (itp != lcv.end() and not trobat) {
    if ((*itp).first == k) trobat = true;
    else ++itp;
  }

  return trobat;
}

/*Retorna el valor associat a la clau donada en cas que existeixi
un parell amb la clau k; llança una excepció si la clau no
existeix.*/
template <typename Clau, typename Valor>
Valor dicc<Clau,Valor>::consulta(const Clau &k) const throw(error)
{
  typename list<pair<Clau,Valor> >::const_iterator itp = lcv.begin();
  bool trobat = false;

  while (itp != lcv.end() and not trobat) {
    if ((*itp).first == k) trobat = true;
    else ++itp;
  }

  Valor val = expressio(token(token::NULLTOK));
  if (trobat) val = (*itp).second;

  return val;
}

/*Retorna totes les claus que existeixen al diccionari.*/
template <typename Clau, typename Valor>
list<Clau> dicc<Clau,Valor>::consulta_claus() const throw(error)
{
  list<Clau> claus;

  typename list<pair<Clau,Valor> >::const_iterator itp = lcv.begin();

  while (itp != lcv.end()) {
    claus.insert(claus.end(), (*itp).first);
    ++itp;
  }

  return claus;
}
