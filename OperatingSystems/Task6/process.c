#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mysem.h"

int main(int argc, char* argv[]){
int file, rez;
char str[5];
sem_t* sem;

  if (argc != 2) {
     perror("Wrong arguments count!");
     EXIT_ERROR;
  }

  srand(time(NULL));
  sem = semOpen(SEM_NAME);

  printf("Process before critical section, semaphore value = %d\n", getpid(), semGV(sem));
  for(int i = 0 ; i < atoi(argv[1]) ; i++) {

      if (SEM_SYNC) semWait(sem); // ждем семафор
      printf("=== Process during critical section, semaphore value = = %d ===\n", getpid(), semGV(sem));

      file = open(FILE_NAME, O_RDONLY);
      if (file < 0) {
         perror("Error open file");
         EXIT_ERROR;
      }

      memset(str, '\0', sizeof(str));

      rez = read(file, str, sizeof(str));
      if (rez < 0) {
         perror("Error read from file");
         EXIT_ERROR;
      }

      rez = atoi(str);
      rez++;
      sprintf(str, "%u", rez);

      rez = close(file);
      if (rez < 0) {
         perror("Error close file");
         EXIT_ERROR;
      }

      PAUSE;

      file = open(FILE_NAME, O_WRONLY);
      if (file < 0) {
         perror("Error open file");
         EXIT_ERROR;
      }

      rez = write(file, str, strlen(str));
      if (rez != strlen(str)) {
         perror("Error write to file");
         EXIT_ERROR;
      }

      rez = close(file);
      if (rez < 0) {
         perror("Error close file");
         EXIT_ERROR;
      }

      if (SEM_SYNC) semPost(sem);

      printf("Process %d after critical section, semaphore value = %d\n", getpid(), semGV(sem));
    }
  
  semClose(sem);
}
