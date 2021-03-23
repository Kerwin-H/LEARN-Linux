#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

int main()
{
	//fopen(文件路径名，打开方式)
	FILE * fp = fopen("./test.txt", "w+");
	if (fp == NULL) {
		perror("fopen error");
		return -1;
	}
	fseek(fp, 10, SEEK_END);
	char *ptr = "今天的天气好晴朗!\n";
	//fwrite(地址，大小，个数， 句柄)
	int ret = fwrite(ptr, strlen(ptr), 1, fp);
	if (ret == 0) {
		perror("fwrite error");
		return -1;
	}
	printf("ret:%d\n", ret);

	//fseek(句柄， 偏移量， 相对起点)
	fseek(fp, 0, SEEK_SET);

	char buf[1024] = { 0 };
	ret = fread(buf, 1, 1023, fp);
	if (ret == 0) {
		printf("没有读取到数据\n");
	}
	printf("buf:%s----%d\n", buf + 10, ret);

	fclose(fp);
	return 0;
}
