//
//  This is a program that test the possibilites of using fork() with execl()
//  Created by Oleg Semenov
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


void fetch_id() { // printing out ID's of the process
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
}


int main(int argc, char* argv[]){
    if (argc != 3) { // checking if the arguments number is correct
        printf("Invalid number of arguments!\n");
        printf("The program needs two arguments - path to an executable and it's name\n");
        printf("To test the program you can use for example './main.x /bin/ls ls\n'");
        exit(1);
    }

    fetch_id(); // fetching the ID's of the main process
    printf("----------------------------------------------------------\n");

    int i;
    for (i = 0; i < 3; i++) {
        switch(fork()) {
            case -1:
                perror("fork error");
                exit(2);
            case 0: // tasks for child process
                execl(argv[1], argv[2], NULL); // using main function arguments in execl to launch a new program in a child process
                perror("exec error");          
            default: // tasks for parent process
                sleep(1);
        };
    }
    for (i = 0; i < 3; i++) {
        if (wait(NULL) == -1) { // waiting for child processes to terminate
            perror("wait error");
            exit(3);
        }
    }

    return 0;
}