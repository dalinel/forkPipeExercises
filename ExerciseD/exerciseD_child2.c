#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

pid_t pidChild1;


int main(int argc, char *argv[]){

    char readBuffer[80];
    char *ptr1;
    char *ptr2;
    int fd[2];
    int fd2[2];
    char c;
    //File descriptors are reiceived as string we need to convert them to int
    fd[0]=strtol(argv[0], &ptr1, 10);
    fd[1]=strtol(argv[1], &ptr2, 10);
    fd2[0]=strtol(argv[2], &ptr1, 10);
    fd2[1]=strtol(argv[3], &ptr2, 10);
    //child 2 close the output side
    close(fd[1]);
    close(fd2[0]);
    //child 2 read from the input side
    for(;;){
        int size = read(fd[0],readBuffer,sizeof(readBuffer));
        printf("Child 2 has received string : %s\n",readBuffer);

        pidChild1 = (pid_t) strtol(readBuffer, &ptr1, 10);

        write(fd2[1], readBuffer, (strlen(readBuffer)+1) );
        printf("Child 2 has sent string : %s\n",readBuffer);

        if((c=getchar()) == 'a'){
            //If the user press a child2 will send SIGTERM to Child1
            //If not the loop will continue after a keyboard entry from the user
            kill(pidChild1,SIGTERM);
            printf("Child2 has sent SIGTERM to Child1\n");
            _exit(0);

       }

    }
    return 0;
}
