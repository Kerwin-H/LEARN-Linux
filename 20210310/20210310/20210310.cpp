
//========fork.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){

	printf("======\n");
	pid_t pid = fork();
	if (pid<0){
		//子进程复制了父进程
	}
	else if (pid == 0){
		//子进程--对于子进程的返回值为0
	}
	else{
		//父进程--对于父进程的返回是子进程的pid

		sleep(5);
		exit(0);//退出进程
	}
	printf("I love study! %d\n", getpid());
	while (1)sleep(1);

	return 0;
}



//========statu.c
#include<stdio.h>
#include<unistd.h>

int main(){

	int a = 0;
	sleep(5);
	while (1)
		a++;

}
