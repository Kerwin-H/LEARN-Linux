#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
	printf("recv signal:%d\n", signo);
}
int main(int argc, char *argv[])
{
	signal(SIGINT, sigcb);
	signal(40, sigcb);

	//sigprocmask(�������ͣ� �źż��ϣ� �źż���)
	sigset_t set;
	sigemptyset(&set);
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	printf("�س��󣬼�������\n");
	getchar();
	printf("����ź��������鿴���\n");
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	while (1) {
		sleep(1);
	}
	return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
	printf("recv signal:%d\n", signo);
	printf("ʱ�䵽�ˣ���һ�ں������~\n");
	alarm(3);
}
int main(int argc, char *argv[])
{
	//signal(�źţ� ����ʽ)
	signal(SIGALRM, sigcb);
	//kill(����ID�� �ź�ֵ)
	//kill(getpid(), SIGINT);
	//raise(SIGINT);
	alarm(3);
	while (1) {
		printf("-------\n");
		sleep(1);
	}
	return 0;
}
