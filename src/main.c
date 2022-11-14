#include "mini_lib.h"
#include <stdio.h>


static void memory_print(){
    /**
     * @author: Junior Sedogbo
     * @date: 13/11/2022
     * @version: 1.0
    Cette fonction affiche le contenu de la mémoire.
    Plus explicitement, elle affiche tous les éléments de la liste des zones mémoires allouées par mini_calloc()
    */
    //redéclaration de la structure malloc_element de mini_memory.c
    struct malloc_element
    {
        void* memory; 
        int size;
        int status;
        struct malloc_element* next_malloc;
    };
    extern struct malloc_element *malloc_list;
    struct malloc_element* zone_courante=malloc_list;
    int count=0;
    while (zone_courante!=(void*)-1)
    {   
        #ifdef USE_PRINTF
            printf("Cellule %d dans la liste: %p--Statut:%d\n",count,zone_courante->memory,zone_courante->status);
        #endif     
        zone_courante=zone_courante->next_malloc;
        count++;
    }
    
}
void memory_allocation_test(){
     /*
    Pour vérifier le bon fonctionnement de l'allocation mémoire, j'alloue 3 zones qui vont contenir des int
    Puis j'affiche leur adresse avec la fonction memory_print()
    */
    int* firstBloc= mini_calloc(sizeof(int),4);
    int* secondBloc= mini_calloc(sizeof(int),1);
    char *thirdBloc=mini_calloc(sizeof(char),3);
    mini_printf("3 premières allocations\n");//Une 4ème cellule s'affiche à cause des allocations temporaires que je fais dans les boucles ci dessous
    memory_print();

    /*
    Pour vérifier que les zones mémoires sont bien initialisées avec '\0', j'affiche leur contenu
    Puis je modifie la valeur de leur contenu
    */
   mini_printf("\nValeurs initiales de la zone 1\n");
    for(int i=0;i<4;i++){
        char* chiffre=mini_calloc(sizeof(char),2);
        mini_printf(mini_itoa(firstBloc[i],chiffre));
        mini_free(chiffre);
    }


    for(int i=0;i<4;i++){
        firstBloc[i]=i+1;
    }


    mini_printf("\nValeurs modifiees de la zone 1\n");
    for(int i=0;i<4;i++){
        char* chiffre=mini_calloc(sizeof(char),2);
        mini_printf(mini_itoa(firstBloc[i],chiffre));
        mini_free(chiffre);
    }

    /*
    On fait pareil pour le pointeur de type char. Cependant rien  n'est affiché cette fois puisqu'on lit \0
    */
    mini_printf("\nValeurs initiales de la zone 3\n");
    for(int i=0;i<3;i++){
        char* lettre=mini_calloc(sizeof(char),2);
        lettre[0]=thirdBloc[i];
        lettre[1]='\0';
        mini_printf(lettre);
        mini_free(lettre);
    }

    /**
     Pour vérifier que mini_free fonctionne correctement, je l'appelle et j'affiche les adresses et status des cellules de la liste
    */
    mini_free(firstBloc);
    mini_printf("\nAprès le 1er free\n");
    memory_print();

    /*
    Pour vérifier qu'on peut réutiliser une zone mémoire, j'appelle mini_calloc pour demander une zone de taille inférieure à celle de
    firstBloc qui vient d'être libérée
    */
    int *fourBloc=mini_calloc(sizeof(int),1);
    mini_printf("\nReutilisation de la zone liberee\n");  
    memory_print();

    /*
    Pour vérifier qu'on réutilise une zone mémoire seulement si la taille est plus grande que celle qu'on veut
    */
    mini_free(fourBloc);
    fourBloc=mini_calloc(sizeof(int),5);

    mini_printf("\nNouvelle zone memoire et pas de reutilisaiton\n");
    memory_print();

    mini_free(secondBloc);
    mini_free(thirdBloc);
    mini_free(fourBloc);
}

