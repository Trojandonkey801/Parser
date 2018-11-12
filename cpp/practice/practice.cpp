#include <iostream>
using namespace std;

int main(){
	char* ex1;	
	char** ex2 = &ex1;
	char foo = 'a';	
	int bar = 97;
	int foobar = 72;
	ex1 = &foo;
	cout << *ex1 << endl;
	cout << **ex2 << endl;
	int var[5] = {1,4,5,6,7};
	int* ptr[5];
	ptr[0] = &bar;
	ptr[1] = &foobar;
	return 0;
}
