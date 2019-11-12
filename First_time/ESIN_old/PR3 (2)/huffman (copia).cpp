void ordena(vector<arbbin<pair<int,nat> > > &freq_sort)
{
	unsigned int i=0, j=0;
	bool ordenat = true;
	while(i<freq_sort.size() and not ordenat) {
		while (j<freq_sort.size()) {

		}
		++i;
		j=0;
	}
}

string dep = "";
void pintar(arbbin<pair<int, nat> >::iterador it) 
{
  string d1=dep;
  if (not it) 
    cout<<".";
  else {
  	pair<int, nat> p = *it;
    cout<< "[<"<<p.first << "," << p.second<<">]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    pintar(it.fill_dret());
    cout<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    pintar(it.fill_esq());
  }
  dep=d1;
}

void caminos(arbbin<pair<int, nat> >::iterador it, vector<string>& taula_codis, string s, string s2)
{

	//cout << "CAMINOS" << endl;
	if (it) {
		/*s+=s2;
		if ((not it.fill_esq()) and not (it.fill_dret())) {

			cout << "NO ENTRO NUNCA PUTA" << endl;
			pair<int, nat> p = *it;
			cout << "S me vale mierda << " << s << endl;
			cout << "El fisrt me vale mierda " << p.first << " y el secon " << p.second<< endl;
			taula_codis[p.first] = s;
		}else{

			//if (it.fill_esq()) {
				
				caminos(it.fill_esq(), taula_codis, s, "0");
				//s+="0";
			//}
			
			//if (it.fill_dret()) {
				
				caminos(it.fill_dret(), taula_codis, s, "1");
				//s+="1";
			//}
		}*/

		pair<int, nat> p = *it;
		//cout << "El fisrt me vale mierda " << p.first << " y el secon " << p.second<< endl;
		s+=s2;
		//cout << "S me vale mierda << " << s << endl;
		if ((not it.fill_esq()) and not (it.fill_dret())) {
			taula_codis[p.first-1] = s;
		}else{

				if (it.fill_esq()) caminos(it.fill_esq(), taula_codis, s, "0");
				if (it.fill_dret()) caminos(it.fill_dret(), taula_codis, s, "1");

		}

	}

}

void monta_arbol(vector<arbbin<pair<int, nat> > >& freq_sort, vector<string>& taula_codis) {

	arbbin<pair<int, nat> > arb;
	/*arbbin<pair<int, nat> > arb::iterator it;
	*/

	while (freq_sort.size()>1) {

		pair<int, nat> res;

		arbbin<pair<int, nat> >::iterador it = freq_sort[0].arrel();

		/*if (i==0) {

			arbbin<pair<int, nat> >::iterador it2 = freq_sort[i].arrel();

			res = make_pair(min((*itb).first,(*(itb+1)).first), ((*itb).second+(*(itb+1)).second));

			arbbin<pair<int, nat> > fe((*itb), arbbin<pair<int,nat> >(), arbbin<pair<int,nat> >());
			arbbin<pair<int, nat> > fd((*(itb+1)), arbbin<pair<int,nat> >(), arbbin<pair<int,nat> >());

			arb = arbbin<pair<int,nat> > (res, fe, fd);

			*/


		//}else{

		arbbin<pair<int, nat> > fe = freq_sort[0];
		arbbin<pair<int, nat> > fd = freq_sort[1];

		arbbin<pair<int, nat> >::iterador itfe = fe.arrel();
		arbbin<pair<int, nat> >::iterador itfd = fd.arrel();

		pair<int, nat> p1 = (*itfe);
		pair<int, nat> p2 = (*itfd);

		nat frequ = p1.second + p2.second;
		int ind = min(p1.first, p2.first); //INDICE MÁS BAJO

		res = make_pair(ind, frequ);
		

		arbbin<pair<int,nat> > arbusto(res,fe,fd);

		//cout << "freq_sort["<<0<<"].second="<< p1.second << " > p.second=" << p2.second << endl;

		//SI LA FRECUENCIA ES MAYOR EL DEL VECTOR QUE EL DEL ARBOL, EN LA DERECHA, SINO PA LA IZQUIERDA
		/*if (*(it).second > *(it+1).second) {

			cout << "DERECHA" << endl;
			
			arbusto = arbbin<pair<int,nat> > (res, arb, arbu);

		}else{

			cout << "IZQUIERDA" << endl;

			arbusto = arbbin<pair<int,nat> > (res, arbu, arb);
		}*/

		//ELIMINAMOS DOS PRIMEROS ARBOLITOS
		freq_sort.erase (freq_sort.begin(),freq_sort.begin()+2);

		//BUSCO NUEVA POSICION
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

		//cout << "Añadido pair<" << res.first << "," << res.second << ">" << endl;
	
	}

	//cout << "EL ARBOL ES DE TAMAÑO " << freq_sort[0].size() << endl;

	arbbin<pair<int, nat> >::iterador it = freq_sort[0].arrel();

	//cout << "LA TABLA ME VALE MIERDA " << taula_codis.size() << endl;

	//cout << "MI ARBOL" << endl;

	//pintar(it);

	//cout << endl;

	it = freq_sort[0].arrel();

	caminos(it,taula_codis,"","");

	//cout << "SALIDA CAMINOS" << endl;
}

