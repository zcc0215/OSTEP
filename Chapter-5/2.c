#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(char argc,char * argv[]){
    int fd = open("./Check.txt",O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int pid = fork();
    if (pid < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if (pid == 0){
        char * buf = "Child\n";
        write(fd,buf,sizeof(char)* strlen(buf));
    }else {
        char * buf = "Parent\n";
        write(fd,buf,sizeof(char)* strlen(buf));
        int wc = wait(NULL);
        close(fd);
    }
    return 0;
}