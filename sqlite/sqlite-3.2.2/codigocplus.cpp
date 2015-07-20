extern "C"{
#include "headerc.h"
}
#include<iostream>
using namespace std;
int main()
{
	cout << "Hola en C++" << endl;
	init_sqlite();
	return 0;
}
