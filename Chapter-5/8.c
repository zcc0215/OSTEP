#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
        char *msg = "Hello!\n";
        close(fd[0]);//关闭读管道
        write(fd[1], msg, sizeof(char) * strlen(msg));
    }else {
        wait(NULL);
        char asw[10];
        close(fd[1]);//关闭写管道
        int res = read(fd[0], asw, sizeof(char) * 10);
        printf("size:%d, %s", res, asw);
    }
  }
    return 0;
}