#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	int ret = pipe(pipefd);
	if (ret < 0) {
		perror("pipe error");
		return -1;
	}

	if (fork() == 0) {
		//����ps����
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execlp("ps", "ps", "-ef", NULL);
		exit(-1);
	}
	if (fork() == 0) {
		//����grep����
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		execlp("grep", "grep", "pipe", NULL);
		exit(-1);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	wait(NULL);
	wait(NULL);
	printf("�����������\n");
	return 0;
}


//
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	int ret = pipe(pipefd);
	if (ret < 0) {
		perror("pipe error");
		return -1;
	}

	pid_t pid = fork();
	if (pid < 0) {
		perror("fork error");
		return -1;
	}
	else if (pid == 0) {
		close(pipefd[0]);
		sleep(5);
		char *ptr = "����8����\n";
		printf("�ӽ���Ҫ��ʼд��������\n");
		int ret = write(pipefd[1], ptr, strlen(ptr));
		printf("д�����ݳɹ�\n");
	}
	else {
		printf("�����̹رն���\n");
		close(pipefd[0]);
		sleep(10000);
		char buf[1024] = { 0 };
		int ret = read(pipefd[0], buf, 1023);
		if (ret < 0) {
			perror("read error");
		}
		else if (ret == 0) {
			printf("����д�α��ر���\n");
		}
		printf("�����̣�%s-%d\n", buf, ret);
	}
	return 0;
}
