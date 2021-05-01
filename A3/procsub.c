// Add necessary #include's
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int procsub(const char *prog1, const char *prog2, char *prog2_argv[], int status[])
{
    int fds[2];
    if (pipe(fds) == -1) return -1;
    //fds 0 = read
    //fds 1 = write
    pid_t child1;
    pid_t child2;

    child2 = fork();
    switch(child2) {
        case(-1):
            return -1;
            break;

        case(0):
            close(fds[0]);
            dup2(fds[1], 1);
            if (execvp(prog2, prog2_argv) == -1) exit(37);
            exit(0);
            break;

        default: 
            close(fds[1]);
            waitpid(0, &status[1], 0);
            child1 = fork();
            switch(child1) {}
            if (child1 == -1) {
                return -1;
            }
            else if (child1 == 0) {
                close(fds[1]);
                char input[1024];
                sprintf(input, "/dev/fd/%d", fds[0]);
                if (execlp(prog1, prog1, input, NULL) == -1)  exit(37);
                exit(0);
            }
            else {
                close(fds[0]);
                waitpid(0, &status[0], 0);
            }
    }
    return 0;
}
