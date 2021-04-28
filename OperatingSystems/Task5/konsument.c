#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF 16


int main(int argc, char *argv[]) {
int  file, size, FIFO;
char buff[BUFF + 1];

   if (argc != 3) {
     perror("The program requires 2 arguments!\n");
     exit(EXIT_FAILURE);
   }

   char* fout = argv[1]; 
   char* fifo = argv[2];

   if ((file = open(fout, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
      perror("file open error\n");
      exit(EXIT_FAILURE);
   }

   if ((FIFO = open(fifo, O_RDONLY)) < 0) {
      perror("FIFO open error\n");
      exit(EXIT_FAILURE);
   }

   while ((size = read(FIFO, buff, BUFF)) > 0 ) {
      write(STDOUT_FILENO, "\nFIFO read:", strlen("\nFIFO read:"));
      write(STDOUT_FILENO, buff, size);
      if (write(file, buff, size) < 0) {  
         perror("Error write to fout\n");
         exit(EXIT_FAILURE);
      } 
      else {
         write(STDOUT_FILENO, "\nfile write:", strlen("\n file write:"));
         write(STDOUT_FILENO, buff, size);
      }
      sleep(2);
   } 
   write(STDOUT_FILENO, "FIFO is empty",strlen("FIFO is empty"));

   if (close(file)!=0){
      perror("Error close fout\n");
      exit(EXIT_FAILURE);
   }
   if (close(FIFO)!=0){
      perror("Error close FIFO\n");
      exit(EXIT_FAILURE);
   }
   return 0;
}