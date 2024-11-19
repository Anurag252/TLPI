#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(){


    int fd1 = open("./testfile1.txt", O_RDWR);
    int fd2 = creat("./testfile2.txt", O_RDWR);

    int err  = 0;
    int buf[10];
    while (read(fd1, buf, 10) > 0)
    {
        write(fd2,buf, 10);
        
    }
    /*
    int size  = sendfile(fd2, fd1, 0, 100 );
    if (size <= 0) {

        perror("error occured while sending ");
        printf("%s\n",strerror(errno));
    }
    */
}