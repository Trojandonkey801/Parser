/**
 * This file provides the set of functions to create and modify their redblack tree
 * This includes inserting, deleting, searching, printing, rotating
 * In the process of deletion, the functions have to additionally
 * pass in the parents and left right, as the NIL node is only one node.
 * Therefore, it cannot have a parent.
 * Therefore, the parents and children have to always be accomodated
 *
 */
#include "red_black.h"
#define COUNT 5
#define TESTVAL 90
#include <cstring>
stringstream buffer;
int size = 0;
node_t *NIL;
node_t* head = NIL;
int tempval;
/**
 * This function provides the basic functionality to search the bst
 * Since it does not matter whether it is a red black tree, it
 * conducts search like a normal bst
 * @param int value
 * 		this value is the value that will be searched in the tree
 */
bool search(int value){
	node_t *current = head;
	while(true){
		int currkey = current->key;
		if(value == currkey)
			return true;
		else if(value < currkey){
			if(current->left == NIL)
				return false;
			current = current->left;
		}
		else{
			if(current->right == NIL)
				return false;
			current = current->right;
		}
	}
	return false;
}

/**
 * This function provides a functionality similar to the other search.
 * However, it returns a pointer to a node instead
 * If there is no such node, it returns NIL.
 * @param int value
 * 		The value to search for
 * @return node_t *
 * 		The node that carries the value that we are searching for.
 * 		If no such node exists, return a NIL node
 */
node_t *search_node(int value){
	node_t *current = head;
	if(current == NIL || current == NULL)
		return NIL;
	while(true){
		int currkey = current->key;
		if(value == currkey)
			return current;
		else if(value < currkey){
			if(current->left == NIL)
				return NIL;
			current = current->left;
		}
		else{
			if(current->right == NIL)
				return NIL;
			current = current->right;
		}
	}
	return NIL;
}

/**
 * The function that balances after bst insertion
 * This follows closely the wikipedia page on red black trees
 * @param node_t *inserted
 * 		The node that is to be balanced after insertion
 */
void balance(node_t *inserted){
	//CASE 1
	if(inserted == head){
		inserted->color = BLACK;
	}
	//CASE 2
	else if(get_parent(inserted)->color == BLACK){
		//DONOTHING
	}
	//CASE 3
	else if(get_parent(inserted)->color == RED 
			&& get_uncle(inserted)->color == RED){
		get_parent(inserted)->color = BLACK;
		get_uncle(inserted)->color = BLACK;
		get_grandf(inserted)->color = RED;
		balance(get_grandf(inserted));
	}
	//CASE 4
	else if(get_parent(inserted)->color == RED
			&& get_uncle(inserted)->color == BLACK){
		if(get_grandf(inserted)->left != NIL &&
				get_grandf(inserted)->left->right == inserted){
			rotate_left(get_parent(inserted));
			inserted = inserted->left;
		}
		else if(get_grandf(inserted)->right != NIL && 
				get_grandf(inserted)->right->left == inserted){
			rotate_right(get_parent(inserted));
			inserted = inserted->right;
		}
		node_t *g = get_grandf(inserted);
		node_t *p = get_parent(inserted);
		if(inserted == p->left){
			rotate_right(g);
		}else{
			rotate_left(g);
		}
		p->color = BLACK;
		g->color = RED;
	}
}


bool l_r = false;
/**
 * A wrapper function for delete_in_bst, in order
 * to allow for the function pointers to accomodate
 * @param int todelete
 * 		The integer value to delete
 */
void del_from_tree(int todelete){
	node_t *todel = search_node(todelete);
	if(todel != NULL && todel != NIL){
		delete_in_bst(todel);
	}
}

/**
 * The actual function that deletes values from the red black tree
 * This functions by deleting as it normally would.
 * It then rebalances.
 * This heavily takes after wikipedia's red black tree algorithms
 *
 */
