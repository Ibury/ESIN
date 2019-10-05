#include <iostream>
#include "arbre.h"
#include <vector>
#include "token.h"
#include <stack>
#include <cmath>

//TUPLA PER PRIORITATS LLEGIR INFIXA.
struct priority {
	token p;
	int n;
	bool l;
};


string ExpressioPrefixa(arbre<token> a) 
/*Pre: Cert. */
/*Post: String amb recorregut preordre de l'arbre a.*/
{
	string s="";
	stack<arbre<token> > p;
    
    p.push(a);
        
    //INV: p conté l'arbre a i els arbres fills
    //Funcio de Fita: Altura de l'arbre, arbres fills entre arrel i fulles
    while (not p.empty()) {
        arbre<token> a1 = p.top();
        p.pop();
        if (not a1.es_buit()) {
        	s = s + a1.arrel().to_string() + " ";
            if (not a1.fd().es_buit()) p.push(a1.fd());
            if (not a1.fe().es_buit()) p.push(a1.fe());
        }
    }

    return s;
}


string ExpressioPostfixa(arbre<token> a)
/*Pre: Cert. */
/*Post: String amb recorregut postordre de l'arbre a.*/
{	
	string s = "";
    stack<arbre<token> > p;
    
    token arr;

    if (not a.es_buit()) arr = a.arrel();
	if (not a.fd().es_buit()) p.push(a.fd());
	if (not a.fe().es_buit()) p.push(a.fe());

    //INV: p conté els arbres.
    //Funcio de Fita: Altura de l'arbre disminueix, arbres fills entre arrel i fulles
    while (not p.empty()){

        arbre<token> a1 = p.top();
        p.pop();
        
        if (not a1.es_buit()){
            if (a1.fd().es_buit() and a1.fe().es_buit()){
             s = s + a1.arrel().to_string() + " ";
             
         }

            else {
	            arbre<token> abuit;
                arbre<token> aux (a1.arrel(),abuit,abuit);
                p.push(aux);  
                if (not a1.fd().es_buit()) p.push(a1.fd());
                if (not a1.fe().es_buit()) p.push(a1.fe());  

            }  
        }      
    }

    s = s + arr.to_string() + " ";

    return s;
}


string ExpressioInfixa(arbre<token> a)
/*Pre: Cert. */
/*Post: String amb recorregut inodre de l'arbre a.*/
{	
	
	string s = "";
	if (not a.es_buit()){
		
		if (a.arrel().es_operador_binari() or a.arrel().es_operador_commutatiu())
			s = s + "(" + ExpressioInfixa(a.fe()) + " " +  a.arrel().to_string() + " " + ExpressioInfixa(a.fd()) + ")";
			/*HI: A s hem fusionat les arrels de l'arbre actual més fills esquerra i dret.*/
            /*FF: L'arbre es va desglossant i l'string es va fent més llarg.*/
		
		
		else if (a.arrel().es_operador_unari()) s = "(" + a.arrel().to_string() + " " + ExpressioInfixa(a.fe()) + ")" ;
			/*HI: A s hem fusionat les arrels de l'arbre actual més fills esquerra i dret.*/
            /*FF: L'arbre es va desglossant i l'string es va fent més llarg.*/
		

		else s = s +  a.arrel().to_string();
		

	}

	return s;
}


arbre<token> LlegirPrefixa() {
/*Pre: Cert.*/
/*Post: Retorna un arbre a partir d'un token en recorregut preordre.*/

	arbre<token> ar;
	token t;
	
	cin >> t;

	if (t.es_operador_binari()) {

		arbre<token> fe = LlegirPrefixa();
		arbre<token> fd = LlegirPrefixa();
		arbre<token> ar1(t,fe,fd);
		ar = ar1;
		/*HI: ar1 hi tenim els tokens de l'arbre ordenats jeràrquicament. L'arbre ar1 té fill esquerra, dreta i l'arrel és un operador binari*/
        /*FF: A cada crida recursiva l'arbre es va desglossant fins a quedar buit.*/
	}

	else if (t.es_operador_unari()) {
	    arbre<token> ar1(t,LlegirPrefixa(),arbre<token>());
		ar = ar1;
		/*HI: ar1 hi tenim els tokens de l'arbre ordenats jeràrquicament. L'arbre ar1 té fill esquerra i l'arrel és un operador unari*/
        /*FF: A cada crida recursiva l'arbre es va desglossant fins a quedar buit.*/
	}

	else {
		arbre<token> ar1(t);
		ar = ar1;
		/*HI: ar1 hi tenim els tokens de l'arbre ordenats jeràrquicament. L'arbre no té fills i l'arrel es qualsevol cosa que ni sigui operador binari o unari*/
        /*FF: A cada crida recursiva l'arbre es va desglossant fins a quedar buit.*/
	}

	return ar;
}


