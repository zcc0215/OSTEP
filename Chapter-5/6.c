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
        sleep(1);
        printf("Child\n");
    }else{
        int wc = waitpid(pid,NULL,WNOHANG);//option = 0为默认，行为与wait一致
        printf("WC=%d\n",wc);
    }
    return 0;
}