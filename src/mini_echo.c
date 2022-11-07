#include "mini_lib.h"
#include <stdio.h>


int main(int argc, char** argv){
   
    if(argc>1){
        for(int i=1;i<argc;i++){
            mini_printf(argv[i]);
            mini_printf(" ");
        }
    }    
    mini_printf("\n");
    mini_exit();
}