arbre<token> LlegirPostfixa() 
/*Pre: Cert.*/
/*Post: Retorna un arbre a partir d'un token en recorregut postordre.*/
{


	arbre<token> ar;
	token p;
	
	stack<arbre<token > > s;
	
	cin >> p;

    //INV: s conté l'arbre de la postcondició
    //Funcio de Fita: Quantitat d'elements que hi ha entre l'arbre de tokens que creix i el flux de dades, fins que arriba al centinella 
	while (p!="->"){	

		if (p.es_enter() or p.es_variable() or p.es_boolea()){
			arbre<token> v1 (p);
			s.push(v1);

		}
		
		else if (p.es_operador_binari() or p.es_operador_commutatiu()){
			arbre<token> v1 = s.top();
			s.pop();
			arbre<token> v2 = s.top();
			s.pop();
			arbre<token> def (p,v2,v1);
			s.push(def);

		}

		else {
			arbre<token> v1 = s.top();
			s.pop();
			arbre<token> def (p,v1,arbre<token>());
			s.push(def);
		}

		cin >> p;

	}	

	ar = s.top();
	return ar;
}


pair <int,bool> getPrioritat (token t)
/*Pre: Token t conté un operador. */
/*Post: Retorna la prioritat (int / bool) del token t.*/
{

	vector<priority> v;
	
	
	priority a = {token(string("or")),1,true};
	v.push_back(a);
	priority b = {token(string("and")),2,true};
	v.push_back(b);
	priority c = {token(string("not")),3,false};
	v.push_back(c);
	priority d = {token(string("==")),4,true};
	v.push_back(d);
	priority e = {token(string("!=")),4,true};
	v.push_back(e);
	priority f = {token(string("+")),5,true};
	v.push_back(f);
	priority g = {token(string("-")),5,true};
	v.push_back(g);
	priority h = {token(string("*")),6,true};
	v.push_back(h);
	priority i = {token(string("/")),6,true};
	v.push_back(i);
	priority j = {token(string("**")),7,false};
	v.push_back(j);
	priority l = {token(string("(")),0,false};
	v.push_back(l);

	priority m ;

	bool trobat = false;
	
	unsigned int k = 0;
	
	//INV: v conté la taula de prioritat d'operadors.
	while (k<v.size() and not trobat){
		if (t==v[k].p){
			trobat = true;
			m = v[k];
		} 

		else if (not trobat)  ++k;
	}

	pair<int,bool> final = make_pair (m.n,m.l);

	return final;
}


void mostraoperador (stack<token> s){
/*Pre: Pila de operadors no buida. */
/*Post: Res. */

	//INV : pila de tokens.
	//HF : A cada iteració la pila es fa més petita.
	while (not s.empty()){
		token t = s.top();
		cout << t << " ";
		s.pop();
	}

}

void mostraarbre (stack<arbre<token > > a){
/*Pre: Pila d'arbres d'operadors no buida. */
/*Post: Res. */

	//INV : pila d'arbres de tokens.
	//HF : A cada iteració la pila es fa més petita.
	while (not a.empty()){
		arbre <token> t = a.top();
		cout << t << endl;
		a.pop();
	}
}


