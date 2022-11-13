#include "mini_lib.h"

/*
Reimplémentation de la commande système grep
peut prendre 2 ou plus paramètres
Param1: mot recherché
Parm2...n: fichiers dans lequels il faut chercher
*/
int main(int argc, char** argv){
    if(argc==1){
        mini_printf("Usage: mini_grep [OPTION]... PATTERNS [FILE]...\nTry 'mini_grep --help' for more information.\n");
        mini_exit();
    }
    extern int IOBUFFER_SIZE;
    char* buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);
    char* pattern=argv[1];

    if(buffer!=(void*)-1){ 
        if(argc==2){
            while (1){ 
                mini_scanf(buffer,IOBUFFER_SIZE);
                if(mini_strcmp(buffer,"exit")==0)
                    break;
                char* result=mini_searchlinewithpattern(buffer,pattern);
                if(result!=(void*)-1){
                    mini_printf(result);
                    mini_printf("\n");
                }
            }
            mini_exit();
        }

        if(argc>2){
            for(int i=2;i<argc;i++){
                char* file=argv[i];
                MYFILE* fd=mini_fopen(file,'r');

                if(fd!=(void*)-1){
                    
                    int count=0;
                    count=mini_freadline(buffer,sizeof(char),fd);
                    mini_printf(file);
                    mini_printf(":");
                    while(count!=-1 && count!=0){
                        char* result=mini_searchlinewithpattern(buffer,pattern);
                        if(result!=(void*)-1){
                            mini_printf(result);
                            mini_printf("\n");
                        }
                        count=mini_freadline(buffer,sizeof(char),fd);
                    }
                    mini_fclose(fd);
                }
                mini_printf("\n");
            }        
            mini_exit();
        }
        
        mini_free(buffer);
    }
    mini_exit();
}