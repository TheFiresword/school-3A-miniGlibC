#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h>

struct malloc_element
{
    void* memory; 
    int size;
    int status;
    struct malloc_element* next_malloc;
};

// malloc_list est la variable globale qui représente la liste; elle pointe sur le 1er élement de la liste
struct malloc_element *malloc_list=NULL;



void* mini_calloc (int size_element, int number_element){
    //Variable utilisée pour initialiser à 0 la zone mémoire allouée
    unsigned char* allocated_memory=NULL;

    /*SI la liste est vide, on crée une nouvelle zone mémoire et on l'ajoute à la tête de la liste*/
    if(malloc_list==NULL){

        struct malloc_element *new_element= sbrk(sizeof(struct malloc_element));
        if(new_element==(void*)-1)
            mini_perror("Erreur allocation mémoire");
        else{
            new_element->memory=sbrk(size_element* number_element);
            if(new_element->memory == (void*)-1)
                mini_perror("Erreur allocation mémoire");
            else{
                new_element->size=size_element*number_element;
                new_element->status=1;
                new_element->next_malloc=NULL;

                //On initialise la zone mémoire allouée avec des '\0'
                allocated_memory=new_element->memory;
                for(int i=0;i<size_element*number_element;i++){
                    *(allocated_memory+i)='\0';
                }

                //on positionne new_element comme tête de liste       
                malloc_list=new_element;
                return new_element->memory;
            }
        }
        
    }

    /*Si la liste n'est pas vide,on vérifie dans un premier temps si une cellule libre de la liste a une zone 
    mémoire suffisante pour être réutilisée*/
    else{
        struct malloc_element* zone_courante=malloc_list;
        
        while(zone_courante!=NULL){
            if(zone_courante->status==0 && zone_courante->size >= size_element*number_element){
                allocated_memory=zone_courante->memory;

                //On initialise la zone mémoire qu'on veut réutiliser avec des '\0'
                for(int i=0;i<size_element*number_element;i++){
                    *(allocated_memory+i)='\0';
                }
                zone_courante->status=1;
                zone_courante->size=size_element*number_element;
                return zone_courante->memory;
            }
            zone_courante=zone_courante->next_malloc;
        }

        //A la sortie de la boucle, si on n'a pas trouvé de zone mémoire réutilisable, alors on alloue une nouvelle zone
      
        
        struct malloc_element *new_element= sbrk(sizeof(struct malloc_element));
        if(new_element==(void*)-1)
            mini_perror("Erreur allocation mémoire");
        else{
            new_element->memory=sbrk(size_element* number_element);
            if(new_element->memory == (void*)-1)
                mini_perror("Erreur allocation mémoire");
            else{
                new_element->size=size_element*number_element;
                new_element->status=1;
                new_element->next_malloc=NULL;

                //On initialise la zone mémoire allouée avec des '\0'
                allocated_memory=new_element->memory;
                for(int i=0;i<size_element*number_element;i++){
                    *(allocated_memory+i)='\0';
                }

                //On ajoute la cellule à la fin de la liste
                /* Pour ajouter la zone allouée à la liste, il faut parcourir la liste
                jusqu'à trouver la cellule de fin, c'est à dire celle dont l'élément next_malloc vaut NULL
                */
                
                zone_courante=malloc_list;
                while (zone_courante->next_malloc !=NULL)
                {
                    zone_courante=zone_courante->next_malloc;
                }
                zone_courante->next_malloc=new_element;
                return new_element->memory;
            }
                    
        }              
        
    }
    return (void*)-1;
}

void debogage(){
    /*code de debugage*/
    struct malloc_element* zone_courante=malloc_list;
    int count=0;
    while (zone_courante!=NULL)
    {
        printf("Cellule %d dans la liste: %p--Statut:%d\n",count,zone_courante->memory,zone_courante->status);
        zone_courante=zone_courante->next_malloc;
        count++;
    }
    
}


void mini_free(void *ptr){
    if(ptr!=(void*)-1 && ptr!=NULL && malloc_list!=NULL){
        //Il faut chercher dans la liste la cellule dont l'élément memory vaut ptr
        struct malloc_element* zone_courante=malloc_list;
        while(zone_courante!=NULL){
            if(zone_courante->memory==ptr){
                zone_courante->status=0;
                return;
            }
            zone_courante=zone_courante->next_malloc;
        }
        
        
    }
}


void mini_exit(){

    extern OPEN_FILES* OPEN_FILES_LISTE;
    OPEN_FILES* actuel=OPEN_FILES_LISTE;
    while (actuel!=NULL)
    {
        mini_fflush(actuel->cellule);
        actuel=actuel->suivant;
    }
    
    exit_properly(0); 
}