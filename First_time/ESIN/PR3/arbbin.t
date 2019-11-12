//ARBRES
template <typename Elem>
arbbin<Elem>::arbbin() throw(error) {

	pare=NULL;
	mida=0;
}

template <typename Elem>
arbbin<Elem>::arbbin(const arbbin& a) throw(error)
{
	arrel = copia_arbre(a);
}

arbbin(const Elem& x, const arbbin& fesq, const arbbin& fdret) throw(error) 
{
	node* n = new node;
	n->fe = copia_arbre(fesq);
	n->fd = copia_arbre(fdret);
	n->info = x;

	pare = n;

	mida = 1 + n->fe.mida + n->fd.mida;
}

template <typename Elem>
arbbin<Elem>& arbbin<Elem>::operator=(const arbbin& a) throw(error)
{
	arbbin<Elem> b = arbbin(a);
	node* ptr = b.arrel;

	b.arrel = arrel;
	arrel = ptr;
}

template <typename Elem>
arbbin<Elem>::~arbbin() throw()
{
	esborra_arbre(arrel);
}

template <typename Elem>
void arbbin<Elem>::esborra_arbre(node* ptr) throw() 
{
	esborra_arbre(ptr->fe);
	esborra_arbre(ptr->fd);

	if (ptr != NULL) {
		delete ptr;
	}
}

template <typename Elem>
node* arbbin<Elem>::copia_arbre(node* ptr) throw() 
{
	node* ptra;

	if (ptr->fe != NULL) {
		copia_arbre(ptr->fe);
		ptra->fe = new node;
		ptra->fe->info = ptr->fe->info;
		++mida;
	}

	if (ptr->fd != NULL)  {
		copia_arbre(ptr->fd);
		ptra->fd = new node;
		ptra->fd->info = ptr->fd->info;
		++mida;
	}

	if (ptr != NULL) {
		ptra->info = ptr->info;
		++mida;
	}

	return ptra;
}

template <typename Elem>
nat arbbin<Elem>::size() const throw()
{
	return longitud;
}

template <typename Elem>
typename arbbin<Elem>::iterador arbbin<Elem>::arrel() const throw()
{
	iterador it;
	if (pare != NULL) it = pare;
	return it; 
}


//ITERADOR
template <typename Elem>
Elem arbbin<Elem>::iterador::operator*() const throw(error)
{
	return pit->info;
}

template <typename Elem>         
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_esq() const throw(error)
{
	iterador it;
	if (pit->fe != NULL) it.pit = pit->fe;
	else throw error(IteradorNul);
	return it; 
}

template <typename Elem>         
typename arbbin<Elem>::iterador arbbin<Elem>::iterador::fill_dret() const throw(error)
{
	iterador it;
	if (pit->fd != NULL) it.pit = pit->fd;
	else throw error(IteradorNul);
	return it; 
}

template <typename Elem>         
arbbin<Elem>::iterador::operator bool() const throw()
{
	return (pit!=NULL);
}

