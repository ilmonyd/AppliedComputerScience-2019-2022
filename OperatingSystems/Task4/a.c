#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


void producer(char* fname, int stream[]) {
    int fd;
    char* buf;
    int bytes = 0;

    buf = malloc(30);

    if (-1 == close(stream[0])) {
        perror("file descriptor close error");
        exit(1);
    }
 
    fd = open(fname, O_RDWR | O_CREAT, 0777);

    while ((bytes = read(fd, buf, 30)) > 0) {
        write(stream[1], buf, 30);
        sleep(1);
    }

    if (close(fd) == -1) {
        perror("file descriptor close error");
        exit(1);
    }
          
    if (close(stream[1]) == -1) {
        perror("file descriptor close error");
        exit(1);
    }

	close(stream[1]);
}


void consumer(char* fname, int stream[]) {   
    int fd;
    char* buf;

    buf = malloc(30);

    if (close(stream[1]) == -1) {
        perror("file descriptor close error");
        exit(1);
    }
   
    fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0777);

    while (read(stream[0], buf, 30) > 0) {
        write(fd, buf, 30);

        printf("——————————————————————————————\n");
        printf("%s\n",buf);
        printf("——————————————————————————————\n");

        sleep(1);
    }

    if (close(stream[0]) == -1) {
        perror("file descriptor close error");    
        exit(1);
    }
    if (close(fd) == -1) {
        perror("file descriptor close error");
        exit(1);
    }
}

int main(int argc, char* argv[]) {   
    pid_t pid;
    int stream[2];

    char* file_in;
    char* file_out;

    if (argc < 2) {
        printf("The program requires two arguments\n");
        exit(1);
    }

    file_in = argv[1];
    file_out = argv[2];
    
    if (pipe(stream) == -1) {
        perror("error creating pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            consumer(file_out, stream);
            break;
        default:
        producer(file_in, stream);      
    }

    wait(NULL);
    
    return 0;
}
