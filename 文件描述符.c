#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
	umask(0);//将当前进程的文件默认创建权限掩码设置为0
	//open(文件名， 打开标志，权限)
	int fd = open("./tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0) {
		perror("open error");
		return -1;
	}

	char *ptr = "明天就要休假了，好开心~~\n";
	//write(句柄，数据，长度)
	int ret = write(fd, ptr, strlen(ptr));
	if (ret < 0) {
		perror("write error");
		return -1;
	}

	//lseek(句柄，偏移量，位置) SEEK_SET SEEK_CUR SEEK_END
	lseek(fd, 0, SEEK_SET);

	char buf[1024] = { 0 };
	ret = read(fd, buf, 1023);
	if (ret < 0) {
		perror("read error");
		return -1;
	}
	printf("%s-%d\n", buf, ret);

	close(fd);
	ret = read(fd, buf, 1023);
	if (ret < 0) {
		perror("read error");
		return -1;
	}
	return 0;
}