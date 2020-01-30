#include "myshell.h"
using namespace std;
/**
int main(){
	vector<string> *topass = new vector<string>();
	topass->push_back("time");
	handle_argcmd(topass);
	return 0;
}
*/
/**
void execArgs(string[] parsed)
{
    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}
int main(){
	char* argv[] = { "ls",(char*)NULL };
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid == 0){
		close(fd[0]);
		dup2(fd[1], 1);
		execvp(argv[1],argv);
		close(fd[0]);
	}else{
		cout << "inside parent" << endl;
		char reading_buf[1];
		while(read(fd[0], reading_buf, 1) > 0)
		{
			write(1, reading_buf, 1); // 1 -> stdout
		}
		close(fd[0]);
		cout << reading_buf << endl;
	}
}
int main(int argc, char *argv[])
{
	int loc = 100;
	loc = 100;
	int *ptr = &loc;
	pid_t pid = fork();
	if(pid == 0){
		*ptr = 2;
	}
	else{
		pid_t pi2 = fork();
		if(pi2 == 0)
			cout << *ptr << endl;
		wait(NULL);
	}
	cout << loc << endl;
	return 0;
}
  int main(int argc, char *argv[])
  {
  int fd1[2];
  int fd2[2];
  string input = "this is going in";
  string output;
  if(pipe(fd1) == -1){
  cout << "shit broke 1 " << endl;
  }
  if(pipe(fd2) == -1){
  cout << "shit broke 2" << endl;
  }
  return 0;
  }
  int main(int argc, char *argv[])
  {
  std::system("ls -l | more"); // execute the UNIX command "ls -l >test.txt"
  return 0;
  }
 **/
 // Scott Kuhl
//
// This program does not check the return code of close(), dup2(),
// execlp(), fork(), and waitpid(). A good program would add those
// additional checks!
// #include <iostream>
/**
#include <cstdio>
#include <iostream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include "util.h"

using namespace std;

int main()
{
	int fd[2];
	pipe(fd);
	pid_t pid  = fork();
	if(pid == 0){//child
		string inputString;
		close(fd[PIPE_READ]);
		ifstream myfile;
		myfile.open ("example.txt");
		close(fd[0]);
		while(myfile >> inputString)
		{
			write(fd[1], inputString.c_str(), sizeof(inputString) + 1);
		}
		close(fd[PIPE_WRITE]);
	}
	else{
		wait(NULL);
		pid_t pid1 = fork();
		if(pid1==0){
			close(fd[PIPE_WRITE]);
			std::string s;
			char ch;
			while (read(fd[PIPE_WRITE], &ch, 1) > 0)
			{
				if (ch != 0)
					s.push_back(ch);
				else
				{
					std::cout << s << '\n';
					s.clear();
				}
			}
			close(fd[PIPE_READ]);
			exit(0);
		}
		else{
			wait(NULL);
		}
	}
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

#define READ_FD     0
#define WRITE_FD    1

int main (int argc, char * argv[])
{
    int fd[2];
    pid_t cpid;

    pipe(fd);
    if ((cpid = fork()) == -1)
    {
        cout << "ERROR" << endl;
        exit(1);
    }

    // child process
    if (cpid == 0)
    {
        // don't need the write-side of this
        close(fd[WRITE_FD]);

        std::string s;
        char ch;
        while (read(fd[READ_FD], &ch, 1) > 0)
        {
            if (ch != 0)
                s.push_back(ch);
            else
            {
                std::cout << s << '\n';
                s.clear();
            }
        }

        // finished with read-side
        close(fd[READ_FD]);
    }

    // parent process
    else
    {
        // don't need the read-side of this
        close(fd[READ_FD]);

        fstream fileWords ("words.txt");
        string toSend;
        while (fileWords >> toSend)
        {
            // send word including terminator
            write(fd[WRITE_FD], toSend.c_str(), toSend.length()+1);
        }

        // finished with write-side
        close(fd[WRITE_FD]);
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
*/

