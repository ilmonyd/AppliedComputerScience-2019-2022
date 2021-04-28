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


int main() {
    fetch_id();
    return 0;
}