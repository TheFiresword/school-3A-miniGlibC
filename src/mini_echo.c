#include "mini_lib.h"
/*
Reimplementation de la commande système echo
affiche à l'écran la chaine passée en paramètre, qui peut contenir des espaces
*/

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