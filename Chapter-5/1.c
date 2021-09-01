#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(char argc,char * argv[]){
    int num = 100;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if (rc == 0){
        num += 1;
        printf("Child num=%d\n",num);
    }else{
        num += 2;
        printf("Parent num=%d\n",num);
    }
    return 0;
}