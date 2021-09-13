#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

char * coms[10];
char * compath[10] = {"/bin/"};
int  redirectfile = -1;
void print_wish(FILE* file){
    if(file ==stdin){    
        printf("wish>");
    } 
}
void wish_error(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
    
}
void comsplit(char * line){
    for (size_t i = 0; i < 10; i++){
        coms[i] = NULL;
    }    
    char * d =" ";
    char * result = NULL;
    result = strtok(line, d);
    int i = 0;
    while (result != NULL){
        if (strcmp(result,">") == 0){
            result = strtok(NULL, d);
            redirectfile = open(result,O_WRONLY | O_CREAT |O_TRUNC);
            if(redirectfile ==-1){
                wish_error();
            }
            break;
        }
        coms[i] = result;        
        ++i;
        result = strtok(NULL, d);
    }

}
void comecec(char * path){
    if(redirectfile > 0){
        dup2(redirectfile,STDOUT_FILENO);
        dup2(redirectfile,STDERR_FILENO);
    }
    execv(path,coms);
}
void actioncom(char * path,int parallelflag){
    if(parallelflag){
        comecec(path);
    }else{
        pid_t pid = fork();
        if(pid == 0){
            comecec(path);
        }else{
            wait(NULL);
        }
    }
}
void execcom(int parallelflag){
    int i = 0;
    int falg = 1;
    char b [40] ={0};
    while (compath[i]){
        memset(b, '\0', sizeof(b));
        strcat(b,compath[i]);
        strcat(b,coms[0]);
        char * a = b;
        if(access(b,X_OK) == 0){
            falg = 0;
            actioncom(b,parallelflag);
            break;
        }
        ++i;
    }
    if(falg){
        wish_error();
    }
    
}
void readline(FILE* file){
    while (1){
        print_wish(file);

        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        while(read = getline(&line,&len,file) != -1){
            if(strcmp(line,"\n") == 0){
                print_wish(file);
                continue;  
            }

            redirectfile =-1;
            char * com = strtok(line, "\n");
            
            if(strchr(com,'&')!= NULL){
                char * d ="&";
                char * result = NULL;
                result = strtok(com, d);
                while (result != NULL){
                    pid_t pid = fork();
                    if(pid == 0){
                        comsplit(result);
                        execcom(1);
                    }
                    result = strtok(NULL,d);
                }
                while (wait(NULL)!=-1){}
                
                print_wish(file);
                continue;  
            }else{
                comsplit(com);
            }
            
            if(strcmp(coms[0],"exit") == 0){
                if(coms[1] !=NULL && coms[1] !=0){
                    wish_error();
                }else{
                    free(line);
                    exit(0);
                }
                print_wish(file);
                continue;               
            }

            if(strcmp(coms[0],"cd") == 0){
                if(coms[1] !=NULL && coms[2] ==NULL){
                    if(chdir(coms[1]) !=0){
                        wish_error();
                    }
                }else{
                    wish_error();
                }
                print_wish(file);
                continue;
            }

            if(strcmp(coms[0],"path") == 0){
                int i = 1;  
                for (size_t i = 0; i < 10; i++){
                    compath[i] = NULL;
                }                
                while (coms[i]){
                    compath[i - 1] = coms[i];
                    ++i;
                }
                print_wish(file);
                continue;
            }

            execcom(0);

            print_wish(file);
        }
        free(line);
    }    
}
int main(char argc,char* argv[]){   
    if(argc == 1){
       readline(stdin);
    }else if(argc ==2){
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            wish_error();
            exit(1);
        }
        readline(fp);
        fclose(fp);
    }
    else{
        wish_error();
        exit(1);
    }
    exit(0);
}