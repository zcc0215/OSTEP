#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(char argc,char * argv[]){
    int pid = fork();
    if (pid < 0){
        fprintf(stderr,"fork fail\n");
        exit(1);
    }else if (pid == 0){
        char * myargs[3];
        myargs[0]  = strdup("ls");
        myargs[1]  = strdup("-a");
        myargs[2]  = NULL;
        execvp(myargs[0],myargs);
    }else {
        int wc = wait(NULL);
    }
    return 0;
}
/** execl() execv() 参数是否由数组传递
 *  execle() execve() 参数是否带环境变量
 *  execlp() execvp() 命令由环境变量自动查找，无需指定完整路径
 *  execvpe() 带环境变量由指针传递参数传递变量名 **/