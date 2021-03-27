#include <stdio.h>
#include <string.h>

int main()
{
	FILE * fp = fopen("./bite.txt", "w+");
	if (fp == NULL) {
		perror("fopen error");
		return -1;
	}
	fseek(fp, 10, SEEK_END);
	char *ptr = "linux easy\n";
	int ret = fwrite(ptr, strlen(ptr), 1, fp);
	if (ret == 0) {
		perror("fwrite error");
		return -1;
	}
	fseek(fp, 0, SEEK_SET);

	char buf[1024] = { 0 };
	ret = fread(buf, 1, 1023, fp);
	if (ret == 0) {
		printf("没有读取到数据\n");
	}
	printf("buf:%s\n", buf + 10);

	fclose(fp);
	return 0;
}
