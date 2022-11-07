#include <fcntl.h>
#include "mini_lib.h"
#include <stdio.h>
#include <unistd.h>

int IOBUFFER_SIZE=2048;

OPEN_FILES* OPEN_FILES_LISTE=NULL;



MYFILE* mini_fopen(char* file, char mode){
    int fd;
    int converted_flag;

    switch (mode)
    {
    case 'a':
        converted_flag= O_APPEND;
        break;
    case 'r':
        converted_flag=O_RDONLY;
        break;
    case 'w':
        converted_flag= O_WRONLY;
        break;
    case 'b':
        converted_flag=O_RDWR;
        break;
    case 'c':
        converted_flag=O_WRONLY|O_CREAT;
        break;
    default:
        converted_flag=O_RDONLY;
        break;
    }
    if(converted_flag==(O_WRONLY|O_CREAT)){
        if((fd=open(file,converted_flag,S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH))==-1){ 
            mini_perror("Erreur d'ouverture du fichier");
            return NULL;
        }
    }
    else{
        if((fd=open(file,converted_flag))==-1){ 
            mini_perror("Erreur d'ouverture du fichier");
            return NULL;
        }
    }

    MYFILE* the_file= mini_calloc(sizeof(MYFILE),1);
    if (the_file!=(void*)-1){
        the_file->fd=fd;
        the_file->ind_read=-1;
        the_file->ind_write=-1;
    }
     //On ajoute le fichier à la liste des fichiers à flush
    OPEN_FILES* new_file=mini_calloc(sizeof(OPEN_FILES),1);
    if(new_file!=(void*)-1){
        new_file->cellule=the_file;
        new_file->suivant=NULL;
        
        if(OPEN_FILES_LISTE==NULL){
            OPEN_FILES_LISTE=mini_calloc(sizeof(OPEN_FILES),1);
            if(OPEN_FILES_LISTE!=(void*)-1){
                OPEN_FILES_LISTE=new_file;
            }
        }
        else{
            OPEN_FILES* fichier_actuel=OPEN_FILES_LISTE;
            while (fichier_actuel->suivant!=NULL)
            {
                fichier_actuel=fichier_actuel->suivant;
            }
            fichier_actuel->suivant=new_file;     
        }
    }
    //Count the fd; for debug
    OPEN_FILES* actuel=OPEN_FILES_LISTE;
    int count=0;
    while (actuel!=NULL)
    {
        count++;
        actuel=actuel->suivant;
    }
    #ifdef DEBUG
        printf("Open %d fichiers ouverts\n",count);
    #endif

    return the_file;
}  




int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file){
    /*
    Lit IOBUFFER_SIZE elements avec read et les stocke dans buffer_read.
    Les éléments de buffer_read sont recopiés dans buffer
    Un autre read est déclenché que si ind_read est arrivé à la fin de buffer_read
    */

   if(file->ind_read ==-1){
        //1ere lecture dans le fichier file
        if((file->buffer_read=mini_calloc(size_element,IOBUFFER_SIZE))==(void*)-1){
            mini_perror("Erreur allocation mémoire du buffer read");
            return -1;
        }
        file->ind_read=0;
        
        if(read(file->fd,file->buffer_read,IOBUFFER_SIZE*size_element)==-1){
            mini_perror("Erreur de lecture du fichier");
            return -1;
        }
        
   }
        
    int i=0;
    char* char_buffer_read=mini_calloc(size_element,IOBUFFER_SIZE);
    char* char_buffer=mini_calloc(size_element,number_element);

    char_buffer_read=(char*)file->buffer_read;
    char_buffer=(char*)buffer;

    while(i<number_element*size_element){
        if(file->ind_read==IOBUFFER_SIZE*size_element){
            //On est arrivé à la fin du buffer read, on le recharge avec un read
            if(read(file->fd,file->buffer_read,IOBUFFER_SIZE*size_element)==-1){
                mini_perror("Erreur de lecture du fichier");
                mini_free(char_buffer);
                mini_free(char_buffer_read);
                return -1;
            }
            file->ind_read=0;    
        }
        if(char_buffer_read[file->ind_read]=='\0'){
            //on est arrivé à la fin du fichier
            break;
        }

        char_buffer[i]=char_buffer_read[file->ind_read];
        file->ind_read++;
        i++;
    }
    //char_buffer[i]='\0';

    mini_free(char_buffer);
    mini_free(char_buffer_read);
    return i;

}

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file){
    /*
    Recopie les éléments de buffer_write et met à jour ind_write
    UN write est déclenché que si buffer_write est plein
    Renvoie le nombre de caractères écrits ou -1
    */
    

    if(file->ind_write==-1){
        //1ere écriture dans le fichier file
        if((file->buffer_write=mini_calloc(size_element,IOBUFFER_SIZE))==(void*)-1){
            mini_perror("Erreur allocation mémoire du buffer write");
            return -1;
        }

        file->ind_write=0;
       
    }
    char* char_buffer=mini_calloc(size_element,number_element);
    char* char_buffer_write=mini_calloc(size_element,IOBUFFER_SIZE);

    char_buffer=(char*)buffer;
    char_buffer_write=(char*)file->buffer_write;
    int i=0;
    while(i<number_element*size_element){
        if(file->ind_write==IOBUFFER_SIZE*size_element){
            //Le buffer write est rempli
            if(write(file->fd,file->buffer_write,IOBUFFER_SIZE*size_element)==-1){
                mini_perror("Erreur d'ecriture dans le fichier");
                mini_free(char_buffer);
                mini_free(char_buffer_write);
                return -1;      
            }
            file->ind_write=0;
            
        }   
        char_buffer_write[file->ind_write]=char_buffer[i];
        file->ind_write++;
        //On arrête la boucle si on tombe sur le caractère fin de chaîne
        if(char_buffer[i]=='\0'){
            break;
        }
        i++;
    }
    mini_free(char_buffer);
    mini_free(char_buffer_write);
    //Le caractère '\0' n'est pas compté
    return i;
}

