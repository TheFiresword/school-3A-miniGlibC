#include "mini_lib.h"


int main(int argc, char** argv){
    /*
    Programme mini_cat
    Affiche le contenu entier des fichiers qui sont passés en paramètre
    Peut prendre plusieurs fichiers en paramètres
    */
    extern int IOBUFFER_SIZE;
    char* buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);

    if(buffer!=(void*)-1){

        if(argc>1){
            int count=0;
            for(int i=1; i<argc;i++){
                MYFILE* fd=mini_fopen(argv[i],'r');
                if(fd!=(void*)-1){
                    count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                    while(count!=-1 && count!=0){
                        mini_printf(buffer);
                        count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                    }
                    mini_printf("\n");
                    mini_fclose(fd);
                }          
            }   
        }
        else{
            while (1){ 
                mini_scanf(buffer,IOBUFFER_SIZE);
                if(mini_strcmp(buffer,"exit")==0)
                    break;
                mini_printf(buffer);
                mini_printf("\n");
            }
        }
        mini_free(buffer);
    }
    

    mini_exit();
}   