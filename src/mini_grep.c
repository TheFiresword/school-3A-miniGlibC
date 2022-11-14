#include "mini_lib.h"

/**
* @author: Junior Sedogbo
     * @date: 13/11/2022
     * @version: 1.0
Reimplémentation de la commande système grep
peut prendre 2 ou plus paramètres
Param1: mot recherché
Parm2...n: fichiers dans lequels il faut chercher
Si 1 seul argument est passé au programme, il lit en boucle l'entrée standard et l'affiche si l'argument passé se trouve dans la saisie. 
La saisie de "exit" permet d'arrêter cette boucle
*/
int main(int argc, char** argv){
    
    /*
    Pour faire la recherche de mot dans un fichier, je lis ligne par ligne le fichier avec ma fonction mini_freadline() et je vérifie si
    le mot est présent dans ces lignes avec ma fonction mini_searchlinewithpattern().
    Si le mot est présent, ma fonction renvoie la ligne et je l'affiche.
    */

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
                    count=mini_freadline(buffer,fd);
                    mini_printf(file);
                    mini_printf(":");
                    while(count!=-1 && count!=0){
                        char* result=mini_searchlinewithpattern(buffer,pattern);
                        if(result!=(void*)-1){
                            mini_printf(result);
                            mini_printf("\n");
                        }
                        count=mini_freadline(buffer,fd);
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