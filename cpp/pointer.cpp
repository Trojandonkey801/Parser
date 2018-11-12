#include <iostream>
using namespace std;
int main(){
	int holder = 10; //regular initialization of an integer
	/*
	the int* means that it is a POINTER to an INTEGER. int* IS NOT A DATA TYPE. & is a dereferencer that means refer to the MEMORY LOCATION of the variable.
	the * is used in 2 ways. with a declaration to show that the NAME "pointhold" is a POINTER. It is also used to REFERENCE the DATA at a memory location.(looking inside the box of the memory address)	
	*/
	int* pointhold = &holder;
	// the pointer to an array is the pointer to the first index of the array 
	int foo[5];
	//the refence to an array by default is the memory location.
	if(foo == &foo[0])	
		cout<<"this is true";
	//type g++ "yourfilenamehere".cpp to compile and ./"yourfilecompiled".out 
	//so this file for me inside vim is :! g++ pointer.cpp && ./a.out
	return 0;
}
