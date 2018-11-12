#include <iostream>
using namespace std;
struct node{
 node *next;
 int data;
};
int main(){
	node *root;
	root = new node;
	root->next = 0;
	node* first = new node;
	root->next = first;
	first->data =5;
	cout<<root->next->data;
	node *toadd = root;
	for (int i = 0; i < 10; i++) {
		node *d = new node;
		toadd->next = d;	
		toadd = d;	
	}
	node *toprint;
	toprint = root;
	for (int i = 0; i < 2; i++) {
		cout<<toprint->next;	
		toprint = toprint->next;
	}
	
	return 0;
}
