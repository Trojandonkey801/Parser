#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
bool AND(bool b1, bool b2){
	return b1&b2;	
}

//@param 
// b1: first input bool, 
// b2: second input bool
// expected output is same as NAND
bool NAND(bool b1, bool b2){
	return !AND(b1,b2);
}

bool OR(bool b1, bool b2){
	return b1 | b2;	
}
bool NOR(bool b1, bool b2){
	return !NOR(b1,b2);
}

bool XOR(bool b1,bool b2){
	return((!b1&b2)|(!b2&b1));
}

bool iXOR(bool b1, bool b2){
	return(b1==b2);
}
void trier(){
	int size;
	int max = 2^size;
	cout << "the number of variables" << endl;
	cin>>size;



}
string boolconv(int i1){
	double maxsize = log2(i1);
	cout << "enter number to calc" << endl;
	int tocalc;
	cin >> tocalc;
	int maxparam = (int)maxsize;
	cout << maxparam << endl;
	string toreturn = "";
	for (int i = 0; i <maxparam; i++){
		int tosub = 2^(maxparam-i-1);
		bool subbed = false;
		if(tocalc > tosub){
			tocalc -= tosub;	
			subbed = true;
		}	
		if subbed : toreturn.append("1") ? toreturn.append("0");
		cout << toreturn << endl;
	}
	return toreturn;
}
void initializer(){
	
}
int main(){
	cout <<"printed" <<boolconv(71) << endl;
	return 0;	
}

