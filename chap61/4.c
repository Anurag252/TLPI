#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

int main() {
    struct sockaddr_in addr ;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    listen(sock,5);
    int len = sizeof(addr);
    int result  = getsockname(sock, &addr  , &len);
   
    printf("port number - %d\n ", addr.sin_port);

}