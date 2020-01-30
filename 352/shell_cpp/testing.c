#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
/**
int main(){
	for(int i=0;i<3;i++){
		pid_t p = fork();
		if(p>0)
			printf("%d\n",p);
		if(p==0)
			printf("child %d\n",p);
	}
}
int main(int argc, char *argv[])
{
	pid_t p = fork();
	if(p == 0){
		printf("child");
	}
	return 0;
}
*/

/** PROBLEM 6.a
int main(){
	for(int i=0;i<3;i++){
		pid_t sp = getpid();
		pid_t pp = getppid();
		if(fork()>0)
			printf("A %d self: %d parent: %d \n",i,sp,pp);
	}
}
*/

/**
int gVar = 0;

int main(int argc, char *argv[])
{
	int iVar = 0;
	int *p;
	p = (int*)malloc(sizeof(int));
	int pid = fork();
	if(pid>0){
		gVar = 1;
		iVar = 1;
		*p = 1;
		printf("%d,%d,%d\n",gVar,iVar,*p);
	}else{
		gVar = 2;
		iVar = 2;
		*p = 2;
		printf("%d,%d,%d\n",gVar,iVar,*p);
	}
	return 0;
}
*/

/**
int arrays[100];
void contains(int i1){
	for (int i = 0; i < 100; ++i) {
		if(arrays[i] == i1 )
			return;
		if(arrays[i] == 0){
			arrays[i] = i1;
			break;
		}
	}
}
int gVar = 0;
int main(int argc, char *argv[])
{
	int i;
	int forked = 0;
	for(i=0;i<3;i++) {
		if(i%2==1){
			wait(NULL);
			int retval1 = fork();
			contains(retval1);
			forked++;
		}
		else{
			wait(NULL);
			int retval1 = fork();
			contains(retval1);
			int retval2 = fork();
			contains(retval2);
		}
	}
	for (int i = 0; i < 100; ++i) {
		if(arrays[i] == 0){
			printf(" count    %d",i);
			break;
		}
		else{
			printf("%d \n",arrays[i]);
		}
	}
	return 0;
}
*/
int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "forgeeks.org";
    char input_str[100];
    pid_t p;

    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    scanf("%s", input_str);
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        char concat_str[100];

        close(fd1[0]);  // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str)+1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0], concat_str, 100);
        printf("Concatenated string %s\n", concat_str);
        close(fd2[0]);
    }

    // child process
    else
    {
        close(fd1[1]);  // Close writing end of first pipe

        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);

        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
        for (i=0; i<strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];

        concat_str[k] = '\0';   // string ends with '\0'

        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str)+1);
        write(fd2[1], concat_str, strlen(concat_str)+1);
        close(fd2[1]);

        exit(0);
    }
}
