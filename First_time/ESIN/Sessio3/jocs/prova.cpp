#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "huffman.hpp"
#include "arbbin.hpp"
using namespace std;

typedef unsigned int nat;

void mostra_taula(vector<string> v){
	for (nat i = 0;i<v.size();++i){
		string s = v[i];
		cout << s << endl;
	}
}

void mostra_arbre (arbbin<pair<int,nat> >arbre){
	arbbin<pair<int, nat > >::iterador it = arbre.arrel();
	pair <int, nat> p = (*it);
	cout << "Index -> "<<p.first<< "Frequencia -> "<<p.second<<endl;
}

void print (vector<pair<int,nat> > v){
	for (unsigned int i = 0;i<v.size();++i){
		pair<int,nat> p = v[i];
		cout << "Pair ("<<i<<") Index -> "<<p.first<<" Frequencia -> "<<p.second<<endl;
	}
}

void mostra_vector (vector<arbbin<pair<int,nat > > >v){
	for (unsigned int i=0;i<v.size();++i){
		arbbin<pair<int,nat> > a = v[i];
		mostra_arbre(a);
	}
}

void mostra_vector_int (vector<int> v){
	for (unsigned int i =0;i<v.size();++i){
		cout << v[i]<< " ";
	}
	cout<<endl;
}

void mostra_vector_string (vector<string> v){
	for (unsigned int i=0;i<v.size();++i){
		string s = v[i];
		cout << s << " ";
	}
	cout<<endl;
}

void recorre_arbre (arbbin<pair<int,nat> >::iterador it,vector<string>& v,string s){
	//cout << "Recurrencia "<<endl;

  	if (it){
  		arbbin<pair<int,nat> >::iterador it2 = it.fill_dret();
  		arbbin<pair<int,nat> >::iterador it3 = it.fill_esq();
  		//cout << "!it"<<endl;

  		


  		if (it3){
  			pair<int,nat> esq = *(it3);
  			//cout << "Fill esquerra -> "<<esq.first<<" Freq -> "<<esq.second<<endl;
  			//cout << "!it3"<<endl;
  			string s3 = s;
  			s3+='0';
  			recorre_arbre(it.fill_esq(),v,s3);
  		}

  		if (it2){
	  		pair<int,nat> dret = *(it2);  		
  			//cout << "Fill dret -> "<<dret.first<<" Freq -> "<<dret.second<<endl;
  			//cout << "!it2"<<endl;
  			string s1 = s;
  			s1+='1';
  			recorre_arbre(it.fill_dret(),v,s1);

  		}  		

  		else{
  			pair<int,nat> p = (*it);
  			v[p.first-1] = s;
  		}

  	}

  }




int main(){

	vector<nat> seq;
	nat t;
	while (cin>>t) seq.push_back(t);
	/*pair<int,nat> buit = make_pair(0,0);

	vector<pair<int,nat> > v(seq.size(),buit);

	int max = 0;
	int freq = 0;

	for (unsigned int i=0;i<seq.size();++i){
		if (seq[i]>max) max = seq[i];
		v[seq[i]-1].second++;
		v[seq[i]-1].first = seq[i];
		if (freq < seq[i]) freq = seq[i];
	}

	vector<arbbin<pair<int,nat> > > v_arbre;
	
	for (unsigned int i=0;i<v.size();++i){
		if (v[i].second!=0){
			arbbin<pair<int,nat > > nou (v[i],arbbin<pair<int,nat> >(),arbbin<pair<int,nat> > ());	
			v_arbre.push_back(nou);
		}
	}

	cout << "MOSTRAR ARBRE: "<<endl;
	mostra_vector(v_arbre);

	print(v);
	cout << "MAX -> "<<n<<endl;*/

	vector<int> v (seq.size(),0);

	nat max = v[0];
	int freq = 0;

	for (nat i=0;i<seq.size();++i){
		v[seq[i]-1]++;
		if (seq[i]>max) max = seq[i];
		if (v[seq[i]-1]>freq) freq = v[seq[i]-1];
	}

	mostra_vector_int(v);

	//cout << "Valor maxim -> "<<max<<endl;
	//cout << "Valor frequencia -> "<<freq<<endl;


	vector<arbbin<pair<int,nat> > > v_arbre;
	cout << "Freq -> "<<freq<<endl;

	//cout << "V.size()"<<v.size()<<endl;

	while (freq>0){
		for (int i =v.size()-1;i>=0;--i){
			
			if (v[i]==freq){
				pair<int,nat> tt= make_pair(i+1,v[i]);
				arbbin<pair<int,nat> > nou (tt,arbbin<pair<int,nat> >(),arbbin<pair<int,nat> >());
				v_arbre.push_back(nou);
				v[i]=0;
			}
		}
		--freq;
	}

	mostra_vector(v_arbre);

	while (v_arbre.size() > 1){
		
		arbbin<pair<int,nat> > arbre1 = v_arbre[v_arbre.size()-1];
		arbbin<pair<int,nat> > arbre2 = v_arbre[v_arbre.size()-2];

		arbbin<pair<int,nat> >::iterador it1 = arbre1.arrel();
		arbbin<pair<int,nat> >::iterador it2 = arbre2.arrel();

		pair<int,nat> pair1 = (*it1);
		pair<int,nat> pair2 = (*it2);
		pair<int,nat> prova = make_pair (min(pair1.first,pair2.first),pair1.second + pair2.second);
		arbbin<pair<int,nat> >final;

		if (pair1.second == pair2.second){
			if (pair1.first > pair2.first){
				final = arbbin<pair<int,nat> > (prova,arbre2,arbre1);
			}
			else final = arbbin<pair<int,nat> > (prova,arbre1,arbre2);
		}

		else if (pair1.second > pair2.second) final = arbbin<pair<int,nat> > (prova,arbre2,arbre1);
		else final = arbbin<pair<int,nat> > (prova,arbre1,arbre2);

		// ARBRES MONTAT DEL FINAL

	

		vector<arbbin<pair<int,nat> > >::iterator v_it = v_arbre.end();
		--v_it;
		--v_it;

		vector<arbbin<pair<int,nat> > >::iterator it_insert = v_it;


		while (v_it!=v_arbre.begin()){
			arbbin<pair<int,nat> > arbolito = (*v_it);
			arbbin<pair<int,nat> >::iterador it_ar = arbolito.arrel();
			pair<int,nat> p_ar = (*it_ar);
			if (p_ar.first < prova.first) it_insert = v_it;
			--v_it; // Avança
		}

		v_arbre.insert(it_insert,final);

		// Treiem els dos arbres obtinguts anteriorment
		v_arbre.pop_back();
		v_arbre.pop_back();

	}

	cout << v_arbre.size()<<endl;

	arbbin<pair<int,nat> >imprimir = v_arbre[0];

	arbbin<pair<int,nat> >::iterador prova = imprimir.arrel();

	pair<int,nat> privaf = *(prova);

	cout << "Index -> "<<privaf.first<<" Freq -> "<<privaf.second<<endl;

	// CONSTRUEIX STRING -----

	string s ="";
	vector<string> v_string(max);
	arbbin<pair<int,nat> >::iterador it = imprimir.arrel();
	recorre_arbre(it,v_string,s);

	cout << "RESULTAT :" <<endl;

	mostra_vector_string(v_string);

	cout << "SIZE : "<<	imprimir.size() <<endl;




}