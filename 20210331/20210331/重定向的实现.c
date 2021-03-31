#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	while (1) {
		printf("[user@host path]$ ");
		fflush(stdout);
		char buf[1024] = { 0 };
		fgets(buf, 1023, stdin);
		buf[strlen(buf) - 1] = '\0';

		// echo "nihao" >>    a.txt   
		char *str = buf;
		int reflag = 0;
		char *refile = NULL;
		while (*str != '\0') {
			if (*str == '>') {
				reflag++;
				*str = '\0';
				str++;
				if (*str == '>') {
					reflag++;
					*str = '\0';
					str++;
				}
				while (*str != '\0' && *str == ' ') str++;
				refile = str;
				while (*str != '\0' && *str != ' ') str++;
				*str = '\0';
			}
			str++;
		}

		int myargc = 0;
		char *ptr = buf, *myargv[32] = { NULL };
		while (*ptr != '\0') {
			if (*ptr != ' ') {
				myargv[myargc] = ptr;
				myargc++;
				while (*ptr != '\0' && *ptr != ' ') ptr++;
				*ptr = '\0';
			}
			ptr++;
		}
		myargv[myargc] = NULL;

		// cd /home
		if (strcmp("cd", myargv[0]) == 0) {
			chdir(myargv[1]);
			continue;
		}

		pid_t pid = fork();
		if (pid < 0) {
			perror("fork error");
			continue;
		}
		else if (pid == 0) {
			if (reflag == 1) {
				int fd;
				fd = open(refile, O_RDWR | O_CREAT | O_TRUNC, 0664);
				dup2(fd, 1);
			}
			else if (reflag == 2) {
				int fd;
				fd = open(refile, O_RDWR | O_CREAT | O_APPEND, 0664);
				dup2(fd, 1);
			}
			execvp(myargv[0], myargv);
			perror("execvp error");
			exit(-1);
		}
		wait(NULL);
	}
	return 0;
}
