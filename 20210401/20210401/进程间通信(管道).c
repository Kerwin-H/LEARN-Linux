#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
		sleep(3);
		char *ptr = "����8����\n";
		int total = 0;
		while (1) {
			int ret = write(pipefd[1], ptr, strlen(ptr));
			total += ret;
			printf("�ӽ���д��ɹ�%d\n", total);
		}
	}
	else {
		sleep(100);
		char buf[1024] = { 0 };
		read(pipefd[0], buf, 1023);
		printf("�����̣�%s\n", buf);
	}
	return 0;
}
