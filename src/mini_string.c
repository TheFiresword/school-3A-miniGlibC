#include <unistd.h>
#include "mini_lib.h"
#include <errno.h>

/**
* @author: Junior Sedogbo
     * @date: 13/11/2022
     * @version: 1.0
Implémentation des fonctions de gestion des chaines de caractère
*/
int BUF_SIZE=1024;
char* buffer=(void*)-1;
int ind=-1;

void mini_printf(char* chaine){
    if (ind==-1){
      //1er appel de mini_printf()
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
 else
    buffer[read_character-1]='\0'; 
 
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

char* mini_strrchr(char* string, int c){
    
    /*
    Personal function:: for fun
    reimplementation of strrchr
    */
    c=(unsigned char)c;
    char*occurence=(void*)-1;
    char* actuel=string;
    while (*actuel!='\0')
    {
        if(*actuel==c){
            occurence=actuel;
        }
        actuel++;
    }
    return occurence;
       
}
char* mini_strcspn(char* chaine, char* pattern){
    /*
    Personal function:: for fun
    reimplementation of strcspn
    Cherche pattern dans chaine
    renvoie un pointeur sur la première occurence de pattern
    Sinon renvoie (void*)-1
    */
    int i=0,j=0;
    int lenght=mini_strlen(pattern);

    while (chaine[i]!='\0')
    {
        for(j=0;j<lenght;j++){
            if(chaine[i+j]!=pattern[j])
                break;
        }
        if(j==lenght)//Le pattern est présent dans la chaine à l'indice i
            return chaine+i;
        else
            i=i+j+1;
    }
    return (void*)-1;

}

char* mini_searchlinewithpattern(char* line, char* pattern){
    /*
    Personal function:: for fun
    Cherche pattern dans line.
    Une ligne étant délimitée par \n
    Renvoie la ligne si elle contient pattern
    Sinon renvoie (void*)-1
    */
    if(mini_strcspn(line,pattern)!=(void*)-1)//la ligne contient le pattern
        return line;
    else
        return (void*)-1;
}

char* mini_strcat(char* chaine1, char* chaine2){
    /*
    Concatene les chaines chaine1 et chaine2
    */
    char* concat_string=mini_calloc(sizeof(char), mini_strlen(chaine1)+mini_strlen(chaine2)+1);
    if(concat_string!=(void*)-1){
        for(int i=0;i<mini_strlen(chaine1);i++){
            concat_string[i]=chaine1[i];
        }
        mini_strcpy(chaine2,concat_string+mini_strlen(chaine1));
        mini_free(concat_string);
    }
    return concat_string;

}

int mini_atoi(char* str,int with_alphabetic){
    /*
    This function converts a string into an integer
    if with_alphanbetic is set to 1, then this function has the same
    behavior as atoi()
    Else, the function returns an integer if and only if the str does not
    contain a non numeric caracter
    */
    int number=0;
    int lenght=mini_strlen(str);
    int i=0;
    for(i=0;str[i]=='0'|| str[i]=='1'||str[i]=='2'||str[i]=='3'
    ||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'
    ||str[i]=='9';++i){
        number=number*10 +str[i]-'0';
    }
    if(!with_alphabetic){
        if(i<lenght){
            //si la chaine contient des lettres la fonction renvoie -1
            //Utile pour mon programme mini_head
            return -1;
        }
    }
    return number;
}

char* mini_itoa(int number, char* chaine){
    /*
    J'utilise le fait que les codes ASCII des chiffres {0,1,2,3,4,5,6,7,8,9}
    forment une suite arithmétique de raison 1
    Ex : '1'+1='2'.
    Donc la représentation char d'un chiffre N est égale à '0'+N
    je dois décomposer le nombre pour obtenir ses chiffres
    */
    if(chaine!=(void*)-1){
        int i=0;

        if(number==0){
            chaine[0]='0';
            chaine[1]='\0';
            return chaine;
        }
        while(number!=0){
            chaine[i]=number%10 + '0';
            number=(int)(number/10);
            i++;
        }
        chaine[i]='\0';
       
        //J'inverse la chaine pour avoir le nombre dans le bon sens
        int taille=i;
        int j,k;
        char c;
        for(j=0,k=taille-1;j<k;j++,k--){
            c=chaine[j];
            chaine[j]=chaine[k];
            chaine[k]=c;
        }
        return chaine;
    }
    return (void*)-1;
}
void mini_perror(char * message){
    /*
    Affiche un message d'erreur suivi du code errno
    */
    mini_printf(message);
    mini_printf(": ");
    char tmp[32];
    mini_printf(mini_itoa(errno,tmp));
    mini_printf("\n");
}

void exit_properly(int status){
   write(STDOUT_FILENO,buffer,ind);
   mini_free(buffer);  
   _exit(status);
}