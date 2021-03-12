#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//main函数中存在三个参数
int main(int argc, char *argv[], char *environ[]){


	//main函数中存在三个参数
	int main(int argc, char *argv[], char *environ[]){

		//extern char **environ; //这个变量中保存了所有的访问到环境变量的字符串地址
		int i;
		for (i = 0; environ[i] != NULL; ++i){
			printf("%s\n", environ[i]);
		}
		return 0;
	}

	/*
	int main(){

	char *MYVAL1=getenv("MYVAL1");
	if(MYVAL1==NULL){
	printf("noy found MYVAL1\n");
	}else{
	printf("%s\n",MYVAL1);
	}
	char *MYVAL2=getenv("MYVAL2");
	if(MYVAL2==NULL){
	printf("noy found MYVAL2\n");
	}else{
	printf("%s\n",MYVAL2);
	}
	return 0;
	}
