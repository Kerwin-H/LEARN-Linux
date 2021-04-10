#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int a = 0, b = 0;

int test() {
	a++;
	sleep(1);
	b++;
	printf("%d + %d = %d\n", a, b, a + b);
}

void sigcb(int no)
{
	test();
}
int main(int argc, char *argv[])
{
	signal(SIGINT, sigcb);
	test();
	return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int a = 1;
void sigcb(int no)
{
	a = 0;
	printf("%d\n", a);
}
int main(int argc, char *argv[])
{
	signal(SIGINT, sigcb);
	while (a) {
	}
	printf("程序正常退出\n");
	return 0;
}
