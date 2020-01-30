#include <cstdio>
#include <iostream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;
#define READ_FD     0
#define WRITE_FD    1
int main() { int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid == 0){//child
		string inputString;
		close(fd[READ_FD]);
		fstream myfile("words.txt");
		while(myfile >> inputString)
		{
			write(fd[WRITE_FD], inputString.c_str(),  inputString.length()+ 1);
		}
		close(fd[WRITE_FD]);
	}
	else{
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
		close(fd[READ_FD]);
	}
	return 0;
}
