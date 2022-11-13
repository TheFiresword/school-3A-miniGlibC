#include "mini_lib.h"
#include <unistd.h>

//N'affiche pas dans le bon ordre

/*
Reimplementation de la commande tail
Prend en paramètre un ou plusieurs fichiers
Affiche les N dernières lignes de chaque fichier
L'option -n N peut être positionné n'importe où dans la commande
*/

int main(int argc, char** argv){

int i=1;
int N=-1;
    for(i=1;i<argc;i++){
        if(mini_strcmp(argv[i],"-n")==0 && mini_strlen(argv[i])==2){  

            if(i<argc-1){
                char* N_char=argv[i+1];
                N=mini_atoi(N_char,0);
                if(N==-1){
                    //L'utilisateur n'a pas spécifié le nombre N de lignes
                    //Ou a mal spécifié ce nombre
                    //ex: 14fsf
                    mini_printf("tail: invalid number of lines: ");
                    mini_printf(N_char);
                    mini_printf("\n");
                    mini_exit();
                }
                else if(N==0){
                    //L'utilisateur a spécifié le nombre 0
                    mini_exit();
                }
                else{
                    //Nombre de lignes différent de 0
                    //on fait ce qu'on a à faire à l'extérieur de la boucle
                    break;
                }

            }
            else{
                mini_printf("tail: option requires an argument -- 'n'\nTry 'mini_tail --help' for more information\n");
                mini_exit();
            }
        }
    }
  
    if(N!=-1){
        //Ça veut dire qu'on est passé 1 fois dans la condition if de la boucle et que un nombre de lignes est spécifié
        //On lit les N dernières lignes des fichiers spécifiés, c'est à dire tous les autres arguments autres que -n et N
       
         for(int j=1;j<argc;j++){
            if(j!=i && j!=i+1){
                char* file=argv[j];

                extern int IOBUFFER_SIZE;
                char* buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);
                int count_caracters=0;
                int count_lines=0;

                MYFILE* fd=mini_fopen(file,'r');
                int total_lines=mini_countlines(file);
        
                if(fd!=(void*)-1 && buffer!=(void*)-1){
                    mini_printf("==> ");
                    mini_printf(file);
                    mini_printf(" <==\n");

                    if(total_lines==-1 || total_lines==0){
                        mini_free(buffer);
                        mini_fclose(fd);
                        mini_exit();
                    }

                    if(total_lines<N){
                        //on affiche toutes les lignes
                        count_caracters=mini_freadline(buffer,sizeof(char),fd);
                        while(count_caracters!=-1 && count_caracters!=0){
                            mini_printf(buffer);
                            mini_printf("\n");
                            count_caracters=mini_freadline(buffer,sizeof(char),fd);
                        }
                        mini_free(buffer);
                        mini_fclose(fd);
                        mini_exit();
                    }
                     
                    //sinon on lit alors total_lines-N lignes pour déplacer le curseur
                    count_caracters=mini_freadline(buffer,sizeof(char),fd);
                    while(count_lines<total_lines-N && count_caracters!=-1){
                        count_lines++;
                        count_caracters=mini_freadline(buffer,sizeof(char),fd);
                    }
                    //on lit les N lignes restantes
                    while(count_lines<total_lines && count_caracters!=-1 && count_caracters!=0){
                        mini_printf(buffer);
                        mini_printf("\n");
                        count_lines++;
                        count_caracters=mini_freadline(buffer,sizeof(char),fd);
                    }
                    mini_fclose(fd);
                    mini_free(buffer);
                }
                
            }
        }
    }
    else{
        //Il n'y avait pas d'option -n; cela équivaut à un cat de tous les fichiers spécifiés s'il y en a
        extern int IOBUFFER_SIZE;
        char* buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);
        if(buffer!=(void*)-1){
            if(argc==1){
                //Si aucun paramètre n'a été passé à mini_tail :(
                while (1){ 
                    mini_scanf(buffer,IOBUFFER_SIZE);
                    if(mini_strcmp(buffer,"exit")==0)
                        break;
                    mini_printf(buffer);
                    mini_printf("\n");
                }
                mini_exit();
            }
            //else
            for(int j=1;j<argc;j++){
                char* file=argv[j];
                int count=0;
                MYFILE* fd=mini_fopen(file,'r');
                if(fd!=(void*)-1){

                    mini_printf("==> ");
                    mini_printf(file);
                    mini_printf(" <==\n");

                    count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                    while(count!=-1 && count!=0){
                        mini_printf(buffer);
                        count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                    }
                    mini_printf("\n");
                    mini_fclose(fd);
                }
            } 
            mini_free(buffer);  
        }
    }

    mini_exit();
}