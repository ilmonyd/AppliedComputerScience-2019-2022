#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
   int i, proc_no; 
   pid_t pid;
   
   if (argc != 4) {
     perror("The program requires 3 arguments!\n");
     exit(EXIT_FAILURE);
   }
   char* fin = argv[1];
   char* fout = argv[2];
   char* fifo = argv[3];

   unlink(fifo); 

   if (mknod(fifo, S_IFIFO | 0666, 0) < 0) { 
     perror("Error create FIFO\n");
     exit(EXIT_FAILURE);
   }
   for (i = 0; i < 2; i++) { 
      if ((pid = fork()) < 0) {
         perror("Error exec fork\n");
         exit(EXIT_FAILURE);
      }
      else if (pid == 0) {
         proc_no = i;
         break;
      }
   }

   if (pid == 0) {
      if (proc_no == 0) { 
         execl("producent.x", "", fin, fifo, NULL);
      }
      else if (proc_no == 1) {
         execl("konsument.x", "", fout, fifo, NULL);
      }
   }
   else if(wait(0) == -1) {
      perror("wait error");
      exit(EXIT_FAILURE);
   }

   unlink(fifo);
   return 0; 
}