void delete_in_bst(node_t *n){
	//First, set it up so that n has at most one node child
	node_t *todel = n;
	node_t *child;
	node_t *parent;
	bool le_ri = false; //right is false, left is true.
	if(n->right != NIL && n->left != NIL){
		node_t *succ = find_succ(n,l_r);//successor for node.
		parent = succ->parent;
		le_ri  = is_left(succ);
		int temp = succ->key;
		succ->key = n->key;
		n->key = temp;
		// This retains the R_B property
		// Now, delete the child from which the value 
		// was pulled.
		todel = succ; //Set the node succ to be deleted.
	}
	//print2D(head);
	le_ri = is_left(todel);
	if(todel->right != NIL){//If only the right child is not NIL
		parent = todel->parent;
		link(parent,todel->right,is_left(todel)); // link todel to its right child
		child = todel->right;
	}else{//If only the left child is not NIL, or both NIL
		parent = todel->parent;
		link(parent,todel->left,is_left(todel)); // link todel to its left child
		child = todel->left;
	}
	//print2D(head);
	if(todel->color == BLACK){
		if(child->color == RED)
			child->color = BLACK;
		else{
			Delete1(child,parent,le_ri);
		}
	}
	//free(todel);
}
/**
 * Case 1 in rebalancing deletion.
 * If the node is root, just exit.
 * Otherwise, pass onto case 2
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete1(node_t *n, node_t *parent,bool le_ri){
	if(parent != NIL && parent != NULL){
		Delete2(n,parent,le_ri);
	}
}

/**
 * Case 2 in rebalancing deletion.
 * When the color of the sibling is red, and the parent and the node are black
 * The sibling becomes the black parent, and the parent becomes red
 * and then it becomes rotated
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete2(node_t *n, node_t *parent,bool le_ri){
	node_t *s = parent->left;
	if(le_ri)
		s = parent->right;
	if (s->color == RED) {
		parent->color = RED;
		s->color = BLACK;
		//print2D(head);
		if (is_left(n)) { //When n is the left child, rotate left
			rotate_left_parent(parent);
		} else { // Else, rotate right
			rotate_right_parent(parent);
		}
	}
	//Pass onto deletion 3.
	Delete3(n, parent, le_ri);
}
/**
 * Case 3 in rebalancing deletion.
 * When the parent is black, and the children of the red sibling are black.
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete3(node_t *n, node_t *parent,bool le_ri){
	node_t *s = parent->left;
	if(le_ri)
		s = parent->right;
	if ((parent->color == BLACK) && (s->color == BLACK) &&
			(s->left->color == BLACK) && (s->right->color == BLACK)) {
		s->color = RED;
		Delete1(parent,parent->parent,is_left(parent));
	} else 
		Delete4(n,parent,le_ri);
}
/**
 * Case 4 in rebalancing deletion.
 * When S and S's children are black, but the parent is red.
 * Then exchange S and P color, and then continue
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete4(node_t *n, node_t *parent,bool le_ri){
	node_t *s = parent->left;
	if(le_ri)
		s = parent->right;
	if ((parent->color == RED) && (s->color == BLACK) &&
			(s->left->color == BLACK) && (s->right->color == BLACK)) {
		s->color = RED;
		parent->color = BLACK;
	} else {
		Delete5(n,parent,le_ri);
	}
}

/**
 * Case 5 in rebalancing deletion.
 * When the sibling is black, has a left red child, and a right black child.
 * Additionally, when N is the let child.
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete5(node_t *n, node_t *parent,bool le_ri){
	node_t *s = parent->left;
	if(le_ri)
		s = parent->right;
	if (s->color == BLACK) {
		if ((n == parent->left) && (s->right->color == BLACK) &&
				(s->left->color == RED)) {
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(s);
		} else if ((n == parent->right) && (s->left->color == BLACK) &&
				(s->right->color == RED)) {
			s->color = RED;
			s->right->color = BLACK;
			rotate_left(s);
		}
	}
	Delete6(n,parent,le_ri);

}

/**
 * Case 6 in rebalancing deletion.
 * When the sibling is black, the the sibling has a right red child, and n 
 * is the left child of the parent. We can then rotate around P.
 * @param node_t *n
 * 		The node to balance around
 * @param node_t *parent
 * 		The parent of the balanced node
 * @param bool le_ri
 * 		The left or right of the node, based on the parent
 */
