#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
    /*
    int* memory=calloc(2,sizeof(int));
    memory[0]=2;
    memory[1]=5;
    free(memory);
    */
    void* first=sbrk(0);

    int* memory=malloc(sizeof(int)*2);
 
    memory[0]=1;
    memory[1]=2;

    void* second=sbrk(0);
    free(memory);

   
    int * third=malloc(0);
    //int * third=sbrk(sizeof(int)*2);

    printf("%p %p %p\n",first, second, third);
    return 0;
}