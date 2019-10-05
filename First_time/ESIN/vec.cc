#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<int> v(10);
	for (unsigned int i = 0 ; i < v.size();++i){
		v[i] = i;
	}

	

	try{
		for (unsigned int i = 0; i < 20; ++i){
			if (std::range_error) throw;
			cout << "VALOR : "<<v[i]<<" ";
		}
	}
	catch(std::range_error){ cout << "ERROR TETE "<<endl;}
}