arbre<token> llegir_infixa()
/*Pre: Cert */
/*Post: Retorna un arbre a partir d'un token en recorregut inordre . */
{

	stack<token> s;
	stack<arbre<token > > a;
	token t;
	cin >> t;
	//INV: Token t no és "->"
	while (t!="->"){

		if (t=="("){
			s.push(t);

		}

		else if (t==")") {

			token p = s.top();
			s.pop();
			//INV: p conté els símbols de l'expressió
			while (p!="(") {
				
				if (p.es_operador_unari()){
					arbre<token> fe = a.top();
					a.pop();
					arbre<token> ar (p,fe,arbre<token>());
					a.push(ar);
				}

				else if (p.es_operador_binari()){
					arbre<token> fd = a.top();
					a.pop();
					arbre<token> fe = a.top();
					a.pop();
					arbre<token> ar (p,fe,fd);
					a.push(ar);
				}

				p = s.top();
				s.pop();
			}

		}

		else if (t.es_enter() or t.es_variable() or t.es_boolea()){
			arbre<token> ar (t);
			a.push(ar);
		}

		else {

			pair <int,bool> m = getPrioritat(t);			
				
				//INV: s conté simbols de l'expressió, el token té prioritat inferior al token 'TOP' de la pila o és igual i a més l'associativitat és esquerra a dreta
				while (not s.empty() and ((m.first < getPrioritat(s.top()).first) or (m.first == getPrioritat(s.top()).first and m.second))) {
						
					
					token p = s.top();
					s.pop();

					if (p.es_operador_unari()){
						arbre<token> fe = a.top();
						a.pop();
						arbre<token> ar (p,fe,arbre<token>());
						a.push(ar);
					}

					else if (p.es_operador_binari()){
						arbre<token> fd = a.top();
						a.pop();
						arbre<token> fe = a.top();
						a.pop();
						arbre<token> ar (p,fe,fd);
						a.push(ar);
					}			

				}
			

			s.push(t);
			
		}

		cin >> t;

	}

	//INV: s conté simbols de l'expressió
	while (not s.empty()){
		token t = s.top();
		s.pop();

		if (t.es_operador_unari()){
			arbre<token> fe = a.top();
			a.pop();
			arbre<token> ar (t,fe,arbre<token>());
			a.push(ar);
		}

		else if (t.es_operador_binari()){
			arbre<token> fd = a.top();
			a.pop();
			arbre<token> fe = a.top();
			a.pop();
			arbre<token> ar (t,fe,fd);
			a.push(ar);
		}
	}

	return a.top();
}


bool equivalents (arbre<token> a, arbre<token> b)
//Pre: Els arbres han de ser de la mateixa mida
//Post: Donats dos arbres, diu si corresponen a expressions
//		equivalents aplicant exclusivament la propietat commutativa.
{
	
	bool ho_es=true;

	if (a.es_buit() xor b.es_buit()) ho_es = false;
	else if (a.es_buit() and b.es_buit()) ho_es = true;
	else if (a.arrel()!=b.arrel()) ho_es = false;
	else if (not a.arrel().es_operador_commutatiu()){
		//FF: següent crida a i b són més petits ja que reben fills drets / esquerres.
		//HI: arbre a arrel no és operador commutatiu, la crida recursiva tindrà un arbre més petit.
		ho_es = (equivalents(a.fe(),b.fe()) and equivalents(a.fd(),b.fd())); 
	}
	else if (a.arrel().es_operador_commutatiu()){
		//FF: següent crida a i b són més petits ja que reben fills drets / esquerres.
		//HI: arbre a arrel és operador commutatiu, la crida recursiva tindrà un arbre més petit.
		ho_es = (equivalents(a.fe(),b.fe()) and equivalents(a.fd(),b.fd())) or (equivalents(a.fe(),b.fd()) and equivalents(a.fd(),b.fe()));
	}

	return ho_es;

}


arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2)
//PRE: Arbres amb expressions ja simplificades.
//POST: Si l'operador es de comparació, simplifica la expressió sino retorna un arbre sense simplificar.
{

	arbre<token> r;

	if (op=="==") {
		
		if (equivalents(b1,b2)) {
			r = arbre<token>(token(true));

		}else if(b1.arrel().es_enter() and b2.arrel().es_enter()) {

			if (b1.arrel().to_int()==b2.arrel().to_int()) {
				r = arbre<token>(token(true));
			}else{
				r = arbre<token>(token(false));
			}

		}else if(b1.arrel().es_boolea() and b2.arrel().es_boolea()) {

			if (b1.arrel()==b2.arrel()) {
				r = arbre<token>(token(true));
			}else{
				r = arbre<token>(token(false));
			}
		}

		else if (b1.arrel().es_variable() and b2.arrel().es_variable()) {

			if (b1.arrel()==b2.arrel()){
				r = arbre<token> (token(true));
			}
			else r = arbre<token> (token(false));
		}


		else r = arbre<token> (op,b1,b2);
		
	}

	else if (op=="!=") {

		if (equivalents(b1,b2)) {
			r = arbre<token>(token(false));

		}else if(b1.arrel().es_enter() and b2.arrel().es_enter()) {

			if (b1.arrel().to_int()!=b2.arrel().to_int()) {
				r = arbre<token>(token(true));
			}else{
				r = arbre<token>(token(false));
			}

		}else if(b1.arrel().es_boolea() and b2.arrel().es_boolea()) {

			if (b1.arrel()!=b2.arrel()) {
				r = arbre<token>(token(true));
			}else{
				r = arbre<token>(token(false));
			}
		}

		else if (b1.arrel().es_variable() and b2.arrel().es_variable()) {
			if (b1.arrel()!=b2.arrel()){
				r = arbre<token> (token(true));
			}
			else r = arbre<token> (token(false));
		}

		else r = arbre<token> (op,b1,b2);

	}

	return r;
}


