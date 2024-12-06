#include <iostream>
using namespace std;
#include "Playfair.h"

int main() {
	Playfair pfair("assasinator", "q/z");
	//asintior
	pfair.makeTable();
	pfair.showTable();
	
	cout<<"최종: "+pfair.makeEncryption("becsrefull");
}