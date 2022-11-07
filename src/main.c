#include "mini_lib.h"
#include <stdio.h>

void test1(){
     /*
    Pour vérifier le bon fonctionnement de l'allocation mémoire, j'alloue 3 zones qui vont contenir des int
    Puis j'affiche leur adresse avec la fonction debogage()
    */
    int* firstBloc= mini_calloc(sizeof(int),4);
    int* secondBloc= mini_calloc(sizeof(int),1);
    char *thirdBloc=mini_calloc(sizeof(char),3);
    mini_printf("3 premières allocations\n");
    debogage();

    /*
    Pour vérifier que les zones mémoires sont bien initialisées avec '\0', j'affiche leur contenu
    Puis je modifie la valeur de leur contenu
    */
   mini_printf("\nValeurs initiales de la zone 1\n");
    for(int i=0;i<4;i++){
        printf("%d\n",firstBloc[i]);
    }


    for(int i=0;i<4;i++){
        firstBloc[i]=i+1;
    }


    mini_printf("\nValeurs modifiees de la zone 1\n");
    for(int i=0;i<4;i++){
        printf("%d\n",firstBloc[i]);
    }

    /*
    On fait pareil pour le pointeur de type char. Cependant rien  n'est affiché cette fois puisqu'on lit \0
    */
    mini_printf("\nValeurs initiales de la zone 3\n");
    for(int i=0;i<3;i++){
        printf("%c\n",thirdBloc[i]);
    }

    /**
     Pour vérifier que mini_free fonctionne correctement, je l'appelle et j'affiche les adresses et status des cellules de la liste
    */
    mini_free(firstBloc);
    mini_printf("\nAprès le 1er free\n");
    debogage();

    /*
    Pour vérifier qu'on peut réutiliser une zone mémoire, j'appelle mini_calloc pour demander une zone de taille inférieure à celle de
    firstBloc qui vient d'être libérée
    */
    int *fourBloc=mini_calloc(sizeof(int),1);
    mini_printf("\nReutilisation de la zone liberee\n");  
    debogage();

    /*
    Pour vérifier qu'on réutilise une zone mémoire seulement si la taille est plus grande que celle qu'on veut
    */
    mini_free(fourBloc);
    fourBloc=mini_calloc(sizeof(int),5);

    mini_printf("\nNouvelle zone memoire et pas de reutilisaiton\n");
    debogage();

    mini_free(secondBloc);
    mini_free(thirdBloc);
    mini_free(fourBloc);
}

void test2(){
    char * my_buffer= mini_calloc(sizeof(char),10);
    mini_scanf(my_buffer,10);
    printf("%s\n",my_buffer);
    mini_free(my_buffer);
}

void test3(){
    char * chaine1=mini_calloc(sizeof(char),10);
    printf("Taille initiale de la chaine1: %d\n",mini_strlen(chaine1));

    printf("Nombre de caractères copiés %d\n",mini_strcpy("briffaut",chaine1));
    printf("Chaine 1: %s de taille %d\n", chaine1,mini_strlen(chaine1));

    char * chaine2="junior";
    printf("Chaine 2: %s de taille %d\n",chaine2, mini_strlen(chaine2));
    printf("Chaine1 vs chaine2: %s\n",!mini_strcmp(chaine1,chaine2)?"Identique":"Non identique");

    char * chaine3= mini_calloc(sizeof(char),5);
    mini_strcpy(chaine1,chaine3);
    printf("Chaine 3: %s de taille %d\n",chaine3, mini_strlen(chaine3));
    printf("Chaine1 vs chaine3: %s\n",!mini_strcmp(chaine1,chaine3)?"Identique":"Non identique");

    //mini_strcpy("junior", chaine2); à revoir
    printf("Nouvelle Chaine 2: %s de taille %d\n",chaine2, mini_strlen(chaine2));

    mini_free(chaine1);
    mini_free(chaine3);
}

void test4(){
   MYFILE* my_file=mini_fopen("../fileToRead.txt",'r');
   MYFILE* my_file_2=mini_fopen("../secondTestFile.txt",'r');

   if(my_file!=NULL && my_file_2!=NULL){
        char* first_buffer=mini_calloc(sizeof(char),100);
        char* second_buffer=mini_calloc(sizeof(char),50);

        int tempo_1=mini_fread(first_buffer,sizeof(char),100,my_file);
        int tempo_2=mini_fread(second_buffer,sizeof(char),50,my_file_2);

        while(tempo_1!=0 && tempo_1!=-1){
            mini_printf("On a lu: ");
            mini_printf(first_buffer);
            mini_printf("\n");
            tempo_1=mini_fread(first_buffer,sizeof(char),100,my_file);
        }
        mini_printf("\n2nd fichier\n");
        
        while(tempo_2!=0 && tempo_2!=-1){
            mini_printf("On a lu: ");
            mini_printf(second_buffer);
            mini_printf("\n");
            tempo_2=mini_fread(second_buffer,sizeof(char),50,my_file_2);
        }
        
        mini_free(first_buffer);
        mini_free(second_buffer);
   }
   mini_fclose(my_file);
   
   mini_fclose(my_file_2);
}
void test5(){
    char* buffer="Je teste la fonction mini_fwrite\n Ça marche non? Vous croyez? heeee mais ecoutez moi les reufs\n";
    double *double_buffer=mini_calloc(sizeof(double),5);
    for(int i=0;i<5;i++){
        double_buffer[i]=i+0.1*i;
    }
    MYFILE* my_file2=mini_fopen("../fileToWrite.txt",'w');
    MYFILE* my_file1=mini_fopen("../fileToRead.txt",'r');
    MYFILE* my_file3=mini_fopen("../fileToRead.txt",'w');
    MYFILE* my_file4=mini_fopen("../fileToRead.txt",'a');

    if(my_file2!=NULL){
        mini_fwrite(buffer,sizeof(char),100,my_file2);
        //mini_fwrite(double_buffer,sizeof(double),5,my_file2);  
    }
    mini_free(double_buffer);
    mini_fclose(my_file4);
    mini_fclose(my_file2);
    mini_fclose(my_file1);
    mini_fclose(my_file3);
}

void test6(){
    
    MYFILE* my_file2=mini_fopen("../fileToWrite.txt",'w');
    if(my_file2!=NULL){
        //mini_fputc(my_file2,'a');
        mini_fwrite("p",sizeof(char),5,my_file2);
        mini_fwrite("maman",sizeof(char),5,my_file2);
        mini_fwrite("maman",sizeof(char),5,my_file2);
        mini_fclose(my_file2);
    }
    
    my_file2=mini_fopen("../fileToRead.txt",'r');
    if(my_file2!=NULL){
        char* caractere=mini_calloc(sizeof(char),7);
        mini_fread(caractere,sizeof(char),4,my_file2);
        
        mini_printf(caractere);

        mini_printf("\n");
        
        mini_fclose(my_file2);
    }

}


int main(int argc, char**argv){
    
    //test1();
    //test2();
    //test3();
    test4();
    //test5();
    //test6();
    mini_exit();
}