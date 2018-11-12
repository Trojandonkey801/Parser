#include <iostream>
#include <cstdlib>
using namespace std;
struct node{
 node* next;
 int data;
};
node *blank = new node;
class tester{
	public:
	string myname;
	void printname(){
		cout<<"my name is"<<myname;
	}
};
//pops the next element in line
void pop(node* topop){
	cout<<"it popped";
	node* toppend = next->next;
	topop->next = topop->next->next;
}
void printer(node* tostart){
	node* toprint=tostart;	
	while(toprint->next!= blank){
		cout<<toprint->data<<endl;
		toprint = toprint->next;
	}
}
int main(){
	node* root = new node;
	node* first = new node;
	root->next = first; 
	root->data = 5;
	first->data = 5;
	node* toadd;
	toadd = first;
	for (int i = 0; i < 10; i++) {
		node* temp = new node;	
		toadd->next = temp;
		toadd->data = rand()%10;
		toadd = temp;	
	}
	printer(root);
	pop(root);
	cout<<"break"<<endl;
	printer(root);
}

