#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void fetch_data() {
    // UID,GID,PID,PPID and PGID
    pid_t pid = getpid();
    printf("UID: %d\nGID: %d\nPID: %d\nPPID: %d\nPGID: %d\n", (int)getuid(), (int)getgid(), (int)pid, (int)getppid(), (int)getpgid(pid));
}

int main() {
    fetch_data(); // print the IDs of the current process
    return 0;
}