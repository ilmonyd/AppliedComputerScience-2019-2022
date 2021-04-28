#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF 16




int main(int argc, char *argv[]){
int file, size, FIFO;

char buff[BUFF+1];
   if (argc != 3){
     perror("Program requires two arguments!\n");
     exit(EXIT_FAILURE);
   }
   char* fin = argv[1]; 
   char* fifo = argv[2];

   if ((file = open(fin, O_RDONLY)) < 0) { 
      perror("file open error\n");
      exit(EXIT_FAILURE);
   }
   if ((FIFO = open(fifo, O_WRONLY)) < 0){ 
     perror("FIFO open error\n");
     exit(EXIT_FAILURE);
   }
   while((size = read(file, buff, BUFF)) > 0){
      write(STDOUT_FILENO, "\nFIFO write:", strlen("\nFIFO write:"));
      write(STDOUT_FILENO, buff, size);
      if(write(FIFO, buff, size) == -1 ){
         perror("FIFO write error\n");
         exit(EXIT_FAILURE) ;
      }
      else { 
         write(STDOUT_FILENO, "\nfile read:", strlen("\nfile read:"));
         write(STDOUT_FILENO, buff, size);
      } 
      sleep(2); 
   }
   if (close(file)!=0){
      perror("file close error\n");
      exit(EXIT_FAILURE);
   }
   if (close(FIFO)!=0){ 
      perror("FIFO close error\n");
      exit(EXIT_FAILURE);
   }
   return 0; 
}