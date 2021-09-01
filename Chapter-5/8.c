#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(char argc,char * argv[]){
  int fd[2];
  if (pipe(fd) < 0) {
    perror("pipe error");
    exit(1);
  }
  int pid = fork();
  if (pid < 0){
    fprintf(stderr,"fork fail\n");
    exit(1);
  }else if (pid == 0) {
    int ppid = fork();//创建两个子进程
    if (ppid < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if (ppid == 0) {
        close(fd[0]);
        if(fd[1] != STDOUT_FILENO){
            if(dup2(fd[1],STDOUT_FILENO)!= STDOUT_FILENO){
                fprintf(stderr,"dup2 fail\n");
            }
            close(fd[1]);
        }
        printf("Hello");
    }else {
        wait(NULL);
        close(fd[1]);
        if(fd[0] != STDIN_FILENO){
            if(dup2(fd[0],STDIN_FILENO)!= STDIN_FILENO){
                fprintf(stderr,"dup2 fail\n");
            }
            close(fd[0]);
        }
        char asw[20];
        int res = read(STDIN_FILENO, asw, sizeof(char) * 20);
        printf("size:%d, %s\n", res, asw);
    }
  }
    return 0;
}