#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(char argc,char *argv[]){
  int num = 1;
  char letter;
  if(argc == 1){
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }
  for (int i = 1; i<argc; ++i){
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        while(fread(&num,1,4,fp) == 4){
            fread(&letter, 1, 1, fp);
            for(int j=0;j<num;j++){
                printf("%c",letter);
            }
        }
        fclose(fp);
  }
  return 0;
}