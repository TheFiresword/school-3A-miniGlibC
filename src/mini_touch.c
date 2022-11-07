#include "mini_lib.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARG_MAX_STRLEN 20

static void remove_quotes(char* chaine){
    /*
    HAHA i just figured out this function was useles
    SADDDDD :(
    */
    int length=mini_strlen(chaine);
    char* rm_chaine=mini_calloc(sizeof(char),length);
    if(rm_chaine!=(void*)-1){
        int j=0;
        for(int i=0;i<length;i++){
            if(chaine[i]=='\"'){
                mini_printf("ouiii\n");
            }
            else{
                rm_chaine[j]=chaine[i];
                j++;
            }
        }
        mini_free(chaine);
        chaine=rm_chaine;
    }
    
}

int main(int argc, char** argv){
    if(argc>1){
        char* file=mini_calloc(sizeof(char),ARG_MAX_STRLEN);
        if(file!=(void*)-1){
            remove_quotes(argv[1]);
            mini_strcpy(argv[1],file);
            //On vérifie si le fichier existe dans le répertoire dans lequel on est
            if(access(file,F_OK)==-1){
                int error=(int)errno;
                int tempo;
                if((tempo=open(file,O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH))!=-1)
                    close(tempo);
                else{
                    error=(int)errno;
                }
            }
            mini_free(file);
        }
    
    }

    mini_exit();
}

