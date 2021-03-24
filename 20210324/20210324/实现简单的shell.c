#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

//实现一个简单的shell

int main(int argc, int *argv[]){
	
	while (1){
		
		printf("[user@host path]$ ");
		fflush(stdout);
		char buf[1024] = { 0 };
		fgets(buf, 1023, stdin);
		buf[strlen(buf) - 1] = '\0';


		int myargc = 0;
		char *ptr = buf, *myargv[32] = { NULL };
		while (*ptr != '\0'){
			
			if (*ptr != ' '){
				
				myargv[myargc] = ptr;
				myargc++;

				while (*ptr != '\0'&&*ptr != ' ')	ptr++;

				*ptr = '\0';
			}
			ptr++;
		}

		myargv[myargc] = NULL;

		if (strcmp("cd", myargv[0]) == 0){
			
			chdir(myargv[1]);
			continue;
		}

		pid_t pid = fork();
		if (pid < 0){
			
			perror("fork error");
			continue;
		}
		else if (pid == 0){
			
			execvp(myargv[0], myargv);
			perror("execvp error");
			exit(-1);
		}

		wait(NULL);
	}
	return 0;
}