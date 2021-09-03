#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int file_counter = 1;
  char letter;
  char next_letter;
  int letter_count = 0;

  if(argc == 1){
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }
  
  while (file_counter < argc) {
    fp = fopen(argv[file_counter], "r");
    if(fp == NULL){
      printf("wzip: file1 [file2 ...]\n");
      exit(1);
    }

    letter = getc(fp);
    do {
      letter_count++;
      next_letter = getc(fp);
      if(next_letter != letter && next_letter != EOF){
        fwrite(&letter_count, 4, 1, stdout);
        fwrite(&letter, 1, 1, stdout);
        letter_count = 0;
        letter = next_letter;
      }
    } while(next_letter != EOF);
  
    fclose(fp);
    file_counter++;
  }
  fwrite(&letter_count, 4, 1, stdout);
  fwrite(&letter, 1, 1, stdout);
  exit(0);
}