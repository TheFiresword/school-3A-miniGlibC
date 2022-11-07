#include "mini_lib.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 512

static void copy_file(char *src, char *dst){
   MYFILE* fdsrc, *fddst;
   char buffer[BUFSIZE];
   int nchar;
   
   fdsrc=mini_fopen(src, 'r');
   fddst=mini_fopen(dst, 'c');
   if(fddst!=NULL && fdsrc!=NULL){
        while((nchar = mini_fread(buffer,sizeof(char),BUFSIZE,fdsrc))!=0 && nchar!=-1)
            mini_fwrite(buffer,sizeof(char),BUFSIZE,fddst);
        
   }
   mini_fclose(fdsrc);
   mini_fclose(fdsrc);
}

int main(int argc, char** argv){
    
    if(argc<3){
        if(argc<2)
            mini_printf("cp: missing file operand\nTry \'cp --help\' for more information.\n");
        else{
             mini_printf("cp: missing destination file operand after " );
             mini_printf(argv[1]);
             mini_printf("\nTry \'cp --help\' for more information.\n ");
        }
        mini_exit();
    }
    char* src = argv[1];
    char * dst = argv[2];
    copy_file(src, dst);

    mini_exit();
}
