#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int counter;

static void body(const char *s)
{
    int i;
    for(i=0; i<5; i++){
        sleep(1);
        printf("%s : %d\n",s,counter++);
    }
}

int main(int argc, char *argv[])
{
    pid_t child;
    int res;
    counter = 10;
    child = fork();

    if(child <0){
        perror("Fork");
        return -1;
    }
    if(child==0){
        body("Child");
        return 0;
        //The child terminates with an exit status of 0 (everything went well)
    }

    body("Father");
    wait(&res);
    //The father wait until the child terminates. The exit status of the child is stored in res
    printf("Exit status of child : %d \n",res);
    fflush(stdout);
    return 0;
}
