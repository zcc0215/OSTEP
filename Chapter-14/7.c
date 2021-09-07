#include <stdio.h>
#include <stdlib.h>

int main (char argc,char* argv[]){
    int *data =malloc(sizeof(int)* 100);
    free(&data[10]);
    return 0;
}