#include "restart.h"
#define READ_END     0
#define WRITE_END    1

void handle_argcmd(string torun){
	if(torun.compare("cd") == 0)
		torun = "pwd";
	else if(torun.compare("clr") == 0){
		system("clear");
		return;
	}
	else if(torun.compare("environ") == 0){
		torun = "printenv";
	}
	else if(torun.compare("help") == 0){
		pid_t pid,pid2;
		int fd[2];

		pipe(fd);
		pid = fork();

		if(pid==0)
		{
			dup2(fd[WRITE_END], STDOUT_FILENO);
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			char *argv[] = {"echo", "this stuff"};
			execlp(argv[0], argv[0], argv[1], (char*) NULL);
			exit(1);
		}
		else if((pid2 = fork()) == 0)
		{
				dup2(fd[READ_END], STDIN_FILENO);
				close(fd[WRITE_END]);
				close(fd[READ_END]);
				execlp("/usr/bin/more", "/usr/bin/more", (char*) NULL);
				exit(1);
		}
		else{
				waitpid(pid2, NULL, 0);
		}

	}
	char *argv[] = {(char *) torun.c_str(),(char *)NULL};
	if(execvp(argv[0],argv) < 0){
		cout << "error occurred" << endl;
	}
}
string stripout(string tostrip){
	string toreturn = "";
	for (int i = 0; i < tostrip.length(); ++i) {
		if(i == 0){
			if(tostrip.at(i) != ' '){
				toreturn += tostrip.at(i);
			}
		}
		else if(i == tostrip.length() - 1){
			if(tostrip.at(i) != ' '){
				toreturn += tostrip.at(i);
			}
		}
		else{
			toreturn += tostrip.at(i);
		}
	}
	return toreturn;
}
void handle_argcmd(vector<string> * torun){
}
int count_space(string tocount){
	int count = 0;
	for (int i = 0; i < tocount.length(); ++i) {
		if(tocount.at(i) == ' ')
			count ++;
	}
	return count;
}
void currdir(char *toreturn){
	char currdir[256];
	getcwd(currdir, 256);
	for (int i = 0; i < 256; ++i) {
		toreturn[i] = currdir[i];
	}
}
int main(){
	do{
		char toprint[256];
		currdir(toprint);
		cout << toprint << "/myshell:";
		string toexecute = "";  
		getline(cin,toexecute,'\n');
		if(toexecute.compare("quit") == 0){
			break;
		}
		toexecute = stripout(toexecute);
		cout << toexecute << endl;
		if(toexecute.length() == 0)
			continue;
		if(count_space(toexecute) == 0){
			pid_t outer = fork();
			if(outer == 0){
				pid_t c1 = fork();
				if(c1 == 0)
					handle_argcmd(toexecute);
				else
					wait(NULL);
			}
		}
	}while(true);
	return 0;
}
