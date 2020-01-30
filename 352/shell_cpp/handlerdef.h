#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include <string>
#include "util.h"
using namespace std;


void handle_cd(vector<string>* torun);
void handle_noargcmd(vector<string>* torun);
void handle_argcmd(vector<string>* torun);
void handle_argcmd_out(vector<string>* torun,char **argv[]);
void handle_argcmd_pipe(vector<string>* torun,int fd[],int read_write);
void handle_argcmd(string torun);
void handle_dir(vector<string> * directory);
void handle_echo(vector<string> * toecho);
void handle_clear(vector<string> * toclear);
void handle_environ(vector<string>* torun);
void handle_help(vector<string>* torun);
void handle_pause(vector<string>* torun);
extern void (*fun_ptr_arr[8])(vector<string> *);
