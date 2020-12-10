#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "15011110_fifo"

int main(void){
	char buf[100];
	int num, fd;

	if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1){
		perror("mknod error");
	}

	printf("Server: waiting for a Client.\n");
	fd = open(FIFO_NAME, O_WRONLY);

	printf("Server: write your input.\n");
	while (fgets(buf, sizeof(buf), stdin), !feof(stdin)){
		if((num = write(fd, buf, strlen(buf))) == -1)
			perror("write error");
	}

	return 0;
}

	
