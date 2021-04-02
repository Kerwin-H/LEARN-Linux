#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

//对于命名管道中读的实现代码
int main(int argc, char *argv[]){
	umask(0);
	int ret = mkfifo("123.fifo", 0664);
	if (ret<0 && errno != EEXIST){

		perror("mkfifo error");
		return -1;
	}
	int fd = open("123.fifo", O_RDONLY);
	if (fd<0){
		perror("open error");
		return -1;
	}
	printf("open read fifo success\n");
	while (1){
		char buf[1024] = { 0 };
		int ret = read(fd, buf, 1023);
		if (ret<0){
			perror("read error");
			return -1;
		}
		else if (ret == 0){
			printf("all write closed\n");
			return -1;
		}
		printf("%s-%d\n", buf, ret);
	}
	close(fd);
	return 0;
}



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<string.h>

//对于命名管道中写的实现
int main(int argc, char *argv[]){
	umask(0);
	int ret = mkfifo("123.fifo", 0664);
	if (ret<0 && errno != EEXIST){

		perror("mkfifo error");
		return -1;
	}
	int fd = open("123.fifo", O_WRONLY);
	if (fd<0){
		perror("open error");
		return -1;
	}
	printf("open write file success\n");
	while (1){
		char buf[1024] = { 0 };
		scanf("%s", buf);
		int ret = write(fd, buf, strlen(buf));
		if (ret<0){
			perror("write error");
			return -1;
		}
	}
	close(fd);
	return 0;
}





