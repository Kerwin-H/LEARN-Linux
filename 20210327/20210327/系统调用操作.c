#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
	umask(0);
	int fd = open(".bite.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0) {
		perror("open error");
		return -1;
	}

	char *ptr = " i love linux\n";
	int ret = write(fd, ptr, strlen(ptr));
	if (ret < 0) {
		perror("write error");
		return -1;
	}

	lseek(fd, 0, SEEK_SET);

	char buf[1024] = { 0 };
	ret = read(fd, buf, 1023);
	if (ret < 0) {
		perror("read error");
		return -1;
	}
	printf("%s\n", buf);

	close(fd);
	ret = read(fd, buf, 1023);
	if (ret < 0) {
		perror("read error");
		return -1;
	}
	return 0;
}