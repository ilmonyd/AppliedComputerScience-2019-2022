#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void fetch_data() {
    // UID,GID,PID,PPID and PGID
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", (int)getuid(), (int)getgid(), (int)getpid(), (int)getppid(), (int)getpgrp());
}

int main() {
    printf("The main process: ");
    fetch_data();

    int i;
    for (i = 0; i < 3; i++) { // forking 3 times
        switch (fork()) {
            case -1: // catching the fork error
                perror("fork error");
                exit(1);
            case 0: // tasks for child processes
                fetch_data();
            default: // tasks for parent process
                wait(0);
        }
    }
    
    return 0;
}