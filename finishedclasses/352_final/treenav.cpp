/**
 * This file is designed to navigate the tree
 */
#include "treenav.h"
/**
 * Gets the parent of the current node
 * @param node_t *current 
 * 		The node of which the parent is desired
 */
node_t *get_parent(node_t *current){
	return current->parent;
}

/**
 * Gets the uncle of the current node.
 * If it has no grandfather node, it returns nil
 * @param node_t *current 
 * 		The node of which the parent is desired
 */
node_t *get_uncle(node_t *current){
	if(get_grandf(current) == NIL){
		return NIL;
	}
	else{
		if(get_grandf(current)->left == get_parent(current))
			return get_grandf(current)->right;
		else
			return get_grandf(current)->left;
	}
}

/** 
 * Checks whether if this node is the left node of its parent
 * NEED TO CHECK IF PARENT IS NOT NILL OUTSIDE CALL 
 * @param node_t *current
 * 		The node to check
 */
bool is_left(node_t *current){
	if(current->parent != NIL){
		if(current->parent->left == current)
			return true;
		else
			return false;
	}
	return false;
}

/**
 * Gets the left child of this node
 * @param node_t *current
 * 		the node passed in.
 */
node_t *get_left(node_t *current){
	if(current->left != NULL && current->left != NIL)
		return current->left;
	return NIL;
}

/**
 * Gets the right child of this node
 * @param node_t *current
 * 		the node passed in.
 */
node_t *get_right(node_t *current){
	if(current->right != NULL && current->right != NIL)
		return current->right;
	return NIL;
}


node_t *get_grandf(node_t *current){
	if(get_parent(current) != NIL && get_parent(get_parent(current)))
		return current->parent->parent;
	return NIL;
}

/**
 * Gets the grandfather of this node
 * @param node_t *current
 * 		the node passed in.
 */
int get_color(node_t *current){
	if(current == NIL)
		return BLACK;
	else
		return RED;
}

/**
 * Helper function to set the color of a node.
 * I don't know why this exists
 * @param node_t *current
 * 		node to change color
 * @param int color_in
 * 		the color to set
 */
void set_color(node_t *current,int color_in){
	if(current != nullptr && current != NIL)
		current->color = color_in;
}

/**
 * Helper function to replace a node with another
 * @param node_t *toreplace
 * 		The node to be replaced
 * @param node_t *with
 * 		The node to replace with
 *
 */
void replace(node_t *toreplace, node_t *with){
	link(get_parent(toreplace),with,is_left(toreplace));
	free(toreplace);
}

/**
 * Clean delete of a node.
 * @param node_t *todelete
 * 		the node to pass in and delete
 */
void delete_node(node_t *todelete){
	if(get_parent(todelete) != NIL){
		if(is_left(todelete)){
			get_parent(todelete)->left = NIL;
		}else{
			get_parent(todelete)->right = NIL;
		}
	}
	free(todelete);
}

/**
 * Helper function to swap two nodes
 * @param node_t *first
 * 		the first node to swap
 * @param node_t *second
 * 		The second node to swap
 *
 */
void swap(node_t *first, node_t *second){
	int key = first->key;
	int color = first->color;
	first->key = second->key;
	first->color = second->color;
	second->key = key;
	second->color = color;
}

/**
 * link the node of the parent to the child.
 * If the child is NIL, do not set the parent of the child as the parent,
 * as the NIL is one node.
 * @param node_t *parent
 * 		The parent node to link
 * @param parent node_t * child
 * 		The child node to link
 * @param bool is_left
 * 		If this current node is the left of the parent
 *
 */
void link(node_t *parent, node_t *child,bool is_left){
	if(is_left){
		parent->left = child;
		if(child != NIL)
			child->parent = parent;
	}
	else{
		parent->right = child;
		if(child != NIL)
			child->parent = parent;
	}
}

bool succ = false;
/**
 * Assume has 2 children
 * Find the successor of this node;
 */
node_t *find_succ(node_t *tofind,bool succ){
	if(tofind->left != NIL){
		return recurse(tofind->left,false);
	}
	else{
		return recurse(tofind->right,true);
	}
}

/**
 * returns the sibling of this node
 * @param node_t *current
 * 		the node to pass in
 */
node_t *get_sibling(node_t *current){
	if(current->parent == NIL){
		return NULL;
	}
	else{
		if(is_left(current))
			return get_right(current->parent);
		else
			return get_left(current->parent);
	}
}

/**
 * Helper function for finding the successor/predecessor
 * @param node_t *current
 * 		The node from which to find the child
 * @parm bool is_left
 * 		Whether to find the left or right child
 */
node_t *recurse(node_t *current, bool is_left){
	if(is_left){
		if(current->left == NIL)
			return current;
		else
			return recurse(current->left,is_left);
	}
	else{
		if(current->right == NIL)
			return current;
		else
			return recurse(current->right,is_left);
	}
}
/**
 * Helper function that counts if the current tree is correct
 * @param node_t *head
 * 		current node
 * @param int current
 * 		internal variable used for recursion
 */
int val = -1;
bool correctness(node_t *head,int current){
	
	if(head != NIL){
		if(head->color == BLACK){
			bool one = correctness(head->right,current+1);
			bool two = correctness(head->left,current+1);
			return one && two;
		}
		else{
			bool one = correctness(head->right,current);
			bool two = correctness(head->left,current);
			return one && two;
		}
	}
	else{
		if(val == -1){
			val = current;
		}
		else{
			if(val != current){
				return false;
			}
			else{
				return true;
			}
		}
	}
	return true;
}
