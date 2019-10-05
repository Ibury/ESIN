#include "conjunt.hpp"
#include <iostream>
using namespace std;



int main(){
error e (10,"NoMinMaxEnConjBuit","No hi ha minim/max");
conjunt<int> a;
cout<<e<<endl;

try{
    if (a.card()==0) throw error (e);
}
catch (error){


   e.print(cout);

 }

//cout<<a.max()<<endl;
}