void Delete6(node_t* n, node_t *parent, bool le_ri) {
	node_t *s = parent->left;
	if(le_ri)
		s = parent->right;

	s->color = parent->color;
	parent->color = BLACK;

	if (n == parent->left) {
		s->right->color = BLACK;
		rotate_left(parent);
	} else {
		s->left->color = BLACK;
		rotate_right(parent);
	}
}

/**
 * Rotate right helper function
 * @param node_t *n
 * 		The node aroudn which rotation will occur
 */
void rotate_right(node_t *n){
	bool ishead = false;
	bool right_left = false;
	node_t *parent;
	node_t *left_node = n->left;
	node_t *child = get_right(left_node);
	if(n == head)
		ishead = true;
	else{
		parent = get_parent(n);
		if(parent-> left == n)
			right_left = true;
	}
	if(left_node != NIL || left_node != NULL)
		child = get_right(left_node);
	left_node->right = n;
	n->parent = left_node;
	n->left = child;
	child->parent = n;
	if(ishead){
		if(left_node != NIL)
			left_node->parent = NIL;
		head = left_node;
	}
	else{
		if(left_node != NIL)
			left_node->parent = parent;
		if(right_left)
			parent->left = left_node;
		else
			parent->right = left_node;
	}
}
/**
 * A helper function to rotate left based around the parent.
 * This is useful because when we are rotating around NIL, 
 * we lose the reference to the parent because NIL does not have a parent.
 * @param node_t *n
 * 		The parent node to rotate around
 */
//Used when passing in the parent
void rotate_left_parent(node_t *n){
	bool is_head;
	node_t *gpa;
	node_t *right = n->right;
	bool left = true;
	if(n == head)
		is_head = true;
	else{
		is_head = false;
		gpa = n->parent;
		left = is_left(n);
	}
	node_t *temp = n->right->left;
	link(n->right,n,true);
	link(n,temp,false);
	if(is_head)
		head = right;
	else{
		link(gpa,right,left);
	}
}
/**
 * A helper function to rotate right based around the parent.
 * This is useful because when we are rotating around NIL, 
 * we lose the reference to the parent because NIL does not have a parent.
 * @param node_t *n
 * 		The parent node to rotate around
 */
//Used when passing in the parent
void rotate_right_parent(node_t *n){
	bool is_head;
	node_t *gpa;
	node_t *left = n->left;
	bool right = true;
	if(n == head)
		is_head = true;
	else{
		is_head = false;
		gpa = n->parent;
		right = !is_left(n);
	}
	node_t *temp = n->left->right;
	link(n->left,n,true);
	link(n,temp,false);
	link(n,temp,false);
	if(is_head)
		head = left;
	else{
		link(gpa,left,right);
	}
}
/**
 * Rotate left helper function
 * @param node_t *n
 * 		The node aroudn which rotation will occur
 */
void rotate_left(node_t *n){
	bool ishead = false;
	bool left_right = false;
	node_t *parent;
	node_t *right_node = n->right;
	node_t *child = get_left(right_node);
	if(n == head)
		ishead = true;
	else{
		parent = get_parent(n);
		if(parent-> right == n)
			left_right = true;
	}
	if(right_node != NIL || right_node != NULL)
		child = get_left(right_node);
	right_node->left = n;
	n->parent = right_node;
	n->right = child;
	child->parent = n;
	if(ishead){
		if(right_node != NIL)
			right_node->parent = NIL;
		head = right_node;
	}
	else{
		if(right_node != NIL)
			right_node->parent = parent;
		if(left_right)
			parent->right = right_node;
		else
			parent->left = right_node;
	}
}

/**
 * wrapper function around the int inserter.
 * This instead takes a string, and extracts the int value of the tree
 * @param string s
 *		 The tree value that contains the numerical value
 *
 */
