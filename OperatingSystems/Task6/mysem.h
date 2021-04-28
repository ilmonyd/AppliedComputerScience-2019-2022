#ifndef MYLIB_H
#define MYLIB_H

#include <semaphore.h>
#define SEM_NAME "MYSEM"
#define FILE_NAME "number.txt"
#define EXIT_ERROR exit(EXIT_FAILURE)
#define PAUSE usleep(rand()%999999)
#define SEM_SYNC 1

sem_t* semCreate(const char*, int);
sem_t* semOpen(const char*);
int semClose(sem_t*);
int semWait(sem_t*);
int semPost(sem_t*);
int semUnlink(const char*);
int semGV(sem_t*);

#endif
