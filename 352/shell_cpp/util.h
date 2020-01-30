#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <fstream>
using namespace std;
const string codes[11] = {"cd", "clr", "dir", "environ", "echo", "help", "pause", "quit","|",";","more"};
const int PIPE_WRITE = 1;
const int PIPE_READ = 0;
int identify_string(string toID);
void print_vec(vector<string>* toprint);
void handle_cd(vector<string>* torun);
void handle_noargcmd(vector<string>* torun);
void break_string(string input, vector<string> * topush, vector<char> dividers,int keep);
void break_string(string input, vector<string> * topush, char divier,int keep);
void handle_argcmd(vector<string>* torun);
void handle_dir(vector<string> * directory);
void handle_echo(vector<string> * toecho);
void handle_pipe();
vector<string> read_file(string filename);
