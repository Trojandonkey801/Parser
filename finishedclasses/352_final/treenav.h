/**
 * The header file for treenav.cpp
 */
#include "parser.h"
using namespace std;
#define BLACK 0
#define RED 1
node_t *get_left(node_t *current);
node_t *get_right(node_t *current);
node_t *get_uncle(node_t *current);
node_t *get_grandf(node_t *current);
node_t *get_parent(node_t *current);
int get_color(node_t *current);
void set_color(node_t *current,int color_in);
bool is_left(node_t *current);
void link(node_t *parent, node_t *child,bool is_left);
node_t *recurse(node_t *current,bool is_left);
node_t *find_succ(node_t *tofind,bool succ);
void replace(node_t *toreplace, node_t *with);
node_t *get_sibling(node_t *current);
bool correctness(node_t *head,int current);
