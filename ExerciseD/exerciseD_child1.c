#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void sig_handler(int signo)
{
  if (signo == SIGTERM)
    printf("Child1 Received SIGTERM\n");
    _exit(0);
}

int main(int argc, char *argv[]){
    char readBuffer2[81];
    char pid[10];
    sprintf(pid,"%ld",(long)getpid());//We send the pid through the pipe, as a string

    char *ptr1;
    char *ptr2;
    int fd[2];
    int fd2[2];
    //File descriptors are reiceived as string we need to convert them to int
    fd[0]=strtol(argv[0], &ptr1, 10);
    fd[1]=strtol(argv[1], &ptr2, 10);
    fd2[0]=strtol(argv[2], &ptr1, 10);
    fd2[1]=strtol(argv[3], &ptr2, 10);
    //child 1 close the read (input) side of the pipe;
    close(fd[0]);
    close(fd2[1]);
    //child 1 send string through the write (output) side of the pipe
    for(;;){
        write(fd[1], pid, (strlen(pid)+1) );
        printf("Child 1 has sent string : %s\n",pid);
        signal(SIGTERM, sig_handler);//Enable child 1 to catch and handle SIGTERM
        read(fd2[0],readBuffer2,sizeof(readBuffer2));
        printf("Child 1 reiceived string : %s\n",readBuffer2);

    }
    return 0;
}