void standard_io_test(){
    /*
    Vérifie le bon fonctionnement de mini_printf() et mini_scanf()
    */
    char my_buffer[10];
    mini_printf("Veuillez saisir 10 caractères\n");
    mini_scanf(my_buffer,10);
    //On vide le buffer de stdin avec getchar() pour éviter que les caractères restants éventuels soint exécutés comme une commande
    int c=0;
    while (c!='\n' && c!=EOF){
        c=getchar();
    }
    
    mini_printf(my_buffer);
    mini_printf("\n");
}

void string_functions_test(){
    /*
    Vérifie le bon fonctionnement des fonctions de la bibliothèque mini_string.c
    mini_strlen(), mini_itoa(), mini_atoi(), mini_strcat(),...
    */
    char chaine1[10];
    mini_printf("Taille initiale de la chaine1: ");
    char taille[32];
    mini_printf(mini_itoa(mini_strlen(chaine1),taille));
    mini_printf("\n");
 
    mini_printf("Nombre de caractères copiés ");
    char count[32];
    mini_printf(mini_itoa(mini_strcpy("briffaut",chaine1),count));
    mini_printf("\n");

    mini_printf("Chaine 1: ");
    mini_printf(chaine1);
    mini_printf(" de taille ");
    for(int i=0;i<32;i++)
        taille[i]='\0';

    mini_printf(mini_itoa(mini_strlen(chaine1),taille));
    mini_printf("\n");


    char * chaine2="junior";

    mini_printf("Chaine 2: ");
    mini_printf(chaine2);
    mini_printf(" de taille ");
    for(int i=0;i<32;i++)
        taille[i]='\0';
    mini_printf(mini_itoa(mini_strlen(chaine2),taille));
    mini_printf("\n");
   

    mini_printf("Chaine1 vs chaine2: ");
    char result[32];
    if(!mini_strcmp(chaine1,chaine2))
        mini_strcpy("Identique",result);
    else
        mini_strcpy("Non identique",result);
    
    mini_printf(result);
    mini_printf("\n");


    char chaine3[10];
    mini_strcpy(chaine1,chaine3);
    mini_printf("Chaine 3: ");
    mini_printf(chaine3);
    mini_printf(" de taille ");
    for(int i=0;i<32;i++)
        taille[i]='\0';
    mini_printf(mini_itoa(mini_strlen(chaine3),taille));
    mini_printf("\n");


    mini_printf("Chaine1 vs chaine3: ");
    for(int i=0;i<32;i++)
        result[i]='\0';
    if(!mini_strcmp(chaine1,chaine3))
        mini_strcpy("Identique",result);
    else
        mini_strcpy("Non identique",result);
    
    mini_printf(result);
    mini_printf("\n");


    //mini_strcpy("junior", chaine2); //à revoir
    //printf("Nouvelle Chaine 2: %s de taille %d\n",chaine2, mini_strlen(chaine2));

    char* chaine4="sosthene";
    char* chaine5="jiunioris";

    //checking mini_strcat()
    char* concat_chaine45=mini_strcat(chaine4, chaine5);
    mini_printf("Concatenation de chaine4 et chaine5: ");
    mini_printf(concat_chaine45);
    mini_printf("\n");

    //Checking mini_strrchr()
    char* found=mini_strrchr(chaine5,'i');
    if(found!=(void*)-1){
        mini_printf("Derniere occurence de i dans ");
        mini_printf(chaine5);
        mini_printf(" : ");
        mini_printf(found);
        mini_printf("\n");
    }
    found=mini_strrchr(chaine4,'i');
    if(found!=(void*)-1){
        mini_printf("Derniere occurence de i dans ");
        mini_printf(chaine4);
        mini_printf(found);
        mini_printf(" : ");
        mini_printf("\n");
    }


    //checking atoi et itoa
    int number=95870;
    char converted_number[6];
    mini_printf(mini_itoa(number,converted_number));
    mini_printf("\n");
}

