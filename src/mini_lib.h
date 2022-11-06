#ifndef MINI_LIB_H
#define MINI_LIB_H


void* mini_calloc (int size_element, int number_element);
void mini_free(void *ptr);
void debogage();//fonction personnelle

void mini_exit();
void exit_properly(int status);

void mini_printf(char* chaine);
int mini_scanf(char* buffer, int size_buffer);
int mini_strlen(char* s);
int mini_strcpy(char*s, char*d);
int mini_strcmp(char* s1, char* s2);
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
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);
int mini_fflush(MYFILE* file);

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