void huffman::codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error)
{
	//cout << "ENTRANDO" << endl;
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


	//CREO UN VECTOR CON EL VALOR MÁXIMO DE LA SECUENCIA
	//QUE CONTENDRA EL PAR (INDICE, FRECUENCIA)
	vector<pair<int,nat> > freq(max);
	vector<arbbin<pair<int, nat> > > freq_sort;


	for (unsigned int i=0; i<seq.size(); ++i) {
		++freq[seq[i]-1].second;
		freq[seq[i]-1].first = seq[i];
	}


	/*cout << "SIN ORDENAR" << endl;
	for (unsigned int i=0; i<max; ++i) {
		cout << "Indice: " << i+1 << ", Frecuencia: " << freq[i] << endl;
	}*/

	/*for (unsigned int i=0; i<max; ++i) {
		pair<int,nat> p = make_pair(i+1,freq[i]);

		arbbin<pair<int, nat> > fe;
		arbbin<pair<int, nat> > fd;

		arbbin<pair<int,nat> > ar(p, fe, fd);

		arbbin<pair<int, nat> >::iterador itp = fd.arrel();
		arbbin<pair<int, nat> >::iterador itf = fd.arrel();

		freq_sort.push_back(ar);
	}*/

	//cout << "ORDENAR" << endl;

	vector<pair<int,nat> >::iterator itfreq = freq.begin();
	nat j=1;
	while (freq.size() > 0) {

		if (itfreq == freq.end()) {
			++j;
			itfreq = freq.begin();
		}

		if ((*itfreq).second==j) {

			pair<int,nat> p = make_pair((*itfreq).first,(*itfreq).second);

			//cout << "AGREGO " << (*itfreq).first << "/" << (*itfreq).second << endl;

			arbbin<pair<int, nat> > fe;
			arbbin<pair<int, nat> > fd;

			arbbin<pair<int,nat> > ar(p, fe, fd);

			freq_sort.push_back(ar);

			//cout << "ELIMINO " << endl;

			//cout << freq.size() << endl;

			freq.erase(itfreq);

			//cout << freq.size() << endl;

		}else{
			++itfreq;
		}
		
	}


	/*for (unsigned int i=0; i<max; ++i) {
		pair<int, nat> p;
		if (i) {
			freq_sort.push_back(p = make_pair(i+1,));
		}else{

			if (freq_sort.back().second<=freq[i]) {
				cout << "1. " << freq_sort.back().first << "/" << freq_sort.back().second << " > " << i+1 << "/" << freq[i] << endl;
				
				freq_sort.insert(freq_sort.end(), p = make_pair(i+1,freq[i]));
	
				if (freq_sort[freq_sort.size()-1].first < freq_sort[freq_sort.size()-2].first) {

					cout << "1. " << freq_sort[freq_sort.size()-1].first << "<" << freq_sort[freq_sort.size()-1].second << " == " << freq_sort[freq_sort.size()-2].first << "/" << freq_sort[freq_sort.size()-2].second << endl;
					
					pair<int, nat> p = freq_sort[freq_sort.size()-1];

					freq_sort[freq_sort.size()-1] = freq_sort[freq_sort.size()-2];
					freq_sort[freq_sort.size()-2] = p;

				}else{//SI SON IGUALES, MIRAR INDICES
					//if () {}
				} 

				
			}else if (freq_sort.front().second>=freq[i]) {
				cout << "2. " << freq_sort.front().first << "/" << freq_sort.front().second << " > " << i+1 << "/" << freq[i] << endl;
				
				freq_sort.insert(freq_sort.begin(), p = make_pair(i+1,freq[i]));
			
				cout << "2. " << freq_sort[0].first << "/" << freq_sort[0].second << " > " << freq_sort[1].first << "/" << freq_sort[1].second << endl;
					
				if (freq_sort[0].first > freq_sort[1].first) {
	
					pair<int, nat> p = freq_sort[0];

					freq_sort[0] = freq_sort[1];
					freq_sort[1] = p;
				}//SI SON IGUALES, MIRAR INDICES
				
			}
		}
	}*/

	//sort(freq_sort.begin(), freq_sort.end(),sortbysec);


	//cout << "ORDENADO" << endl;
	/*for (unsigned int i=0; i<max; ++i) {
		cout << "Indice: " << i << endl;
		arbbin<pair<int, nat> >::iterador it = freq_sort[i].arrel();
		pintar(it);
		cout << endl;
	}*/

	/*vector< arbbin<pair<int,nat> > > carb(max/2);

	arbbin<pair<int,nat> > fe;
	arbbin<pair<int,nat> > fd;

	for (unsigned int i=0; i<max; ++i) {
		carb.push_back(arbbin<pair<int,nat> > (make_pair(freq_sort[i].first,freq_sort[i].second),fe, fd));
	}*/

	if (freq_sort.size()>1) monta_arbol(freq_sort, taula_codis);

	//cout << "SALIENDO" << endl;

}