#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h> //pour utiliser NULL
#include <sys/wait.h>


#define ARG_MAX_LENGHT 100
#define ARG_MAX_NUMBER 100
#define PATH_MAX 4096
/*
Ce programme simule un mini-shell. Une fois lancé, il attend sur l'entrée
standard que l'on entre une commande. Cette commande sera ensuite exécutée.
Le processus père attendra que le processus fils se termine avant de demander à nouveau à 
l'utilisateur une commande
Si la commande correspond à exit, le shell s'arrête
*/

char* built_commands[]={
    "mini_touch",
    "mini_cp",
    "mini_echo",
    "mini_cat",
    "mini_head",
    "mini_tail",
    "mini_clean",
    "mini_grep",
    "wc"
};
#define BUILT_COMMANDS_COUNT 9


void init(void){
    /**
     * Initialisation du mini-shell. Bienvenue
    */
    mini_printf("\n\n\n\n*************************************\
******************************");
    mini_printf("\n\n\t\t(:====WELCOME FRIEND====:)");
    mini_printf("\n\t\t---I'M YOUR MINI SHELL---");
    mini_printf("\n\t   |__ You can enter your comands __|\n\n\n");
    mini_printf("*************************************\
******************************\n\n");
}

int get_command(char* command, int size_buffer, char** argv){
    /**
     * Fonction qui écrit l'entrée standard dans le buffer command, et parse la commande en plusieurs
     * arguments. Ces arguments sont stockés dans le tableau de chaines argv
     * Renvoie le nombre d'arguments
    */
    
    mini_scanf(command,size_buffer);
    //Je sépare la commande en plusieurs mots
    //Je vérifie si la commande contient au moins un caractère- sinon y a rien à faire
    int i=0;
    int non_null=0;//booléen pour savoir si la commande contient au moins un caractère
    int j=0;// pour parcourir le tableau d'arguments et avoir le nombre d'arguments
    int k=0;//pour mémoriser la position de début de chaque mot de command
    int length=mini_strlen(command);

    while (i<length)
    {
        if(command[i]!=' '){
            non_null=1;
            break;
        }
        i++;
    }
    if(non_null){
        //commande non vide
   
        i=0;
        while (i<length)
        {
            if(command[i]!=' '&& command[i]!='\t'){
                //on est au début d'un argument
                k=i;
                argv[j]=command+k;
                
                while (command[i]!=' '&& command[i]!='\t' && command[i]!='\0')
                {
                    i++;
                }
                //fin de l'argument
                argv[j][i-k]='\0';

                j++;
                
            }
            i++;
        } 
    }
    return j;  
}

void open_help(){
    /**
    * Fonction qui renvoie le manuel d'aide
    */
    mini_printf("\n\t***MY MINI SHELL HELP***\nCopyright @ Junior Sedogbo\n\n\n\
List of commands supported:\n\n\n \
\t>>>  mini_cat\t<->\tcat\t<->\t./mini_cat\n\n \
\t>>>  touch\t<->\tmini_touch\t<->\t./mini_touch\n\n \
\t>>>  cp\t<->\tmini_cp\t<->\t./mini_cp\n\n \
\t>>>  echo\t<->\tmini_echo\t<->\t./mini_echo\n\n \
\t>>>  head\t<->\tmini_head\t<->\t./mini_head\n\n \
\t>>>  tail\t<->\tmini_tail\t<->\t./mini_tail\n\n \
\t>>>  clean\t<->\tmini_clean\t<->\t./mini_clean\n\n \
\t>>>  grep\t<->\tmini_grep\t<->\t./mini_grep\n\n \
\t>>>  wc\t<->\t./wc\n\n\n");
    mini_printf("All other unix commands are available\n\n");
    return;
}

void execute_command(char** argv){
    /**
     * Fonction qui exécute la commande
    */


    if(mini_strcmp(argv[0],"exit")==0)
        return;
    if(mini_strcmp(argv[0],"help")==0){
        open_help();
        return;
    }
    char* command_prefix=argv[0];

    //Si l'utilisateur saisit la commande sans le ./ on reformate la commande en ajoutant le ./
    for(int i=0;i<BUILT_COMMANDS_COUNT;i++){
        if(mini_strcmp(command_prefix, built_commands[i])==0){
            char* modified_command=mini_calloc(sizeof(char),mini_strlen(command_prefix)+3);
            if(modified_command!=(void*)-1){
                modified_command= mini_strcat("./",command_prefix);
                argv[0]=modified_command;
                break;
            }     
        }
    }
    //on redirige les commandes de base echo, cat, head, ... vers mes commandes personnelles
    char modified_command[20]={'\0'};

    if(!mini_strcmp(argv[0],"echo"))
        mini_strcpy("./mini_echo",modified_command);
        
    else if(!mini_strcmp(argv[0],"touch"))
        mini_strcpy("./mini_touch",modified_command);
     
    else if(!mini_strcmp(argv[0],"cp"))
        mini_strcpy("./mini_cp",modified_command);
    
    else if(!mini_strcmp(argv[0],"cat"))
        mini_strcpy("./mini_cat",modified_command);
    
    else if(!mini_strcmp(argv[0],"head"))
        mini_strcpy("./mini_head",modified_command);
    
    else if(!mini_strcmp(argv[0],"tail"))
        mini_strcpy("./mini_tail",modified_command);
    
    else if(!mini_strcmp(argv[0],"clean"))
        mini_strcpy("./mini_clean",modified_command);
     
    else if(!mini_strcmp(argv[0],"grep"))
        mini_strcpy("./mini_grep",modified_command);
       
    else if(!mini_strcmp(argv[0],"wc"))
        mini_strcpy("./wc",modified_command);
        

    if(mini_strlen(modified_command)>0)
        argv[0]=modified_command;


    //Je fork un child du processus
    pid_t pid=fork();
    if(pid==-1){
        mini_perror("Echec du fork du processus.\n");
        return;
    }
    else if(pid==0){
        //On est dans le processus enfant
        //on peut exécuter notre commande
        if(execvp(argv[0],argv)==-1){
            mini_perror("Commande non executee");
        }
        mini_exit();
    }
    else{
        //on est dans le processus parent
        //on attend
        wait((void*)-1);
        return;
    }

}

int main(int argc, char** argv){

    char command[ARG_MAX_LENGHT*ARG_MAX_NUMBER];
    char path[PATH_MAX];
    char* my_argv[ARG_MAX_NUMBER];
    
    
    int my_argc=0;
    init();
    
    do{
        //Initiailiser à (void*)-1 le tableau d'arguments
        for(int i=0; i<ARG_MAX_NUMBER;i++)
            my_argv[i]=NULL;

        mini_printf("debian@debian11:~");
        mini_printf(getcwd(path,PATH_MAX));
        mini_printf("$ >\n");
        //vider le buffer stdin

        my_argc=get_command(command,ARG_MAX_LENGHT*ARG_MAX_NUMBER,my_argv);
        
        if(my_argc==0){
            //aucun argument, on passe à l'itération suivante
            my_argv[0]=" ";
            continue;
        }
        else
            execute_command(my_argv);   

    } while(mini_strcmp(my_argv[0],"exit")!=0);
    
    mini_printf("\n\n\n\n******************|-_-| BYE FRIEND |-_-|*****************\n\n\n\n");
    
    mini_exit();
}