#include <iostream>
using namespace std;

int main(){
	
	try {
		throw 20;		
		
		}
		catch (int e){
			cout << "Error amb nº"<<e<<endl;
			
		}		
		try {
			throw 15;
		
		catch (int t){
			cout << "Error amb nº "<<t<<endl;
		}
	}
	
	}	 
