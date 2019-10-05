
#ifndef _HUFFMAN_HPP
#define _HUFFMAN_HPP

#include <vector>
#include <string>

#include <esin/error>
#include <esin/util>

using util::nat;
using namespace std;

namespace huffman {

  void codi_huffman(const vector<nat>& seq, vector<string>& taula_codis) throw(error);

  static const int SeqCurta = 21;

};
#endif
