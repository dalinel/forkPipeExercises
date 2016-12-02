#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int counter;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("Parent Received SIGINT\n");
    fflush(stdout);
}

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
        kill(getppid(),SIGINT);// The child ask the father to terminates
        return 0;
        //The child terminates with an exit status of 0 (everything went well)
    }

    body("Father");
    signal(SIGINT, sig_handler) ;//The father reiceive and handle the signal
    wait(&res);
    printf("Exit status of child : %d \n",res);
    fflush(stdout);

    return 0;
}
