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

	printf("Client: waiting for a server.\n");
	fd = open(FIFO_NAME, O_RDONLY);

	printf("Client: the client ready.\n");

	do {
		if ((num = read(fd, buf, 100)) == -1)
			perror("read error");
		else{
			buf[num] = '\0';
			printf("\t%d + 1 = %d\n", atoi(buf), atoi(buf) + 1);
		}
	}while(num > 0 );

	return 0;
}

	
