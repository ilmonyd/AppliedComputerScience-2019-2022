#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//
//  This is a program that test the possibilites of signal handling
//  Created by Oleg Semenov
//

extern const char * const sys_siglist[];

void my_sighandler(int sig) {
    printf("\nSignal number: %d\nSignal name: %s\n", sig, sys_siglist[sig]);
    exit(0);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("The program requires two arguments!\n");
        return 1;
    }

    if (strcmp(argv[1], "default") == 0) {
        if (signal(atol(argv[2]), SIG_DFL) == SIG_ERR){
            perror("Signal function error");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(argv[1], "ignore") == 0) {
        if (signal(atol(argv[2]), SIG_IGN) == SIG_ERR){
            perror("Signal function error");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(argv[1], "custom") == 0) {
        if (signal(atol(argv[2]), my_sighandler) == SIG_ERR){
            perror("Signal function error");
            exit(EXIT_FAILURE);
        }
    }

    else {
        printf("Wrong mode!\n");
        printf("%d",SIGINT);
    }

    printf("PID: %d, PGID: %d\n", (int)getpid(), (int)getpgrp());
    pause();
    
    return 0;
}