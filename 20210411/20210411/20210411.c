#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

	umask(0);
	int ret = mkfifo("guandao.fifo", 0664);
	if (ret<0 && errno != EEXIST){
		perror("mkfifo error");
		return -1;
	}
	int fd = open("guandao.fifo", O_RDONLY);
	if (fd<0){
		perror("open error");
		return -1;
	}
	printf("success rd\n");
	while (1){
		char buf[1024] = { 0 };
		int ret = read(fd, buf, 1023);
		if (ret<0){
			perror("read error");
			return -1;
		}
		else if (ret == 0){
			printf("all write close\n");
			return -1;
		}
		printf("%s-%d\n", buf, ret);
	}
	close(fd);
	return 0;
}


int main(int argc, char *argv[]){

	umask(0);
	int ret = mkfifo("guandao.fifo", 0664);
	if (ret<0 && errno != EEXIST){

		perror("mkfifo error");
		return -1;
	}

	int fd = open("guandao.fifo", O_WRONLY);
	if (fd<0){
		perror("open error");
		return -1;
	}
	printf("open success\n");

	while (1){

		char buf[1024] = { 0 };
		scanf("%s,buf");
		int ret = write(fd, buf, strlen(buf));
		if (ret<0){

			perror("write error");
			return -1;
		}
	}
	close(fd);

	return 0;
}
