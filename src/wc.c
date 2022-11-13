#include "mini_lib.h"

/*
Reimplementation de la commande wc
Prend en parametre un nom de fichier
Renvoie le nombre de mots que contient ce fichier; un mot est délimité par ' '
*/
int main(int argc, char** argv){

    extern int IOBUFFER_SIZE;
    char* buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);
    if(buffer!=(void*)-1){
        if(argc==1){
            //Si aucun paramètre n'a été passé à wc :(
            while (1){
                mini_scanf(buffer,IOBUFFER_SIZE);
                if(mini_strcmp(buffer,"exit")==0)
                    break;
            }
        }
        else{
            char* file=argv[1];
            int count=0;//Nombre de caractères renvoyé par mini_fread()
            MYFILE* fd=mini_fopen(file,'r');
            if(fd!=(void*)-1){

                int word_count=0;//compteur de mots
                int lecture_count=0;//compte le nombre d'appels à mini_fread
                int word_continue=0;//boolean pour savoir si on a coupé un mot en 2

                count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                
                while(count!=-1 && count!=0){
                    
                    lecture_count+=1;
                    int i=0;

                    if(lecture_count>1 && word_continue && buffer[0]!=' ' && buffer[0]!='\n'&& buffer[0]!='\t'){
                        //Il faut prendre en compte le cas où à la fin du buffer, on a une partie d'un mot et pas le mot entier.
                        //Ce cas arrive si on fait au moins 2 appels mini_fread, et si le booleen word_continue vaut vrai et si le premier
                        //caractère du nouveau buffer est un caractère alphanumérique
                        //Dans ce cas, on ignore le premier mot du nouveau buffer
                        while (buffer[i]!=' ' && buffer[i]!='\n'&& buffer[i]!='\t')
                                i++;
                    }
                    while(i<count){
                        if(buffer[i]!=' ' && buffer[i]!='\n'&& buffer[i]!='\t'){
                            //On est au début d'un mot
                            word_count++;
                            i++;
                            while (buffer[i]!=' ' && buffer[i]!='\n'&& buffer[i]!='\t')
                                i++;                                                        
                        }
                        i++;
                    }
                    if(buffer[count-1]!=' ' && buffer[count-1]!='\n'&& buffer[count-1]!='\t')
                        word_continue=1;
                    else
                        word_continue=0;
                    
                    count=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fd);
                }
                char nombre_de_mots[32];
                mini_printf(mini_itoa(word_count,nombre_de_mots));                   
                mini_printf(" words\t");
                mini_printf(file);
                mini_printf("\n");

                mini_fclose(fd);
            }
        }
        mini_free(buffer);
    }
    mini_exit();
}