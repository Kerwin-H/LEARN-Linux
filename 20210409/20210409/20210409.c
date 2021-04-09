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

	//sigprocmask(操作类型， 信号集合， 信号集合)
	sigset_t set;
	sigemptyset(&set);
	sigfillset(&set);
	sigprocmask(SIG_BLOCK, &set, NULL);
	printf("回车后，继续运行\n");
	getchar();
	printf("解除信号阻塞，查看结果\n");
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
	printf("时间到了，吃一口红烧肉吧~\n");
	alarm(3);
}
int main(int argc, char *argv[])
{
	//signal(信号， 处理方式)
	signal(SIGALRM, sigcb);
	//kill(进程ID， 信号值)
	//kill(getpid(), SIGINT);
	//raise(SIGINT);
	alarm(3);
	while (1) {
		printf("-------\n");
		sleep(1);
	}
	return 0;
}
