#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#ifdef HAVE_SYS_FILE_H
#  include <sys/file.h>
#endif

#include <termios.h>
char buf[6];
int main(int argc,char *argv[])
{
	int i=0;
	int fd;
	struct sockaddr_in addr;
	unsigned long portul=966;
	struct hostent *hostent;
	buf[0]=0x2f;
	buf[1]=0x04;
	buf[2]=0xe8;
	buf[3]=0x03;
	buf[4]=0x00;
	buf[5]=0x00;
	fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == -1) {
		perror("socket()");
		return -1;
	}
	if (!(hostent = gethostbyname(argv[1]))) {
		fprintf(stderr, "%s: Unknown host \n",__FUNCTION__);
		goto fail_close;
	}
	if (hostent->h_addrtype != AF_INET || hostent->h_length != sizeof(addr.sin_addr) || !hostent->h_addr_list[0]) {
		fprintf(stderr, "tcp_open: Address resolve for host not compatible!\n");
		goto fail_close;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portul);
	memcpy(&addr.sin_addr, hostent->h_addr_list[0], sizeof(addr.sin_addr));

	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("connect()");
		goto fail_close;
	}
		while(i<5)
		{
		write(fd,buf,6);
		sleep(1);
		read(fd,buf,1);
		printf("hello how are you %s",buf);
		i++;
		}
fail_close:
	close(fd);
}