int mini_fflush(MYFILE* file){
    /*
    Force l'écriture des données non écrites présentes dans buffer_write
    Renvoie -1 en cas d'erreur ou le nombre de caractères écrits
    */
    int char_number=0;
    if(file->ind_write!=0 && file->ind_write!=-1){
        if((char_number=write(file->fd,file->buffer_write,file->ind_write))==-1)
            mini_perror("Flush non effectue");
    }
    return char_number;
}


int mini_fclose(MYFILE* file){
    /*
    Ferme le fichier le flush le supprime de la liste
    et utilise l'appel système close pour le fermer 
    */
    if(mini_fflush(file)!=-1){
        OPEN_FILES* actuel= OPEN_FILES_LISTE;
        if(OPEN_FILES_LISTE!=NULL){

            if(OPEN_FILES_LISTE->cellule==file)
                OPEN_FILES_LISTE=OPEN_FILES_LISTE->suivant;
            
            else{
                while(actuel->suivant!=NULL){
                    if(actuel->suivant->cellule==file){
                        actuel->suivant=actuel->suivant->suivant;
                        break;
                    }
                    actuel=actuel->suivant;
                }
            }
             //Count the fd; for debug
            OPEN_FILES* actuel=OPEN_FILES_LISTE;
            int count=0;
            while (actuel!=NULL)
            {
                count++;
                actuel=actuel->suivant;
            }
            #ifdef DEBUG
                printf("Close: %d fichiers ouverts\n",count);
            #endif

        }
        else{
            mini_printf("Aucun fichier n a ete ouvert\n");
        }

        if(close(file->fd)==-1){
            mini_perror("Erreur de fermeture fichier");
            return -1;
        }
        return 0;
    }
    return -1;

}

char mini_fgetc(MYFILE* file){
    /*
    Renvoie un caractère lu, -1 en cas d'erreur
    */
    char* tempo_buffer=mini_calloc(sizeof(char),1);
    if(tempo_buffer!=(void*)-1){
        char character;
        if(mini_fread(tempo_buffer,sizeof(char),1,file)!=-1){
            character=tempo_buffer[0];
            mini_free(tempo_buffer);
            return character;   
        }
    }
    
    return -1;
}

int mini_fputc(MYFILE* file, char c){
    /*
    Ecrit un caractère -1 en cas d'erreur
    */
    char* tempo_buffer=mini_calloc(sizeof(char),2);
    if(tempo_buffer!=(void*)-1){
        tempo_buffer[0]=c;
        tempo_buffer[1]='\0';
        if(mini_fwrite(tempo_buffer,sizeof(char),1,file)!=-1)
            return 0;
    }
    mini_free(tempo_buffer);
    return -1;
}

