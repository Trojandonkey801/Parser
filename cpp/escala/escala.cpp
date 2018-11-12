#include <iostream>
using namespace std;
string escala(int ia[]){
	bool escala = true;
		for (int i = 0; i <sizeof(*ia)-1; i++) {
			if(ia[i]+1 != ia[i+1])
				escala = false;
		}
	if(escala)
		return "Y";
	return "N";
} 
int main(){
	int total[5] = {1,2,2,4,5};
	cout<<escala(total);
	return 0;
}
