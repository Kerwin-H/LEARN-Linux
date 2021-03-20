
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

	pid_t pid = fork();

	if (pid<0){
		perror("fork error");
		exit(-1);
	}
	else if (pid == 0){
		//child
		sleep(5);
		exit(0);

	}
	else{
		//parents
		//int childpid=wait(NULL);
		//int childpid=waitpid(pid,NULL,0);             
		int childpid = waitpid(pid, NULL, WNOHANG);
		printf("%d----%d\n", pid, childpid);
		while (1)sleep(1);
	}
	return 0;
}