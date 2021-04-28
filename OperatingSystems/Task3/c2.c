#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//
//  This is a program that test the possibilites of signal handling
//  Created by Oleg Semenov
//

int main(int argc, char *argv[]) {

    pid_t pid = getpid();

    setpgid(pid, 0);

    for (int i = 0; i < 3; i++) {
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
                if (signal(atol(argv[2]), SIG_IGN) == SIG_ERR){
                    perror("Signal function error");
                    exit(EXIT_FAILURE);
                }
                break;
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    return 0;
}