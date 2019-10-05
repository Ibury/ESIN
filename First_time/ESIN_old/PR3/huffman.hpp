
#ifndef _HUFFMAN_HPP
#define _HUFFMAN_HPP

#include <vector>
#include <string>

#include <esin/error>
#include <esin/util>

#include <iterator>
#include <utility>
#include <bits/stdc++.h>

using util::nat;
using namespace std;

namespace huffman {

  void codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error);
  //void caminos(arbbin<pair<int, nat> >::iterador it, arbbin<pair<int, nat> >::iterador fi, vector<string>& taula_codis);
  //void monta_arbol(vector<pair<int, nat> >& freq_sort, vector<string>& taula_codis);

  static const int SeqCurta = 21;

};
#include "arbbin.hpp"
#include "huffman.cpp"
#endif
