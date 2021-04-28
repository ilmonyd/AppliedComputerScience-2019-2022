#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "mysem.h"

int main(int argc, char* argv[]){
char str[3];
int i, rez;
int file;
sem_t * sem;

  if (argc != 4) {
     perror("Wrong number of arguments!");
     EXIT_ERROR;
  }

  semUnlink(SEM_NAME);
  sem = semCreate(SEM_NAME, 1);

  file = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if (file < 0) {
     perror("Open file error");
     EXIT_ERROR;
  }

  rez = write(file, "0", 1);
  if (rez != 1) {
     perror("Write to file error");
     EXIT_ERROR;
  }

  rez = close(file);
  if (rez < 0) {
     perror("Close file error");
     EXIT_ERROR;
  }

  for (i = 0 ; i < atoi(argv[2]); i++) {
    rez = fork();
    if (rez < 0) {
       perror("Call fork error");
       EXIT_ERROR;
    } else if (rez == 0) {
       execl(argv[1], argv[1], argv[3], NULL);
    }
  }

  for (int i = 0; i < atoi(argv[2]); i++) {
      wait(NULL);
  }

  if (semUnlink(SEM_NAME) < 0) {
     perror("semUnlink");
     EXIT_ERROR;
  }

  file = open(FILE_NAME, O_RDONLY);
  if (file < 0) {
     perror("Open file error");
     EXIT_ERROR;
  }

  rez = read(file, str, sizeof(str));
  if (rez < 0) {
     perror("Read from file error");
     EXIT_ERROR;
  }

  rez = close(file);
  if (rez < 0) {
     perror("Close file error");
     EXIT_ERROR;
  }

  rez = atoi(argv[2]) * atoi(argv[3]);
  printf("Counter value should be = %d\n", rez);
  printf("Counter value received = %s\n", str);

  if (rez == atoi(str)) {
     puts("True");
  }
  else {
     puts("False");
  }
}
