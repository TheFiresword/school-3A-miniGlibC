#include "mini_lib.h"
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Réimplémentation de la commande touch
Crée un fichier vide s'il n'existe pas
Peut prendre plusieurs fichiers en paramètres
*/

int main(int argc, char** argv){
    if(argc>1){
        for(int i=1;i<argc;i++){
            //On vérifie si le fichier existe dans le répertoire dans lequel on est
            char* file=argv[i];
            if(access(file,F_OK)==-1){
                int tempo;
                if((tempo=open(file,O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH))!=-1)
                    close(tempo);
                else
                    mini_perror("Erreur d'ouverture de fichier");
            }
        }
    }
    mini_exit();
}

