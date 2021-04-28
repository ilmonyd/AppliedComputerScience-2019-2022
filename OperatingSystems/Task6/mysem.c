#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#define EXIT_ERROR exit(EXIT_FAILURE)

sem_t * semCreate(char * semid, int value) {
  sem_t * sem = sem_open(semid, O_CREAT | O_EXCL, 0777, 0);
  if (sem == SEM_FAILED) {
     perror("Call semCreate error");
     EXIT_ERROR;
  }
  for (int i = 0; i < value; i++) semPost(sem);
  return sem;
}

sem_t * semOpen(const char * semid){
  sem_t * sem = sem_open(semid, 0);
  if (sem == SEM_FAILED) {
     perror("Call semOpen error");
     EXIT_ERROR;
  }  else return sem;
}
   
void semClose(sem_t * sem){
  int rez = sem_close(sem);
  if (rez < 0) {
     perror("Call semClose error");
     EXIT_ERROR;
  }
}

int semUnlink(const char * semid){
  int rez = sem_unlink(semid);
  if (rez < 0) {
     perror("Call semUnlink error");
     //EXIT_ERROR;
  }
}

int semGV(sem_t * sem) {
  int value;
  if (sem_getvalue(sem, &value) < 0) {
      perror("Call semGV error");
      EXIT_ERROR;
  } else return value;
}

void semWait(sem_t * sem){
  int rez = sem_wait(sem);
  if (rez < 0) {
      perror("Call semWait error");
      EXIT_ERROR;
  }
}

void semPost(sem_t * sem){
  int rez = sem_post(sem);
  if (rez < 0) {
      perror("Call semPost error");
      EXIT_ERROR;
  }
}
