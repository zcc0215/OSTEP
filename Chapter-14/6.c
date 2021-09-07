#include <stdio.h>
#include <stdlib.h>

int main (char argc,char* argv[]){
    int *data =malloc(sizeof(int)* 100);
    data[0] = 0;
    free(data);
    printf("%d\n",data[0]);
    return 0;
}