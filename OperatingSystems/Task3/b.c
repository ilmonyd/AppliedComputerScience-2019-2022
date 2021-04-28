#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

//
//  This is a program that test the possibilites of signal handling
//  Created by Oleg Semenov
//

int main(int argc, char *argv[]) {
    pid_t pid = 0;
    if (argc != 3) {
        printf("The program requires two arguments!\n");
        return 1;
    }
    switch (fork()) {
        case -1:
            perror("fork error");
            return 1;
        case 0:
            pid = getpid();
            execl("./a.x", "a", argv[1], argv[2], NULL);
            perror("exec error");
            _exit(0);
        default:
            sleep(2);
            switch (kill(pid, 0)) {
                case 0:
                    kill(pid, atoi(argv[2]));
                case -1:
                    printf("No such process\n");
                    return 3;
            }
            break;
    }

    return 0;
}