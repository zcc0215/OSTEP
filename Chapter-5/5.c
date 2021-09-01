#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(char argc,char * argv[]){
    int pid = fork();
    if (pid < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if (pid == 0){
        int wc = wait(NULL);
        printf("WC=%d,ChildPid=%d,ParentPid=%d\n",wc,(int)getpid(),(int)getppid());
    }else{
        int wc = wait(NULL);
        printf("WC=%d,ChildPid=%d,ParentPid=%d\n",wc,pid,(int)getpid());
    }
    return 0;
}