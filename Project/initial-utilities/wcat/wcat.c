#include <stdio.h>
#include <stdlib.h>
#define size 100
int main(char argc,char *argv[]){
    if (argc == 1){
        exit(0);
    }
    char buf[size];
    for (int i = 1; i < argc; ++i){
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while (fgets(buf,size,fp) !=NULL){
            printf("%s",buf);
        }
        fclose(fp);
        
    }
    return 0;
}