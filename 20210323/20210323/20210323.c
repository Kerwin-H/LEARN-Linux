#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

int main()
{
	//fopen(�ļ�·�������򿪷�ʽ)
	FILE * fp = fopen("./test.txt", "w+");
	if (fp == NULL) {
		perror("fopen error");
		return -1;
	}
	fseek(fp, 10, SEEK_END);
	char *ptr = "���������������!\n";
	//fwrite(��ַ����С�������� ���)
	int ret = fwrite(ptr, strlen(ptr), 1, fp);
	if (ret == 0) {
		perror("fwrite error");
		return -1;
	}
	printf("ret:%d\n", ret);

	//fseek(����� ƫ������ ������)
	fseek(fp, 0, SEEK_SET);

	char buf[1024] = { 0 };
	ret = fread(buf, 1, 1023, fp);
	if (ret == 0) {
		printf("û�ж�ȡ������\n");
	}
	printf("buf:%s----%d\n", buf + 10, ret);

	fclose(fp);
	return 0;
}
