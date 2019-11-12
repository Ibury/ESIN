//ARBBIN
template <typename Elem>
arbbin<Elem>::arbbin() throw(error) 
//COST: Θ(1)
//PRE: Cert
//POST: Nou arbbin<Elem> sense nodes.
{
	pare=NULL;
	mida=0;
}

template <typename Elem>
arbbin<Elem>::arbbin(const arbbin& a) throw(error)
//COST: Θ(1)
//PRE: arbbin<Elem>
//POST:	El p.i será una copia exactament igual a l'arbre de l'argument a.
{
	pare = copia_arbre(a.pare);
	mida = a.mida;
}

template <typename Elem>
arbbin<Elem>::arbbin(const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error)
//COST: Θ(2^n)
//PRE: Elem, fesq i fdret.
//POST: Crea un nou node i l'afegeix com arrel. Li asigna recursivament l'arbre fill esquerre i fill dret.
{
	pare = new node;
	try{
		pare->fe = copia_arbre(fesq.pare);
		pare->fd = copia_arbre(fdret.pare);
		pare->info = x;

		mida = fesq.mida + fdret.mida + 1;
	}catch(error) {
		if (pare->fe!=NULL) esborra_arbre(pare->fe); 
		if (pare->fd!=NULL) esborra_arbre(pare->fd);
		delete pare;
		throw;
	}
}

template <typename Elem>
arbbin<Elem>& arbbin<Elem>::operator=(const arbbin& a) throw(error)
//COST: Θ(2^n)
//PRE: arbbin<Elem>
//POST:	L'arbre del p.i passa a ser com el que li passen pel argument a.
{
	arbbin<Elem> b (a);
	node* ptr = b.pare;

	b.pare = pare;
	pare = ptr;

	mida = b.mida;

	return *this;
}

template <typename Elem>
arbbin<Elem>::~arbbin() throw()
//COST: Θ(2^n)
//PRE: Cert
//POST: Destrueix l'arbre del p.i
{
	esborra_arbre(pare);
}

template <typename Elem>
void arbbin<Elem>::esborra_arbre(node* ptr) throw()
//COST: Θ(2^n)
//PRE: Node a esborrar. En la primera crida a la funció, ptr és el primer node (l'arrel de l'arbre).
//POST: Esborra recursivament desde el fons de l'arbre fins al primer.
{
	if (ptr != NULL) {
		esborra_arbre(ptr->fe);
		esborra_arbre(ptr->fd);
		delete ptr;
	}
}

template <typename Elem>
typename arbbin<Elem>::node* arbbin<Elem>::copia_arbre(const node* ptr) throw()
//COST: Θ(2^n)
//PRE: Node a copiar. En la primera crida a la funció, ptr és el primer node (l'arrel de l'arbre).
//POST: Copia l'arbre desde el fons fins l'arrel.
{
	node* ptra=NULL;

	if (ptr != NULL) {

		ptra = new node;
		try {
			ptra->fe = copia_arbre(ptr->fe);
			ptra->fd = copia_arbre(ptr->fd);
			ptra->info = ptr->info;
			++mida;
		}catch(error) {
			if (pare->fe!=NULL) esborra_arbre(pare->fe); 
			if (pare->fd!=NULL) esborra_arbre(pare->fd);
			delete ptra;
			throw;
		}
	}

	return ptra;
}

template <typename Elem>
nat arbbin<Elem>::size() const throw()
//COST: Θ(1)
//PRE: Cert
//POST: Nodes que conté l'arbre
{
	return mida;
}

template <typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::arrel() const throw()
//COST: Θ(1)
//PRE: Cert
//POST: Iterador que apunta al primer node de l'arbre (arrel)
{
	iterador it;
	if (!this) throw error(arbbin<Elem>::iterador::IteradorNul);
	it.pit = pare;
	return it; 
}


//ITERADOR
template <typename Elem>
arbbin<Elem>::iterador::iterador() throw(error)
//COST: Θ(1)
//PRE: Cert
//POST: NULL
{
	pit = NULL;
}


template <typename Elem>
arbbin<Elem>::iterador::~iterador() throw()
//COST: Θ(1)
//PRE: Cert
//POST: NULL
{
	pit = NULL;
}

template <typename Elem>
arbbin<Elem>::iterador::iterador(const iterador& it) throw(error)
//COST: Θ(1)
//PRE: Iterador d'un arbbin<Elem>
//POST: Constructor per copia. El p.i apunta a l'argument it.
{
	pit = it.pit;
}

template <typename Elem>
typename arbbin<Elem>::iterador& arbbin<Elem>::iterador::operator=(const iterador& it) throw(error)
//COST: Θ(1)
//PRE: Iterador d'un arbbin<Elem>
//POST: El p.i apunta al mateix lloc que l'argument.
{
	pit = it.pit;
	return *this;
}

template <typename Elem>
Elem arbbin<Elem>::iterador::operator*() const throw(error)
//COST: Θ(1)
//PRE: Cert
//POST: Desparametritza l'iterador. Obtenim el camp info del node actual.
{
	if (pit == NULL) throw error(IteradorNul);
	return pit->info;
}

template <typename Elem>         
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_esq() const throw(error)
//COST: Θ(1)
//PRE: Cert
//POST: L'iterador passa a apuntar al fill esquerra del node actual en cas de tindre. En altre cas informa amb un error.
{
	iterador it;
	if (pit==NULL) throw error(IteradorNul);
	it.pit = pit->fe;
	return it; 
}

template <typename Elem>         
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_dret() const throw(error)
//COST: Θ(1)
//PRE: Cert
//POST: L'iterador passa a apuntar al fill dret del node actual en cas de tindre. En altre cas informa amb un error.
{
	iterador it;
	if (pit==NULL) throw error(IteradorNul);
	it.pit = pit->fd;
	return it; 
}

template <typename Elem>         
arbbin<Elem>::iterador::operator bool() const throw()
//COST: Θ(1)
//PRE: Cert
//POST: True si l'iterador no es NULL, False si es NULL.
{
	return (pit!=NULL);
}