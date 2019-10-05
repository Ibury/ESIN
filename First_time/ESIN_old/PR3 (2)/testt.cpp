// erasing from vector
#include <iostream>
#include <vector>
using namespace std;

int main ()
{
  vector<int> v(12);

  v[0] = 12;
  v[1] = 3;
  v[2] = 22;
  v[3] = 8;
  v[4] = 1;
  v[5] = 17;
  v[6] = 16;
  v[7] = 10;
  v[8] = 2;
  v[9] = 31;
  v[10] = 26;
  v[11] = 11;

  cout << "Secuencia: ";
  for (int i=0; i<v.size(); ++i) {
    for (int j=0; j<v[i]; ++j) {
      cout << (i+1);
    }
  }
  cout << endl;



 int suma=0;
  for (int i=0; i<v.size(); ++i) {
    for (int j=0; j<v[i]; ++j) {
      suma+=v[i];
    }
  }

 cout << "Instrucciones: " << endl;
 cout << "init s" << suma << "E vector<nat>" << endl;

  for (int i=0; i<v.size(); ++i) {
    for (int j=0; j<v[i]; ++j) {
      cout << "insereix_v " << (i+1) << endl;
    }
  }
  cout << "huffman s" << suma << "E" << endl;

}