arbre<token> simplificar_operador_unari (token op, arbre<token> b)
//PRE: Arbre amb expressió ja simplificat.
//POST: Si l'arbre es una expressió amb operador unari el simplifica sino el retorna sense simplificar.
{
	
	arbre<token> ar;

	if (not b.es_buit()){

		if (b.arrel().es_operador_unari() and not b.fe().es_buit()) {
				ar = b.fe();
		}
		else if (b.arrel().es_boolea()) {
			ar = arbre<token>(not (b.arrel().to_bool()) );
		}

		else ar = arbre<token>(op,b,arbre<token>());
	}

	return ar;
}


arbre<token> simplificar_operador_boolea(token op,arbre<token> b1,arbre<token> b2)
//PRE: Arbres amb expressions ja simplificades.
//POST: Si l'operador es booleà, simplifica la expressió sino retorna un arbre sense simplificar.
{
	arbre<token> ar;

	if (op=="or"){
	
		if (b1.arrel().es_boolea() and b2.arrel().es_boolea()) { 

			token t(b1.arrel().to_bool() or b2.arrel().to_bool());
			ar = arbre<token> (t);

		}
		else if (b1.arrel().es_boolea()) {

			if (b1.arrel().to_bool()) {
				ar = arbre<token>(true);
			}else{
				ar = b2;
			}
			
		}

		else if (b2.arrel().es_boolea()) {

			if (b2.arrel().to_bool()) {
				ar = arbre<token>(true);
			}else{
				ar = b1;
			}
			
		}

		else if (equivalents(b1,b2)) ar = b2;

		else {

			ar = arbre<token> (op,b1,b2);
		}
		

	}			

	else if (op=="and"){
			
		if (b1.arrel().es_boolea() and b2.arrel().es_boolea()) {

			token t(b1.arrel().to_bool() and b2.arrel().to_bool());
			ar = arbre<token> (t);
		}

		else if (b1.arrel().es_boolea()) {

			if (b1.arrel().to_bool()) {
				ar = b2;
			}else{
				ar = arbre<token>(token(false));
			}
			
		}
		else if (b2.arrel().es_boolea()) {

			if (b2.arrel().to_bool()) {
				ar = b1;
			}else{
				ar = arbre<token>(token(false));
			}
			
		}

		else if (equivalents(b1,b2)) ar = b2;

		else {

			ar = arbre<token> (op,b1,b2);
		}

	}

	else ar = arbre<token>(op,b1,b2);

	return ar;

}


