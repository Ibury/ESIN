#include <string>
#include <vector>
#include <iostream>
#include <esin/error>
#include <esin/util>
#include "huffman.hpp"
#include "arbbin.hpp"
using util::nat;
using namespace std;

typedef unsigned int nat;


namespace huffman {

	void recorre_arbre (arbbin<pair<int,nat> >::iterador it,vector<string>& v,string &s){
	//Pre: Cert.
	//Post: Recorre tot l'arbre mentres va construint el vector d'strings, si es va cap al fill esquerra s'afegeix un "0" i cap a la dreta un "1"
	//Cost: Θ (n) Recorre tots els nodes

   	if (it){

  		if (it.fill_esq()){
  			string s3 = s;
  			s3+='0';
  			recorre_arbre(it.fill_esq(),v,s3);
  		}

  		if (it.fill_dret()){
  			string s1 = s;
  			s1+='1';
  			recorre_arbre(it.fill_dret(),v,s1);
  		}

  		else v[((*it).first)-1] = s;
  	}

}

	int get_petit (const int &p1, const int &p2)
	//Pre: Cert.
	//Post: Retorna el valor més petit entre p1 i p2.
	//Cost Θ (1)
	{
		return p1 < p2 ? p1 : p2;
	}




	void codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error){
		//Pre: seq.size > 1
		//Post: Vector de strings ple amb la seqüencia huffman de cada índex del rang [1..k]
		//Cost: Θ (n²) Cost maxim

		if (seq.size()<2) throw error (SeqCurta);
		
		vector<int> v (seq.size(),0);

		nat max = v[0];
		int freq = 0;

		for (nat i=0;i<seq.size();++i){
			v[seq[i]-1]++;
			if (seq[i]>max) max = seq[i];
			if (v[seq[i]-1]>freq) freq = v[seq[i]-1];
		}

		vector<arbbin<pair<int,nat> > > v_arbre;

		//MONTEM VECTOR ARBBIN PAIR
		
		while (freq>0){
			for (int i=v.size()-1;i>=0;--i){				
				if (v[i]==freq){
					arbbin<pair<int,nat> > nou (pair<int,nat>(i+1,v[i]),arbbin<pair<int,nat> >(),arbbin<pair<int,nat> >());
					v_arbre.push_back(nou);					
				}
			}
			--freq;
		}
		
		while (v_arbre.size() > 1){
			
			arbbin<pair<int,nat> > arbre1 = v_arbre[v_arbre.size()-1];
			arbbin<pair<int,nat> > arbre2 = v_arbre[v_arbre.size()-2];

			v_arbre.pop_back();
			v_arbre.pop_back();

			arbbin<pair<int,nat> >::iterador it1 = arbre1.arrel();
			arbbin<pair<int,nat> >::iterador it2 = arbre2.arrel();
			
			pair<int,nat> pair1 = (*it1);
			pair<int,nat> pair2 = (*it2);

			pair<int,nat> prova = make_pair (get_petit(pair1.first,pair2.first),pair1.second + pair2.second);
			arbbin<pair<int,nat> >final;

			if (pair1.second == pair2.second){
				if (pair1.first > pair2.first) final = arbbin<pair<int,nat> > (prova,arbre2,arbre1);			
				else final = arbbin<pair<int,nat> > (prova,arbre1,arbre2);
			}

			else if (pair1.second > pair2.second) final = arbbin<pair<int,nat> > (prova,arbre2,arbre1);
			else final = arbbin<pair<int,nat> > (prova,arbre1,arbre2);



			// ARBRES MONTAT DEL FINAL		

			vector<arbbin<pair<int,nat> > >::iterator v_it = v_arbre.begin();
			vector<arbbin<pair<int,nat> > >::iterator v_insert = v_arbre.begin();

			bool posat = false;

			//RECOLOCA ARBRES CREATS

			while (v_it!=v_arbre.end() and not posat){
				arbbin<pair<int,nat> >::iterador it_ar = (*v_it).arrel();
				pair<int,nat> p_it = (*it_ar);
				if (p_it.second > prova.second) ++v_it; 
				else if (p_it.second == prova.second and v_it!=v_arbre.end() and p_it.first > prova.first) ++v_it;
				else if (p_it.second < prova.second){
					posat = true;
					v_insert = v_it;
				}

				else if (p_it.second == prova.second and v_it!=v_arbre.end() and p_it.first < prova.first){
					v_insert = v_it;
					posat = true;
				}

			}
			v_arbre.insert(v_insert,final);
		}

		//CREAR VECTOR STRINGS

		arbbin<pair<int,nat> >imprimir = v_arbre[0];
		string s ="";
		vector<string> v_string(max);
		arbbin<pair<int,nat> >::iterador it = imprimir.arrel();
		recorre_arbre(it,v_string,s);
		taula_codis = v_string;
	}
}  