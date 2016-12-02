#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("COMMANDS\n");
    printf("Press enter to keep sending and reiceiving messages\n");
    printf("Press a followed by enter to exit\n");
    printf("Press enter to start ....\n");
    char c;
    if((c=getchar()) == 'c'){
    }
    pid_t child1, child2;
    int fd[2];// File descriptors
    int fd2[2];// File descriptors
    int res1, res2, resr, resw;
    int status;

    char fd10[5];
    char fd11[5];
    char fd20[5];
    char fd21[5];
    char *args1[5];
    char *args2[5];

    status = pipe(fd);
    if(status == -1){
        perror("Pipe error");
    }
    //We convert the file descriptors to string to pass those in argument with execve
    sprintf(fd10,"%d",fd[0]);
    sprintf(fd11,"%d",fd[1]);

    status = pipe(fd2);
    if(status == -1){
        perror("Pipe2 error");
    }
    //We convert the file descriptors to string to pass those in argument with execve
    sprintf(fd20,"%d",fd2[0]);
    sprintf(fd21,"%d",fd2[1]);

    child1 = fork();//system call --> internal interrupt

    if(child1 <0){
        perror("Fork Child1");
        return -1;
    }
    else if(child1 ==0){
        args1[0]=fd10;
        args1[1]=fd11;
        args1[2]=fd20;
        args1[3]=fd21;
        args1[5]=NULL;
        resw = execve("./exerciseD_child1", args1, NULL);
        return resw;
    }
    else{

        child2 = fork();//system call --> internal interrupt
        if(child2 <0){
            perror("Fork Child2");
            return -1;
        }
        else if(child2 == 0){
            args2[0]=fd10;
            args2[1]=fd11;
            args2[2]=fd20;
            args2[3]=fd21;
            args2[5]=NULL;
            resr = execve("./exerciseD_child2", args2, NULL);
            return resr;
        }
        else{
            waitpid(child1,&res1,0);
            printf("Exit status of child1 : %d \n",res1);
            fflush(stdout);
            waitpid(child2,&res2,0);
            printf("Exit status of child2 : %d \n",res2);
            fflush(stdout);
            return 0;
        }
    }
}
