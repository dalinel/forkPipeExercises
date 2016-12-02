#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char readBuffer[80];
    char *ptr1;
    char *ptr2;
    int fd[2];
    //File descriptors are reiceived as string we need to convert them to int
    fd[0]=strtol(argv[0], &ptr1, 10);
    fd[1]=strtol(argv[1], &ptr2, 10);
    //child 2 close the output side
    close(fd[1]);
    //child 2 read from the input side
    read(fd[0],readBuffer,sizeof(readBuffer));
    printf("Child 2 has reiceved string : %s\n",readBuffer);
    return 0;
}
