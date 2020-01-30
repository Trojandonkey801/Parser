/**
 * Header file for parser program
 *
 *
 */
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

//The struct node. It contains parents, left, right , color and key
typedef struct node {
    int key;
    struct node* left; struct node* right; bool color;
    struct node* parent;
    mutex m;
}node_t;
extern node_t *NIL;
extern node_t *head;
extern vector<string> topass;
extern vector<string> read_t;
extern string read_s;
extern string read_m;
extern vector<string> read_c;
vector<string> read_t_name(string input);
vector<string> read_tree(string input);
bool is_t_name(string input);
bool is_tree(string input);
bool is_command(string input);
void print_vec(vector<string> toprint);
string strip(string tostrip);
string stripout(string tostrip);
string read_m_name(string input);
string read_s_name(string input);
vector<string> read_c_name(string input);
void parselines();
void fileOpen(string inFile);
int strip_paren(string tostrip);
void preorder_print(node_t *head, bool right);
