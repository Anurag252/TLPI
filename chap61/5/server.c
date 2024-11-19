#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr ;
    addr.sin_port = htons(45145);
    addr.sin_family = AF_INET;
    int err = inet_aton("127.0.0.1", &addr.sin_addr.s_addr);
    perror("error");
    
    int len = sizeof(addr);
    printf("%d\n" , len);
    bind(sock, &addr, len );
    err  = listen(sock,5);
    int sock1 = accept(sock, &addr, &len );
    int cmd[50] ;
    err = read(sock1, cmd, 50);
    if (err == 0) {
        printf("error occured 2 %d" , err);
    }
    int t = open("abc.txt", O_CREAT | O_RDWR);
    dup2(t, 1);
    err = system(cmd);
    close(t);
    t = open("abc.txt",  O_RDWR);
    int buf[500];
    int r = read(t, buf, 500);
    buf[100] = '\n'; // end of writing 
    err = write(sock1, buf, 100);
    close(sock1);
}