#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//=============1
void test(){
	
	char *str = (char *)malloc(100);
	strcpy(str, "hello");

	free(str);					//�����free���������Ὣstr���ڴ���,
								//���ܼ���ִ������Ĵ���
	if (str != NULL){
		
		strcpy(str, "world");
		printf(str);
	
	}
}

//========2
void getMemory(int **p, int num){
								//1.����������numֵû�н����ж�
	*p = (char*)malloc(num);
								//2.������ʱ����Ŀռ�û�н����ͷ�,���׳���©��
}

void Test(void){
	
	char *str = NULL;
	getMemory(&str, 100);		//3.�����Ĳ���δ���кϷ����ж�
	strcpy(str, "hello");
	printf(str);
}


//=========3

char *GetMemory(void){

	char p[] = "hello world";
	return p;				//�����p��һ���ֲ�����,���������
							//ִ�����ͻᱻ�ͷ�,�Ͳ����ٱ�����
}
void Test1(void){

	char *str = NULL;

	str = GetMemory();		//�����str���õ�����������������н�����
							//ʱ���Ѿ����ͷ���
	printf(str);			//����������������δ������Ϊ
}


//=======4

void GetMemory1(char *p){

	p = (char*)malloc(100);
							//1.δ����free,�����ڴ�й©
							//2.malloc���ؽ��û�п�
							//3.GetMemory1��������ҲΪ�����п�
							//4.�����������ֻ�Ƕ��ڿ���һ����̬�ڴ�ռ�
		//  ��δ������пղ���,û�취���޸�����,�ٴ�printf������ɷ���Խ��.
}
void Test1(void){

	char *str = NULL;
	GetMemory1(str);
	strcpy(str, "hello world");
	printf(str);
}






















int main(){


	system("pause");
	return 0;
}