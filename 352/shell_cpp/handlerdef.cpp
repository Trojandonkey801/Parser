#include "handlerdef.h"
void (*fun_ptr_arr[8])(vector<string> *) = {handle_cd,handle_clear,handle_dir,handle_environ,handle_argcmd,handle_help,handle_pause,handle_argcmd};

void handle_cd(vector<string>* torun){
	if(torun->size() > 1){
		cout << torun->back() << endl;
		chdir(torun->back().c_str());
	}
	else{
		handle_argcmd("pwd");
	}
}

void handle_environ(vector<string>* torun){
	string pe = "printenv";
	const char *temp = pe.c_str();
	char * ptr = strdup(temp);
	char * argv[] = {ptr,(char *)NULL};
	execvp(argv[0],argv);
	free(ptr);
}

void handle_noargcmd(vector<string>* torun){
	const char * temp = torun->back().c_str();
	char * ptr = strdup(temp);
	char *argv[] = {ptr,  (char *)NULL };
	//char temparr[torun->back().length()+1];
	//strcpy(temparr,ptr);
	execvp(argv[0],argv);
	free(ptr);
}

void handle_argcmd(string torun){
	char *argv[] = {(char *) torun.c_str(),(char *)NULL};
	execvp(argv[0],argv);
}

void handle_argcmd_pipe(vector<string>* torun,int fd[],int read_write){
	int size = torun->size();
	if(read_write == PIPE_READ){
		close(fd[PIPE_WRITE]);
		dup2(fd[PIPE_READ],STDIN_FILENO);
	}
	else if(read_write == PIPE_WRITE){
		close(fd[PIPE_READ]);
		dup2(fd[PIPE_WRITE],STDOUT_FILENO);
	}
	char *argv[size+1];
	for (int i = 0; i < torun->size(); ++i) {
		char *ptr = (char *)torun->at(i).c_str();
		argv[i] = ptr;
	}
	argv[size] = (char *)NULL;
	execvp(argv[0],argv);
	printf("execlp() failed.\n");
	exit(EXIT_FAILURE); // exit child process if exec fails.
}

void handle_argcmd(vector<string>* torun){
	int size = torun->size();
	char *argv[size+1];
	for (int i = 0; i < torun->size(); ++i) {
		char *ptr = (char *)torun->at(i).c_str();
		argv[i] = ptr;
	}
	argv[size] = (char *)NULL;
	execvp(argv[0],argv);
}

void handle_argcmd_out(vector<string>* torun,char **argv[]){
	for (int i = 0; i < torun->size(); ++i) {
		char *ptr = (char *)torun->at(i).c_str();
		cout << ptr << endl;
		*argv[i] = ptr;
	}
	(*argv)[torun->size()] = NULL;
}

void handle_dir(vector<string> * torun){
	torun->at(0) = (char *)"ls";
	handle_argcmd(torun);
}

void handle_echo(vector<string> * toecho){
}

void handle_pause(vector<string> * tohelp){

}

void handle_help(vector<string> * tohelp){
}

void handle_more(){
	
}
void handle_clear(vector<string> * toclear){
	system("clear");
}