void insert_node(string s){
	insert_node(stoi(s.substr(0,s.length()-1)));
}

int execorder = 0;
/**
 * Function that inserts an integer value into a tree
 * It then has to call the balance function in order to balance the 
 * newly created node
 * @param int value
 * 		The value that we want to insert into the tree
 */
void insert_node(int value) {
	if(head == NIL){
		head = create_node(value,NIL);
		size++;
		balance(head);
	}
	node_t *current = head;
	while(true){
		int currkey = current->key;
		if (value == currkey)
			break;
		else if (value < currkey) {
			if (current->left == NIL) {
				size++;
				current->left = create_node(value,current);
				balance(current->left);
				break;
			} else{
				current = current->left;
			}
		} else if (value > currkey) {
			if (current->right == NIL) {
				size++;
				current->right = create_node(value,current);
				balance(current->right);
				break;
			} else{
				current = current->right;
			}
		}
	}
}

/**
 * helper function that is used to first initialize the tree 
 * that is provided in the text file
 * It is different in that it is aware of the color.
 * @param string in
 * 		The string to parse and insert
 */
node_t *create_hard(string in){
	if(in == "f")
		return NIL;
	else{
		node_t *toreturn = (node_t *)malloc(sizeof(node_t));
		int tempval = stoi(in.substr(0,in.length()-1));
		toreturn->key = tempval;
		toreturn->left = NIL;
		toreturn->right = NIL;
		toreturn->parent = NIL;
		if(in.at(in.length()-1) == 'r')
			toreturn->color = RED;
		else
			toreturn->color = BLACK;
		return toreturn;
	}
}

/**
 * Function that creates a node.
 * It sets left and right children to NIl, sets the parent node.
 *
 */
node_t *create_node(int in_key,node_t *parent_node){
	node_t *toreturn = (node *)malloc(sizeof(node_t));
	toreturn->key = in_key;
	toreturn->left = NIL;
	toreturn->right = NIL;
	toreturn->parent = parent_node;
	toreturn->color = RED;
	return toreturn;
}

/**
 * helper function to compare two node key values
 * if inserting is greater than prev, positive
 * if prev is greater than inserting, negative
 * if equal, 0
 */
int compare(node_t *inserting, node_t *prev){
	if(prev == NIL)
		return 0;
	if(prev == NIL)
		return 0;
	int diff = prev->key - inserting->key;
	if(diff < 0)
		return -1;
	if(diff > 0)
		return 1;
	else
		return 0;
}
int veccount = 0;
/**
 * Helper printer function to initialize the 2d printer util
 * This has nothing to do with the assignment, and it was 
 * copied from some random stackoverflow post.
 * It is not used in the final program, it just makes it easier 
 * to visualize.
 * @param node_t *root
 * 	The root node to start enumerating
 */
void print2D(node_t *root){
	tempval = 0;
	cout << "--------START---------" << endl;
	print2DUtil(root,0);
	cout << "--------END---------" << endl;
}


/**
 * Function that prints out the tree
 * @param node_t *root
 * 		The node to enumerate
 * @param int space
 * 		A value passed in to allow recursion to happen
 */
void print2DUtil(node_t *root, int space)
{
	if (root == NULL)
		return;
	space += COUNT;
	print2DUtil(root->right, space);
	cout<<endl;
	int i = COUNT;
	while(i<space){
		cout<<" ";
		i++;
	}
	cout<<root->key;
	if(root->color == RED)
		cout<<'r'<<endl;
	else
		cout<<'b'<<endl;
	print2DUtil(root->left, space);
}
/*
 * This function recursively enumerates the tree, and clears and frees the nodes
 * @param node_t *root The root node, or the current node to clear.
 *
 */
void clean_tree(node_t *root){
	if(root->right != NIL){
		clean_tree(root->right);
	}
	if(root->left != NIL){
		clean_tree(root->left);
	}
	if(root == head)
		free(head);
	else
		free(root);
}
