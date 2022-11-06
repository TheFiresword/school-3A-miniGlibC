#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char** argv){
    /*
    int* memory=calloc(2,sizeof(int));
    memory[0]=2;
    memory[1]=5;
    free(memory);
    */
   int fd=open("../testFile.txt",O_RDONLY);
   write(fd,"maman",5);
   write(fd,"maman",5);

    return 0;
}