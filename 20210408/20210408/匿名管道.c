#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]){
	int pipefd[2];
	int ret = pipe(pipefd);
	if (ret<0){
		perror("pipe error");
		return -1;
	}
	pid_t pid = fork();
	if (pid<0){
		perror("fork error");
		return -1;
	}
	else if (pid == 0){
		//zi  
		char buf[1024] = { 0 };
		read(pipefd[0], buf, 1023);
		printf("子进程打印出:");
		printf("%s\n", buf);
	}
	else{
		//fu
		char* ptr = "i am father";
		int ret = write(pipefd[1], ptr, strlen(ptr));
		printf("success\n");
	}
	return 0;
}