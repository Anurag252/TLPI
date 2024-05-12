## This code is not production ready and only work for a small subset of happy path

```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>


char* read_line_and_find(int fd, char* username);
int exist_username(char* line, char* username);
char* *read_dir(char* path);
char* find_user_id(char* line);

int main(int argc, char **argv) {
    int fd;
    fd = open("/etc/passwd", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char* line;
    line = read_line_and_find(fd, argv[1]); //TODO: handle no params
    char* id = find_user_id(line);
    char* *path = read_dir("/proc/");
    printf("user %s is running :-\n", argv[1]);
    for (int i = 0 ; i < 100; i ++) {
        char* path_name = path[i];
        char* proc = malloc(100*sizeof(char));
        strcpy(proc,"/proc/");
        strcat(proc, path_name);
        strcat(proc, "/status");
        fd = open(proc, O_RDONLY);
        if (fd == -1) {
            continue;
        }
        char* line_name_match = read_line_and_find(fd, "Name");
        char* line_uid_match = read_line_and_find(fd, "Uid");
        if (exist_username(line_uid_match,  id )){
            printf(" %s \n", line_name_match);
        }
        
    }

    close(fd);
    return 0;
}

char* find_user_id(char* line) {

    char* token;
    strtok(line, ":");
    strtok(NULL, ":");
    strtok(NULL, ":");
    token =  strtok(NULL, ":");
    return token;
    //return strtol(token, NULL, 10);
}

char* *read_dir(char* path) {
    char* *result = malloc(1000 * sizeof(char));
    DIR *dirp;
    struct dirent *dp;
    dirp = opendir(path);
    int i = 0;
    while(dp != NULL) {
        dp = readdir(dirp);
        if (dp == NULL){
            return result;
        }
        if ( dp->d_type != 4){
            continue;
        }
        result[i] = (dp->d_name);
        i = i + 1;
    }
    return result;
}

char* read_line_and_find(int fd, char* username) {
        char buf[1];
        char *line = (char *)malloc(1000 * sizeof(char));
        int read_bytes = 1;
        int i = 0;
        while(read_bytes > 0) {
            *buf = malloc(1);
            while(1) {
                read_bytes = read(fd, buf, 1);
                memcpy(line + i, buf, 1);
                i ++;
                if (*buf == '\n') { //TODO: handle infitie loop
                    break;
                }
                *buf = malloc(1);
                 
            }
            if (exist_username(line, username) == 1){
                return line;
            } else {
                *line = (char *)malloc(1000 * sizeof(char));
                i = 0;
            }
        }
        return line;    
}

int exist_username(char* line, char* username){
    char* found;
    found = strstr(line, username);
    if (found != NULL) {
        return 1;
    }
    return 0;
}
```