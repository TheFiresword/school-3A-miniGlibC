#include <stdio.h>
#include <unistd.h>
#include "mini_lib.h"
#include <string.h>
#include <errno.h>

int BUF_SIZE=1024;
char* buffer=NULL;
int ind=-1;

void mini_printf(char* chaine){
    if (ind==-1){
      //1er appel de new_printf()
      buffer=mini_calloc(sizeof(char),BUF_SIZE);
      if (buffer!=(void*)-1){
         ind=0;
      }
   }
   char c=chaine[0];
   int i=0;
   while (c!='\0'){
        if (c=='\n' || ind==BUF_SIZE){
            //On vide le buffer
            if(write(STDOUT_FILENO,buffer, ind)==-1){
                mini_perror("Echec d'écriture:");
            }
            else{
                ind=0;
                if(c=='\n'){
                    write(STDOUT_FILENO,"\n",1);

                }
            }
        }
        else{
            //On peut écrire dans le buffer
            buffer[ind]=c;
            ind++;
        }
        
        if(ind != BUF_SIZE)
            i++;
        c=chaine[i];  
   }
}

int mini_scanf(char* buffer, int size_buffer){
/*
Cette fonction lit depuis l'entrée standard au plus size_buffer caractères et
stocke le contenu dans buffer.
Si l'utilisateur saisit plus de size_buffer caractères, on efface les caractères
qui dépassent
Retourne le nombre de caractères lus.
*/
 int read_character;
 if((read_character=read(STDIN_FILENO, buffer, size_buffer))==-1){
    mini_perror("Erreur à la lecture de l'entree standard");
 }
 else{
    buffer[read_character-1]='\0';

    //on vide le buffer du clavier

 }
 return read_character;
}


int mini_strlen(char* s){
    /*
    retourne la taille de la chaine s
    */
   int i=0;
   char c=s[0];
    while (c!='\0')
   {
    i++;
    c=s[i];
   }
   return i;
   
}

int mini_strcpy(char*s, char*d){
    /*
    Copie la chaîne s dans d retourne le nombre de caractères copiés
    */
    char c=s[0];
    
    int i=0;
     while (c!='\0')
   {
    d[i]=c;
    i++;
    c=s[i];
   }
   d[i]='\0';
   return i;
}

int mini_strcmp(char* s1, char* s2){
    /*Compare les chaines s1 et s2, retourne 0 si identique
    Sinon renvoie 1
    */
    if (mini_strlen(s1)!=mini_strlen(s2))
        return 1;
    
    int i=0;
     while (s1[i]!='\0')
   {
    if(s1[i]!=s2[i])
        return 1;
    i++;
   }
   return 0;
}

void mini_perror(char * message){
    /*
    Affiche un message d'erreur suivi du code errno
    */
    mini_printf(message);
    mini_printf(": ");
    mini_printf(strerror(errno));
    mini_printf("\n");
}

void exit_properly(int status){
   write(STDOUT_FILENO,buffer,ind);  
   _exit(status);
}