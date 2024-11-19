#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <stdio.h>

int main() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("Hi1\n");
    struct sockaddr_in addr = {} ;
    struct in_addr addrs ;
    inet_aton("0.0.0.0", &addr.sin_addr.s_addr);
    printf("Hi2\n");
    addr.sin_family = AF_INET;
    printf("Hi4\n");
    addr.sin_port = htons(12345);
    printf("Hi5\n");
    printf("Hi3\n");
    sem_t sem ;
    int res = bind(sock, &addr, sizeof(addr));
    if (res != 0) {
        printf("error occured");
    } else {
        printf("no error occured\n");
    }
    perror("errpr\n");
    res = listen(sock, 100);
    perror("errpr\n");
    if (res != 0) {
        printf("error occured");
    } else {
        printf("no error occured\n"); 
    }
    printf("Hi\n");
    sem_init(&sem, 1, 5);
    printf("Hi6\n");
    int count  = 0;
    
    printf("Hi7\n");
    while(1) {
        printf("w8\n");
        sem_wait(&sem);
        printf("Hi8\n");
        int len = sizeof(&addr);
        int newsock = accept(sock, &addr, &len);

        switch(fork()){
            case -1:
            printf("error\n");
            break;

            case 0:
                char* buf = "HELLO";
                write(newsock, buf,20 );
                sleep(10);
                printf("done\n");
                sem_post(&sem);

                sem_getvalue(&sem,&count);
                printf("value of sem %d", count);
                break;
                
        }

    }

}