#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <esin/error>
#include <esin/gen_driver>
#include <esin/util>


#include "arbbin.hpp"
#include "huffman.hpp"


/* TypeTraits */
template <> const char* TypeTraits<arbbin<int> >::name = "arbbin<int>";
template <> const char* TypeTraits<arbbin<int>::iterador>::name = "arbbin<int>::iterador";
template <> const char* TypeTraits<vector<nat> >::name = "vector<nat>";
template <> const char* TypeTraits<vector<string> >::name = "vector<string>";




typedef arbbin<int>* Arbbin_int;
typedef vector<nat>* Vector_nat;
typedef vector<string>* Vector_string;
typedef arbbin<int>::iterador* Iterator;

using util::byte;
using util::nat;

ostream& operator<=(ostream& os, const bool b) {
  os << (b ? "true" : "false");
  return os;
}

// imprimir vector

template <typename T>
void imprimeix_vector(const vector<T>& V, const char sep = ' ', ostream& os = std::cout) {
  for (unsigned int i = 0; i < V.size(); ++i) {
    os << V[i] << sep;
  }
  os << endl;
}

// imprimir pair

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& x) {
  os << '(' << x.first << ',' << x.second << ')';
  return os;
}

// imprimir arbbin en post-ordre

template <typename Iter>
void imprimeix_arbbin_rec(const Iter& it, const char sep, ostream& os) {
  if (it) {
    imprimeix_arbbin_rec(it.fill_esq(), sep, os);
    imprimeix_arbbin_rec(it.fill_dret(), sep, os);
    os << *it << sep;
  }
}

template <typename T>
void imprimeix_arbbin(const arbbin<T>& A, const char sep = ' ', ostream& os = std::cout) {
  imprimeix_arbbin_rec(A.arrel(), sep, os);
  os << endl;
}


////////Basicas:constructoras, asignacion y destruccion//////////

void* user_init(gen_driver& dr) {
  string id = dr.args(1);
  string tid = dr.args(2);
  if (tid == "arbbin<int>") { 
    if (dr.nargs() == 2) {
      return static_cast<void*>(new arbbin<int>);
    }
    else if (dr.nargs() == 3) {
      int x = util::toint(dr.args(3));
      return static_cast<void*>(new arbbin<int>(x, arbbin<int>(), arbbin<int>()));
    }
    else if (dr.nargs() == 5) {
      int x = util::toint(dr.args(3));
      if (dr.object_type(4) != "arbbin<int>" or 
	  dr.object_type(5) != "arbbin<int>") {
        throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
                    gen_driver::WrongTypeArgsMsg);
      }
      arbbin<int> *fe = dr.object<arbbin<int> >(4);
      arbbin<int> *fd = dr.object<arbbin<int> >(5);
      return static_cast<void*>(new arbbin<int>(x, *fe, *fd));
    }
    else {
      throw error(gen_driver::WrongNumArgs, gen_driver::nom_mod,
		  gen_driver::WrongNumArgsMsg);
    }
  }
  if (tid == "arbbin<int>::iterador") {
    if (dr.nargs() != 2) {
      throw error(gen_driver::WrongNumArgs, gen_driver::nom_mod, 
                  gen_driver::WrongNumArgsMsg);
    }
    return static_cast<void*>(new arbbin<int>::iterador()); 
  }
  if (tid == "vector<nat>") {
    if (dr.nargs() != 2) {
      throw error(gen_driver::WrongNumArgs, gen_driver::nom_mod, 
                  gen_driver::WrongNumArgsMsg);
    }
    return static_cast<void*>(new vector<nat>); 
  }
  if (tid == "vector<string>") {
    if (dr.nargs() != 2) {
      throw error(gen_driver::WrongNumArgs, gen_driver::nom_mod, 
                  gen_driver::WrongNumArgsMsg);
    }
    return static_cast<void*>(new vector<string>); 
  }
 
  throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
	      gen_driver::WrongTypeArgsMsg);

}


//////////////////////////arbbin/////////////////////////

template <typename T>
void tracta_size(gen_driver& dr) {
  arbbin<T> *a = dr.template object<arbbin<T> >();
  dr.get_ostream() << a->size() << endl;
}

template <typename T>
void tracta_arrel(gen_driver& dr) {
  arbbin<T> *a = dr.template object<arbbin<T> >();
  dr.get_ostream() << *(a->arrel()) << endl;
}

template <typename T>
void tracta_print_arbbin(gen_driver& dr) {
  if (dr.object_type() == "arbbin<int>") {
    arbbin<T> *a = dr.template object<arbbin<T> >();
    imprimeix_arbbin(*a,' ',dr.get_ostream());
  }
  else {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		gen_driver::WrongTypeArgsMsg);
  }
}

//////////////////////////arbbin<int>::iterador/////////////////////////

template <typename T>
void tracta_bool(gen_driver& dr) {
  if (dr.object_type() == "arbbin<int>::iterador") {
    Iterator it = dr.template object<typename arbbin<T>::iterador>();
    dr.get_ostream() <= (it->operator bool());
    dr.get_ostream() << endl;
  }
  else {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		gen_driver::WrongTypeArgsMsg);
  }
}

