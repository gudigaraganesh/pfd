#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
main()
{
struct hostent *sx;
char *out;
struct in_addr a1;
long val=gethostid();
a1.s_addr=(long)val;
out=inet_ntoa(a1);
printf("%s",out);
sx=gethostbyname((const char *)getenv("HOSTNAME"));
printf("check\n%s\n",sx->h_addr_list[0]);
}
