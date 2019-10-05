#include <iostream>
using namespace std;


double funcio_2 (double x, int n) {
if (n==0) {
return 1;
} else if (n%2==0) {
double y = funcio_2(x,n/2);
return y * y;
} else {
double y = funcio_2(x,n/2);
return y * y * x;
} }


int main(){

double x;
cin >> x;
int n;
cin >> n;
double resultat = funcio_2(x,n);
cout << resultat << endl;
	
}