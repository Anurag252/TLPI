#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char ** argv) {
    // NO ERROR HANDLING
    char * address = argv[1];
    char * cmd = argv[2];
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("check point  1\n");
    struct sockaddr_in addr ;
    addr.sin_port = htons(45145);
    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr.s_addr);
    int len = sizeof(addr);
    int err = connect(sock, &addr, len );
    err = write(sock, cmd, sizeof(cmd));
    shutdown(sock , SHUT_WR);
    int arr[500] ;
    read(sock, arr, 500);
    arr[49] = '\0';
    printf("data - %s\n" , arr); 
}