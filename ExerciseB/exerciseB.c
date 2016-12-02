#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("Please enter a word in argument\n");
        printf("This word will be send through the pipe\n");
        return -1;
    }
    pid_t child1, child2;
    int fd[2];// File descriptors
    char fd0[5];
    char fd1[5];
    char *args1[5];
    char *args2[5];

    int res1, res2, resw, resr;
    int status;

    status = pipe(fd);
    if(status == -1){
        perror("Pipe error");
    }
    //We convert the file descriptors to string to pass those in argument with execve
    sprintf(fd0,"%d",fd[0]);
    sprintf(fd1,"%d",fd[1]);

    child1 = fork();//system call --> internal interrupt

    if(child1 <0){
        perror("Fork Child1");
        return -1;
    }
    else if(child1 ==0){
        args1[0]=fd0;
        args1[1]=fd1;
        args1[2]=argv[1];//The word entered by the user will be transmitted
        args1[3]=NULL;
        resw = execve("./exerciseB_child1", args1, NULL);

        return resw;
    }
    else{

        child2 = fork();//system call --> internal interrupt
        if(child2 <0){
            perror("Fork Child2");
            return -1;
        }
        else if(child2 == 0){
            args2[0]=fd0;
            args2[1]=fd1;
            args2[2]=NULL;
            resr = execve("./exerciseB_child2", args2, NULL);
            printf("%d\n",resr);fflush(stdout);
            return resr;
        }
        else{
            waitpid(child1,&res1,0);
            waitpid(child2,&res2,0);
            printf("Exit status of child1 : %d \n",res1);
            fflush(stdout);
            printf("Exit status of child2 : %d \n",res2);
            fflush(stdout);

            return 0;
        }
    }
}
