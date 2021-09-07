#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int agrc,char* agrv[]){
    if(agrc < 3){
        printf("Illegal parameter");
        exit(1);
    }
    printf("pid:%d\n",getpid());
    int memory = atoi(agrv[1])*1024 *1024;
    int length = memory / sizeof(int);
    int time = atoi(agrv[2]);
    int * num = (int *)malloc(sizeof(int)*length);
    struct timeval begin , now;   
    gettimeofday(&begin,NULL);
    while (1){
        gettimeofday(&now,NULL);
        if(now.tv_sec - begin.tv_sec > time){
            break;
        }
        for(int i = 0;i < length;++i){
            num[i] = i;
        }
    }
    free(num);
    
    return 0;
}