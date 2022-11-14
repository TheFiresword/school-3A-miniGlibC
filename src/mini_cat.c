#include "mini_lib.h"


int main(int argc, char** argv){
    

    /**
     * @author: Junior Sedogbo
     * @date: 13/11/2022
     * @version: 1.0
    Programme mini_cat
    Affiche le contenu entier des fichiers qui sont passés en paramètre
    Peut prendre plusieurs fichiers en paramètres
    Si aucun argument n'est passé au programme, il lit en boucle l'entrée standard et l'affiche. C'est le comportement de la vraie commande
    cat.
    La saisie de "exit" permet d'arrêter cette boucle
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
                    //On lit et on affiche le fichier tant qu'on n'est pas arrivés à la fin
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