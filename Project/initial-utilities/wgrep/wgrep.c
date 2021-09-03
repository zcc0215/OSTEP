#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

int main(char argc,char *argv[]){
    if (argc == 1){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }else if (argc == 2){
        char * search = argv[1];
        if (strcmp(search, "") == 0){
            exit(0);
        }
        char buf[size];
        while (fgets(buf,size,stdin) !=NULL){
            if(strstr(buf,search) !=NULL){
                   printf("%s",buf);
               }
        }
    }else {
        char * search = argv[1];
        if (strcmp(search, "") == 0){
            exit(0);
        }
        for (int i = 2; i < argc; ++i){
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
           }
           char * line = NULL;
           size_t len = 0;
           ssize_t read;
           while(read = getline(&line,&len,fp) != -1){
               if(strstr(line,search) !=NULL){
                   printf("%s",line);
               }
           }
           fclose(fp);
        }
    }
    return 0;
}