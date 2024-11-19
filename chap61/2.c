#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


void write_on(char * data, int fd);
void read_on(int fd, char* buf) ;

int main(){
    int fs[2] ;
    signal(SIGPIPE, SIG_IGN); // to avoid program termination while writing to boken pipe

    int err  = socketpair(PF_LOCAL,SOCK_STREAM,0,fs);
    if (err != 0) {
        
        printf("error occured %d %d %d %s", fs[0], fs[1], err, strerror(errno) );
        return 1;
    } else {
        printf("socket pair created  %d %d\n", fs[0], fs[1]);
    }
    char * data2 = "some test";
    char * data1 = "some other test";
    write_on(data1, fs[0]);
    
    char buf[50];
    read_on(fs[1], buf);
    if (strcmp(data1,buf)){
        perror("could not read\n");
        printf("%s\n", buf);
    } else {
        printf("%s\n", buf);
    }
    
    write_on(data2, fs[1]);
    read_on(fs[0], buf);
    if (strcmp(data2,buf)){
        perror("error occured\n");
    } else {
        printf("%s\n", buf);
    }
    
    if (shutdown(fs[1], SHUT_WR) != 0) {
        printf("error occured while shutting down duplex connection\n");
    } else {
        printf("performed shutdown \n");
    }
    // shutdown(fs[0], SHUT_RW) should also be done 
    data2 = "some text diff than previous";
    write_on(data2, fs[1]);
    read_on(fs[0], buf);
    if (strcmp(data2,buf)){
        perror("error occured\n");
    } else {
        printf("%s\n", buf);
    }

    return 0; 
}

void write_on(char * data, int fd){
    int err = write(fd, data, 50);
    if( err > 0) {
        printf("successfully written\n");
    } else {
        printf("error occured while writing %s \n", strerror(errno));
    }
    
}

void  read_on(int fd, char* buf){  
    if (read(fd, buf, 50) > 0) {
        printf("successfullt read\n");
    }
}