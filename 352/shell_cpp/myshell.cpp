#include "myshell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define READ_FD     0
#define WRITE_FD    1
using namespace std;
string currdir;
int main(int argc, char* argv[]){
	if(argc>2){
		vector<string> file_read = read_file(argv[1]);
		for (int i = 0; i < file_read.size(); ++i) {
			vector<char> div = {';'};
			vector<string> *parsed = new vector<string>();
			break_string(file_read.at(i),parsed,div,1);
			fork_and_execute(parsed);
			delete(parsed);
		}
	}
	else{
		vector<string> * parsed = new vector<string>;
		string readin = wait_for_input();
		break_string(readin,parsed,';',1);
		fork_and_execute(parsed);
	}
	return 0;
}

/**
 * This function is the "console line" that waits for user input
 *
 */
string wait_for_input(){
	char work_dir[256];
	string toreturn;
	getcwd(work_dir, 256);
	currdir = work_dir;
	cout<< currdir << "/myshell" << " :";
	getline (cin, toreturn);
	return toreturn;
}

/**
 * This function take the values of the input and returns the correct integar mapping of the command.
 * Otherwise, it returns -1
 * @param toparse The string to parse
 * @return the integer mapping of the command. -1 if the command does not exist
 */
int parser(string toparse){
	int i = 0;
	for (i = 0; i < 9; ++i) {
		if(codes[i].compare(toparse) == 0)
			return i;
	}
	return -1;
}

int error_handler(){
	cout << "error occured." << endl;
	return 0;
}

int fork_and_execute(vector<string> * toexec){
	for (int i = 0; i < toexec->size(); ++i) {
		if(toexec->at(i).find("|") != string::npos){//found pipe, pass to pipe handler
			vector<string>* pipe_push = new vector<string>();
			vector<char> pipe_break;
			pipe_break.push_back('|');
			pipe_break.push_back(' ');
			break_string(toexec->at(i),pipe_push,pipe_break,1);
			pipe_handler(pipe_push);
		}
		else if(toexec->at(i).find(">") != string::npos){
			if(toexec->at(i).find(">>") != string::npos){
				vector<string>* dir_push = new vector<string>();
				vector<char> dir_break;
				dir_break.push_back('|');
				dir_break.push_back(' ');
				break_string(toexec->at(i),dir_push,dir_break,1);
				file_writer(dir_push,1);
			}
			else{
				vector<string>* dir_push = new vector<string>();
				vector<char> dir_break;
				dir_break.push_back('|');
				dir_break.push_back(' ');
				break_string(toexec->at(i),dir_push,dir_break,1);
				file_writer(dir_push,0);
			}
		}
		else{//no pipe operation
			vector<string> * broken = new vector<string>();
			break_string(toexec->at(i),broken,' ',1);
			int loc = identify_string(broken->at(0));
			pid_t child = fork();
			if(child == 0){
				(*fun_ptr_arr[loc])(broken);
			}
			else{
				wait(NULL);
			}
		}
	}
	return 0;
}

int pipe_handler(vector<string> * toexec){
	//assumed input is some commands | more
	int my_pipe[2];
	if(pipe(my_pipe) == -1)
	{
		fprintf(stderr, "Error creating pipe\n");
	}

	pid_t child_id, child2;
	child_id = fork();
	string comm = toexec->back();
	if(child_id == -1)
	{
		fprintf(stderr, "Fork error\n");
	}
	if(child_id == 0) // child process
	{
		close(my_pipe[0]); // child doesn't read
		toexec->pop_back();//pop more
		toexec->pop_back();//pop |

		char *argv[toexec->size()+1];
		for (int i = 0; i < toexec->size(); ++i) {
			string temp = toexec->at(i);
			argv[i] = (char *)alloca(temp.size()+1);
			memcpy(argv[i], temp.c_str(), temp.size()+1);
		}
		argv[toexec->size()] = (char *)NULL;
		//handle_argcmd_out(toexec,argv);
		dup2(my_pipe[1], 1); // redirect stdout
		execvp(argv[0], argv);
		close(my_pipe[1]);
		fprintf(stderr, "Exec failed\n");
	}
	else
	{
		child2 = fork();
		if(child2 == 0){
			wait(NULL);
			pid_t child2 = fork();
			if(child2 == 0){
				close(my_pipe[1]); // parent doesn't write
				dup2(my_pipe[0],0);
				char* arguments[] = {"more", NULL};
				execvp(arguments[0], arguments);
			}
		}
		else{
			waitpid(child2,NULL,0);
		}
	}
	return 0;
}

int file_writer(vector<string>* towrite,int dub){
}
