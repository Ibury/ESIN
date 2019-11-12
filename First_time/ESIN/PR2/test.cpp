#include "conjunt.hpp"
using namespace std;

int main() {
	conjunt<int> cj;
	cj.insereix(4);
	cj.insereix(6);
	cj.insereix(10);
	cj.insereix(8);
	cj.insereix(64);
	cj.insereix(36);

	cj.print(cout);
	cout << endl;


	conjunt<int> cj2;

	cj2.insereix(9);
	cj2.insereix(2);
	cj2.insereix(4);
	cj2.insereix(16);
	cj2.insereix(36);
	cj2.insereix(1);

	cj2.print(cout);
	cout << endl;

	cj.intersectar(cj2);

	cj.print(cout);
	cout << endl;

	cj.unir(cj2);

	cj.print(cout);
	cout << endl;

	cj.restar(cj2);

	cj.print(cout);
	cout << endl;


}