void file_functions_1_test(){
    /*
    Teste l'ouverture la lecture et  la fermeture de fichiers:
    C'est à dire les fonctions mini_fopen(), mini_fclose(), mini_fread(), et mini_fgetc()
    */
    MYFILE* my_file=mini_fopen("./fileToRead.txt",'r');
    MYFILE* my_file_2=mini_fopen("./secondTestFile.txt",'r');

    if(my_file!=(void*)-1 && my_file_2!=(void*)-1){
            char first_buffer[100+1];
            char second_buffer[50+1];

            int tempo_1=mini_fread(first_buffer,sizeof(char),100,my_file);
            int tempo_2=mini_fread(second_buffer,sizeof(char),50,my_file_2);
            
            mini_printf("1er fichier\n");
            while(tempo_1!=0 && tempo_1!=-1){
                mini_printf("On a lu: ");
                mini_printf(first_buffer);
                mini_printf("\n");

                mini_printf("Testing fgetc:10 caracteres ");
                char tmp[2];
                for(int i=0;i<10;i++){
                    tmp[0]=mini_fgetc(my_file);
                    tmp[1]='\0';
                    mini_printf(tmp);   
                }
                mini_printf("\n");
                tempo_1=mini_fread(first_buffer,sizeof(char),100,my_file);
            }

            mini_printf("\n2nd fichier\n");  
            while(tempo_2!=0 && tempo_2!=-1){
                mini_printf("On a lu: ");
                char tmp[32];
                mini_printf(mini_itoa(tempo_2,tmp));
                mini_printf(" caracteres: ");
                mini_printf(second_buffer);
                mini_printf("\n");
                tempo_2=mini_fread(second_buffer,sizeof(char),50,my_file_2);
            }
    }
    mini_fclose(my_file);
    
    mini_fclose(my_file_2);
}
void file_functions_2_test(){
    /*
    Teste l'écriture dans un fichier
    C'est à dire les fonctions mini_fwrite() et mini_fputc()
    */
    char* buffer="Je teste la fonction mini_fwrite.Ça marche non? Vous croyez? heeee mais ecoutez moi les reufs\n";
    MYFILE* my_file2=mini_fopen("./fileToWrite.txt",'a'); //mode append + écriture
    MYFILE* my_file3=mini_fopen("./thirdTestFile.txt",'b');// mode lecture écriture + écriture


    if(my_file2!=(void*)-1){
        char tmp[3];
        mini_printf("Nombre de caracteres ecrits: ");
        mini_printf(mini_itoa(mini_fwrite(buffer,sizeof(char),96,my_file2),tmp));
        mini_printf("\n");

        for(int i=0;i<4;i++){
            mini_fwrite("hey",sizeof(char),4,my_file2);
        }
        for(int i=0;i<4;i++){
            mini_fputc(my_file2,'i');
        }
        mini_fputc(my_file2,'\n');     
    }

    if(my_file3!=(void*)-1){
        for(int i=0;i<4;i++){
            mini_fputc(my_file3,'a');
        }
        mini_fclose(my_file3);
        
        my_file3=mini_fopen("./thirdTestFile.txt",'b');
        if(my_file3!=(void*)-1){
            char tmp[2];
            tmp[1]='\0';
            mini_printf("Lecture du fichier thirdTestFile.txt après écriture de aaaa\n");
            for(int i=0;i<4;i++){
                tmp[0]= mini_fgetc(my_file3);
                mini_printf(tmp);
            }
            mini_printf("\n");
        }
    }
    
    mini_fclose(my_file2);
    mini_fclose(my_file3);
}


int main(int argc, char**argv){
    mini_printf("****Tests allocation memoire****\n");
    memory_allocation_test();
    mini_printf("\n\n");

    mini_printf("****Tests entrees standards****\n");
    standard_io_test();
    mini_printf("\n\n");

    mini_printf("****Tests fonctions string****\n");
    string_functions_test();
    mini_printf("\n\n");

    mini_printf("****Tests sur les fichiers__Partie 1****\n");
    file_functions_1_test();
    mini_printf("\n\n");

    mini_printf("****Tests sur les fichiers__Partie 2****\n");
    file_functions_2_test();
    mini_printf("\n\n");

    mini_exit();
}