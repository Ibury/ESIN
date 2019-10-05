#include <iostream>
#include "huffman.hpp"
using namespace std;

int main() {

	vector<nat> seq;
	vector<string> codis;

	seq.push_back(1);
	seq.push_back(2);
	seq.push_back(3);
	seq.push_back(4);
	seq.push_back(4);

	huffman::codi_huffman(seq,codis);

	for (unsigned int i=0; i<codis.size(); ++i) {
		cout << codis[i] << " ";
	}

	cout << endl;
}