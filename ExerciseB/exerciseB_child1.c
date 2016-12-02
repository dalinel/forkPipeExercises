#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *ptr1;
    char *ptr2;
    int fd[2];
    //File descriptors are reiceived as string we need to convert them to int
    fd[0]=strtol(argv[0], &ptr1, 10);
    fd[1]=strtol(argv[1], &ptr2, 10);
    //child 1 close the read (input) side of the pipe;
    close(fd[0]);
    //child 1 send string through the write (output) side of the pipe
    write(fd[1], argv[2], (strlen(argv[2])+1) );
    printf("Child 1 has sent string : %s\n",argv[2]);
    return 0;
}
