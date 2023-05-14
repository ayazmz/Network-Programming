#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){

	printf("Start\n");
	int pid = getpid();
	printf("Process ID:%d\n", pid);
	int f_pid = fork();
    
	if(f_pid == -1){
		printf("Fork Failed!\n");
		exit(1);}
	else if(f_pid == 0){
		printf("This is the child process.ID:%d\n", getpid());
		printf("Present Directory:\n");
		execlp("pwd","pwd",NULL);
	}
	else{
		wait(NULL);
		printf("This is the parent process\n");
		printf("ls\n");
		execlp("ls","ls",NULL);
	}
	return 0;
}