namespace huffman {

	int miin(int x, int y)
	//COST: Θ(1)
	//PRE: Dos enters a comparar.
	//POST: Y si es més petit que X. En altre cas, X.
	{
		if (x>y) {
			return y;
		}else{
			return x;
		}
	}

	void camins(arbbin<pair<int, nat> >::iterador it, vector<string>& taula_codis, string s, string s2)
	//COST: Θ(2^n)
	//PRE: Iterador que apunta al node. En la primera crida a la funció it es l'arrel de l'arbre. S és el recorregut que porta. S2 és 0 si el següent pas es a l'esquerra, 1 a la dreta.
	//POST: Omple la taula_codis amb els recorreguts per camins. Un camí es un recorregut desde l'arrel fins a una fulla.
	{
		if (it) {
			
			pair<int, nat> p = *it;
			s+=s2;
			if ((not it.fill_esq()) and not (it.fill_dret())) {
				taula_codis[p.first-1] = s;
			}else{
				if (it.fill_esq()) camins(it.fill_esq(), taula_codis, s, "0");
				if (it.fill_dret()) camins(it.fill_dret(), taula_codis, s, "1");
			}
		}
	}

	void munta_arbre(vector<arbbin<pair<int, nat> > >& freq_sort, vector<string>& taula_codis)
	//COST: munta_arbre = Θ(n²). Θ(max(munta_arbre,camins) = 2^n).
	/*PRE: freq_sort és un vector d'arbres de pairs (índex, freqüència) ordenat incrementalmente de menys freqüència a més. També de menys index a més. 
		   Ex: freq_sort[0..n] on 0 és el menys infreqüent i amb menys index i n tot el contrari.*/
	/*POST: Arbre amb tots el subarbrets que hi havia al vector.
			Agafa els dos subarbres més infreqüents (tal i com està ordenat freq_sort, el més infreqüent és el de l'esquerra d'aquests dos) freq_sort[0] i freq_sort[1]
			i els junta muntant un de nou amb el camp info index/freqüència on index és el mínim dels dos que hem agafat i freqüència la suma de les freqüencies.
			Esborrem els dos subarbres del vector i possem el nou on compleixi que el vector continuï ordenat com la PRE.
			Repetim el procés fins que hi quedi 1 element al vector que hi será l'arbre final amb tots els subarbres muntat.*/
	{
		while (freq_sort.size()>1) {

			pair<int, nat> res;

			arbbin<pair<int, nat> >::iterador it = freq_sort[0].arrel();

			arbbin<pair<int, nat> > fe = freq_sort[0];
			arbbin<pair<int, nat> > fd = freq_sort[1];

			arbbin<pair<int, nat> >::iterador itfe = fe.arrel();
			arbbin<pair<int, nat> >::iterador itfd = fd.arrel();

			pair<int, nat> p1 = (*itfe);
			pair<int, nat> p2 = (*itfd);

			nat frequ = p1.second + p2.second;
			int ind = miin(p1.first, p2.first); //INDEX MÉS PETIT

			res = make_pair(ind, frequ);
			
			arbbin<pair<int,nat> > arbusto(res,fe,fd);

			//ESBORREM ELS DOS PRIMERS ARBRETS
			freq_sort.erase (freq_sort.begin(),freq_sort.begin()+2);

			//BUSCO UNA NOVA POSICIÓ PER AL NOU ARBRET, PER TAL QUE AL AFEGIR-LO EL VECTOR ENCARA SIGUI ORDENAT INCREMENTALMENT.
			bool trobat = false;
			vector<arbbin<pair<int,nat> > >::iterator itVec = freq_sort.begin();

			while (itVec != freq_sort.end() and not trobat) {

				arbbin<pair<int, nat> >::iterador itArbsort = (*itVec).arrel();

				if (res.second <= (*itArbsort).second) {

					if (res.second == (*itArbsort).second) {
						if (res.first < (*itArbsort).first) {
							freq_sort.insert(itVec, arbusto);
							trobat = true;
						}
					}else{
						freq_sort.insert(itVec, arbusto);
						trobat = true;
					}
					
				}
				++itVec;
			}

			if (not trobat) freq_sort.push_back(arbusto);
		
		}

		arbbin<pair<int, nat> >::iterador it = freq_sort[0].arrel();

		camins(it,taula_codis,"","");

	}
}

void huffman::codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error)
//COST: codi_huffman = Θ(3n). Θ(max(codi_huffman,max(munta_abre,camins)) = 2^n)
//PRE: Seqüencia de naturals i taula amb codis (camins de l'arbre resultant) buïda.
/*POST: Si la seqüencia es més petita que 2 elements llança un error.
		Troba el natural màxim de la seqüencia. Crea un vector de pairs índex/freqüència amb la mida del màxim trobat.
		Crea un vector buit d'arbres de pairs.
		Insereix de forma ordenada el parell índex  ordenat incrementalmente de menys freqüència a més. També de menys index a més. 
	    Ex: freq_sort[0..n] on 0 és el menys infreqüent i amb menys index i n tot el contrari.
	    Si té més d'un arbret freq_sort, busca munta l'arbre resultat i buscará els camins per omplir taula_codis*/
{
	if (seq.size()<2) throw error(SeqCurta);

	nat max=seq[0];
	

	unsigned int i=1;
	while (i<seq.size()) {
		if (seq[i] > max) {
			max = seq[i];
		}
		++i;
	}

	taula_codis.resize(max);

	/*CREO UN VECTOR AMB EL VALOR MÀXIM DE LA SEQÜÈNCIA
	QUE CONTINDRÀ EL PARELL (ÍNDEX, FREQÜÈNCIA)*/
	vector<pair<int,nat> > freq(max);
	vector<arbbin<pair<int, nat> > > freq_sort;


	for (unsigned int i=0; i<seq.size(); ++i) {
		++freq[seq[i]-1].second;
		freq[seq[i]-1].first = seq[i];
	}

	vector<pair<int,nat> >::iterator itfreq = freq.begin();
	nat j=1;
	while (freq.size() > 0) {

		if (itfreq == freq.end()) {
			++j;
			itfreq = freq.begin();
		}

		if ((*itfreq).second==j) {

			pair<int,nat> p = make_pair((*itfreq).first,(*itfreq).second);

			arbbin<pair<int, nat> > fe;
			arbbin<pair<int, nat> > fd;

			arbbin<pair<int,nat> > ar(p, fe, fd);

			freq_sort.push_back(ar);

			freq.erase(itfreq);

		}else{
			++itfreq;
		}
		
	}

	if (freq_sort.size()>1) munta_arbre(freq_sort, taula_codis);
}