/**
 * The header file for red_black.cpp
 *
 */
#include "treenav.h"
using namespace std;
bool search(int value);
void delete_in_bst(node_t *n);
node_t *search_node(int value);
void del_from_tree(int todelete);
void insert_node(int value);
int compare(node_t *inserting, node_t *prev);
node_t *create_node(int in_key,node_t *parent_node);
void insert_node(string s);
void print2DUtil(node_t *root, int space);
void print2D(node_t *root);
void rotate_left(node_t *n);
void rotate_right(node_t *n);
void right_rotate(node_t *n);
void left_rotate(node_t *n);
void delete_node(node_t *n);
void fixInsertRBTree(node_t *ptr) ;
void clean_delete(node_t *deleted, node_t *child);
void Delete1(node_t *node, node_t* parent, bool le_ri);
void Delete2(node_t *node, node_t* parent, bool le_ri);
void Delete3(node_t *node, node_t* parent, bool le_ri);
void Delete4(node_t *node, node_t* parent, bool le_ri);
void Delete5(node_t *node, node_t* parent, bool le_ri);
void Delete6(node_t *node, node_t* parent, bool le_ri);
void rotate_right_parent(node_t *n);
void rotate_left_parent(node_t *n);
node_t *create_hard(string in);
void clean_tree(node_t *root);
