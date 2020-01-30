#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include <string>
#include "handlerdef.h"

std::string wait_for_input();
int parser(std::string toparse);
int error_handler();
void cd_handler(std::string arg);
int fork_and_execute(vector<string> * toexec);
int pipe_handler(vector<string> * toexec);
int file_writer(vector<string>* towrite,int dub);
