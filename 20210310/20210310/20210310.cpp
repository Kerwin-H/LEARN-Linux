
//========fork.c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){

	printf("======\n");
	pid_t pid = fork();
	if (pid<0){
		//�ӽ��̸����˸�����
	}
	else if (pid == 0){
		//�ӽ���--�����ӽ��̵ķ���ֵΪ0
	}
	else{
		//������--���ڸ����̵ķ������ӽ��̵�pid

		sleep(5);
		exit(0);//�˳�����
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
