#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
using namespace std;

bool test(string var) {
	unsigned int i=0;

	bool es_var = true;
	while (i<var.size() and es_var) {

		if (not((var[i]>='a' or var[i]<='z') and (var[i]>='A' or var[i]<='Z'))) {
			
			if (var[i]!='_') {
				es_var = false;
			}
		}
		++i;
	}

	return es_var;
}

int main() {

	string s;

	while(cin >> s) {
		cout << s << " --> "<< (test(s) ? " cumple" : " no cumple") << endl;
	}

	enum LALA {AA, BB, ZZ};

	LALA p = ZZ;

	if (p == BB) {
		cout << "SI" << endl;
	}else{
		cout << "NO" << endl;
	
	}

}