arbre<token> simplificar_operador_aritmetic(token op,arbre<token> b1,arbre<token> b2)
//PRE: Arbres amb expressions ja simplificades.
//POST: Si l'operador es aritmetic, simplifica la expressió sino retorna un arbre sense simplificar.
{

	arbre<token> ar;

	token t = 0;


	if (op=="*"){

		if (b1.arrel()=="1") ar = b2;
		else if (b2.arrel()=="1") ar = b1;
		else if (b1.arrel()=="0") ar = arbre<token>(t);
		else if (b2.arrel()=="0") ar = arbre<token>(t);
		else if (b1.arrel().es_enter() and b2.arrel().es_enter()) {
			
			int p = b1.arrel().to_int();
			int s = b2.arrel().to_int();
			int res = p*s;
			
			token def (res);
			ar = arbre<token> (def);
		}

		else ar = arbre<token> (op,b1,b2);
	}

	else if (op=="+"){

		if (b1.arrel()=="0") ar = b2;
		else if (b2.arrel()=="0") ar = b1;
		else if (b1.arrel().es_enter() and b2.arrel().es_enter()){
			int p = b1.arrel().to_int();
			int s = b2.arrel().to_int();
			int res = p+s;
			token def (res);
			ar = arbre<token>(def);
		}

		else ar = arbre<token> (op,b1,b2);
	}

	else if (op=="-") {

		if (b2.arrel()=="0") ar = b1;
		else if (equivalents(b1,b2)) ar = arbre<token> (t);		
		else if (b1.arrel().es_enter() and b2.arrel().es_enter()) {
			int p = b1.arrel().to_int();
			int s = b2.arrel().to_int();
			int res = p-s;
			token def (res);
			ar = arbre<token> (def);
		}

		else ar = arbre<token> (op,b1,b2);
	}

	else if (op=="/") {

		if (b1.arrel()=="0"){
			ar = arbre<token> (t);
		}
		else if (b2.arrel()=="1"){
			ar = b1;
		}
		else if (equivalents(b1,b2)){
			token t = 1;
			ar = arbre<token> (t);
		}
		else if (b1.arrel().es_enter() and b2.arrel().es_enter()) {

			int p = b1.arrel().to_int();
			int s = b2.arrel().to_int();
			int res = p/s;
			token def (res);
			ar = arbre<token> (def);
		}
		else ar = arbre<token> (op,b1,b2);
	}

	else if (op=="**"){

		if (b1.arrel()=="0") {
			ar = arbre<token> (t);
		}
		else if (b1.arrel()=="1") {
			token r = 1;
			ar = arbre<token> (r);
		}
		else if (b2.arrel()=="0") {
			token r = 1;
			ar = arbre<token> (r);
		}
		else if (b2.arrel()=="1") {
			ar = arbre<token> (b1.arrel());
		}

		else if (b1.arrel().es_enter() and b2.arrel().es_enter()){
			int p = b1.arrel().to_int();
			int s = b2.arrel().to_int();
			int res = pow(p,s);
			token def (res);
			ar = arbre<token>(def);
		}
		else ar = arbre<token> (op,b1,b2);
	}
	
	return ar;	
}


arbre<token> simplificar(arbre<token> a) 
//PRE: Arbre amb expressió sense simplificar
//POST: Simplifica l'arbre tot el que pot
{ 

	arbre<token> ar = a;
	arbre<token> fe ;
	arbre<token> fd ;

	if (not a.es_buit() and not a.es_fulla()) {

	 	if (not a.fd().es_buit()) fd = simplificar(a.fd());
	 	/*HI: fd serà arbre a, si fill dret d'a no és buit. */
    	/*FF: A cada crida recursiva l'arbre es va desglossant fins a quedar buit.*/

	 	if (not a.fe().es_buit()) fe = simplificar(a.fe());
	 	/*HI: fe serà arbre a, si fill esquerra d'a no és buit. */
   		/*FF: A cada crida recursiva l'arbre es va desglossant fins a quedar buit.*/
		
		if (a.arrel().es_operador_binari()) {
			if (a.arrel()=="==" or a.arrel()=="!="){
				ar = simplificar_operador_comparacio(a.arrel(),fe,fd);
			}

			else if (a.arrel()=="*" or a.arrel()=="+" or a.arrel()=="-" or a.arrel()=="/" or a.arrel()=="**") {
				ar = simplificar_operador_aritmetic(a.arrel(),fe,fd);
			}

			else ar = simplificar_operador_boolea(a.arrel(),fe,fd);
		}

		else if (a.arrel().es_operador_unari()) {
			ar = simplificar_operador_unari(a.arrel(),fe);
		}

	else ar = arbre<token> (a.arrel(),fe,fd);

	

	}

	return ar;
}


int main(){

	string s;
	//Inv: Mentre hi hagi flux de dades cap a s.
	while (cin >> s){
		arbre<token> final;
		token fin;
		if (s=="PREFIXA"){
			final = LlegirPrefixa();
			cin.ignore(256,'>');
		}

		else if (s=="POSTFIXA")	final = LlegirPostfixa();

		else if (s=="INFIXA") final = llegir_infixa();
		

		final = simplificar(final);

		cin >> s;

		if (s=="PREFIXA") fin = ExpressioPrefixa(final);		


		else if (s=="POSTFIXA") fin = ExpressioPostfixa(final);		

		else fin = ExpressioInfixa(final);

		cout<< fin << endl;
	}
	
}