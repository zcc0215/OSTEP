#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(char argc,char * argv[]){
    int pid = vfork();
    if (pid < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if( pid == 0){
        printf("hello\n");
        exit(0);
    }else{
        printf("goodbye\n");
    }
    return 0;
}