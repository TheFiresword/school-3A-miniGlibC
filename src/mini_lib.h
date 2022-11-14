#ifndef MINI_LIB_H
#define MINI_LIB_H

//#define DEBUG// Active l'affichage de messages de debogage quand on ouvre et on ferme des fichiers.
#define USE_PRINTF// Autorise l'utilisation de la fonction printf pour afficher des adresses mémoires en hexadécimal
//#define READLINE_INSTALLED// La librairie externe readline est correctement installée

void* mini_calloc (int size_element, int number_element);
void mini_free(void *ptr);


void mini_exit();
void exit_properly(int status);

void mini_printf(char* chaine);
int mini_scanf(char* buffer, int size_buffer);
int mini_strlen(char* s);
int mini_strcpy(char*s, char*d);
int mini_strcmp(char* s1, char* s2);
char* mini_strcat(char* chaine1, char* chaine2);//I've added this function
char* mini_strrchr(char* string, int c);//I've added this function
char* mini_strcspn(char* chaine, char* pattern);//I've added this function
char* mini_searchlinewithpattern(char* line, char* pattern);//I've added this function
int mini_atoi(char* str,int with_alphabetic);//I've added this function
char* mini_itoa(int number, char* chaine);//I've added this function
void mini_perror(char * message);
struct MYFILE
{
    int fd;
    void* buffer_read;
    void* buffer_write;
    int ind_read;
    int ind_write;
};
typedef struct MYFILE MYFILE;
MYFILE* mini_fopen(char* file, char mode);
int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file);
int mini_freadline(void* buffer,int size_element, MYFILE* file);//I've added this function
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);
int mini_fflush(MYFILE* file);
int mini_fseek(MYFILE* file,int offset,int whence);//I've added this function
int mini_countlines(char* file);//I've added this function
typedef struct OPEN_FILES OPEN_FILES;
struct OPEN_FILES
{
    MYFILE* cellule;
    struct OPEN_FILES* suivant;
};

int mini_fclose(MYFILE* file);
char mini_fgetc(MYFILE* file);
int mini_fputc(MYFILE* file, char c);
#endif