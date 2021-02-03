#include<stdio.h>
#include<string.h>

void test(){
	printf("this is a funcation\n");
	char *tmp=NULL;
	memcpy(tmp,"hello",5);
	printf("%s\n",tmp);
	return ;

}


int main(){
	printf("hello nice\n");

	int i=0;

	for(i=0;i<5;i++){
		printf("-------\n");
	}
	test();
	printf("over\n");
	return 0;
}