template <typename T>
void tracta_consult_iterador(gen_driver& dr) {
  if (dr.object_type() == "arbbin<int>::iterador") {
    Iterator it = dr.template object<typename arbbin<T>::iterador>();
    dr.get_ostream() << it->operator*() << endl;
  }
  else {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		gen_driver::WrongTypeArgsMsg);
  }
}

template <typename T>
void tracta_fill_esq(gen_driver& dr) {
  if (dr.object_type() == "arbbin<int>::iterador") {
    Iterator it = dr.template object<typename arbbin<T>::iterador>();
    dr.get_ostream() << *(it->fill_esq()) << endl;
  }
  else {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
                  gen_driver::WrongTypeArgsMsg);
  }
}

template <typename T>
void tracta_fill_dret(gen_driver& dr) {
  if (dr.object_type() == "arbbin<int>::iterador") {
    Iterator A = dr.template object<typename arbbin<T>::iterador>();
    dr.get_ostream() << *(A->fill_dret()) << endl;
  }
  else {
     throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		 gen_driver::WrongTypeArgsMsg);
  }
}

//////////////////////////vector<nat>, vector<string> i vector<byte>//////////////////

void tracta_insereix_v(gen_driver& dr){
  if (dr.object_type() == "vector<nat>") {
    Vector_nat v = dr.object<vector<nat> >();
    nat i = static_cast<nat>(util::toint(dr.args(1)));
    v->push_back(i);
  }
  else if (dr.object_type() == "vector<string>") {
    Vector_string v = dr.object<vector<string> >();
    v->push_back(dr.args(1));
  }
  else {
     throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		 gen_driver::WrongTypeArgsMsg);
  }
}

//////////////////////////huffman/////////////////////////

void tracta_huffman(gen_driver& dr){
  Vector_nat S = dr.object<vector<nat> >(dr.args(1));
  vector<string> taula_codis;

  huffman::codi_huffman(*S, taula_codis);
  imprimeix_vector(taula_codis,' ',dr.get_ostream());
}

/*void tracta_codifica(gen_driver& dr) {
  Vector_nat S = dr.object<vector<nat> >(1);
  Vector_string C = dr.object<vector<string> >(2);

  vector<byte> out;
  nat nbits;

  huffman::codifica(*S, *C, out, nbits);
  dr.get_ostream() << nbits << endl;
  imprimeix_vector_byte_string(out,' ',dr.get_ostream());
  }*/


//////////////////////////////////////////////////////////////

int main() {
  gen_driver d("errors_huffman.txt");
  
  //arbbin<int>
  d.add_call("arrel", tracta_arrel<int>, "arbbin<int>", "",
	     "[<arbbin<int>>] arrel"); 
  d.add_call("size", tracta_size<int>, "arbbin<int>", "",
	     "[<arbbin<int>>] (s)ize"); 
  d.add_call("s", tracta_size<int>, "arbbin<int>", "",
	     "[<arbbin<int>>] (s)ize"); 
 
  d.add_call("print_arbbin", tracta_print_arbbin<int>, "arbbin<int>", "",  
	     "[<arbbin<int>>] (p)rint_(a)rbbin");
  d.add_call("pa", tracta_print_arbbin<int>, "arbbin<int>", "", 
	     "[<arbbin<int>>] (p)rint_(a)rbbin"); 

  //vector<nat>, vector<string>
  d.add_call("insereix_v", tracta_insereix_v, "*");
  d.add_call("iv", tracta_insereix_v, "*");

  //huffman
  d.add_call("huffman", tracta_huffman, "*", "vector<nat>",
	     "(huff)man <vector<nat>");
  d.add_call("huf", tracta_huffman, "*", "vector<nat>",
	     "(huff)man <vector<nat>");

  //d.add_call("codifica", tracta_codifica, "*", "vector<string>");
  //d.add_call("c", tracta_codifica, "*", "vector<string>");

  // iterador de arbbin<int>
  d.add_call("bool", tracta_bool<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (b)ool");
  d.add_call("b", tracta_bool<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (b)ool");
  d.add_call("consult_iterador", tracta_consult_iterador<int>, 
	     "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (c)onsult_(i)terador");
  d.add_call("ci", tracta_consult_iterador<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (c)onsult_(i)terador");
  d.add_call("fill_esq", tracta_fill_esq<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (f)ill_(e)sq");
  d.add_call("fe", tracta_fill_esq<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (f)ill_(e)sq");
  d.add_call("fill_dret", tracta_fill_dret<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (f)ill_(d)ret");
  d.add_call("fd", tracta_fill_dret<int>, "arbbin<int>::iterador", "",
	     "[<arbbin<int>::iterador>] (f)ill_(d)ret");

  d.install_type<arbbin<int> >();
  d.install_type<arbbin<int>::iterador>();
  
  d.install_std_type<vector<nat> >();
  d.install_std_type<vector<string> >();

  d.go(); 

}
