#include <stdio.h>
#include <stdlib.h>

int main (char argc,char* argv[]){
    int *data =malloc(sizeof(int)* 100);
    data[100] = 0;
    return 0;
}