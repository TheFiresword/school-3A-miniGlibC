#include "mini_lib.h"
#include <sys/stat.h>
#include <fcntl.h>

/**
* @author: Junior Sedogbo
     * @date: 13/11/2022
     * @version: 1.0
Reimplementation de la commande systeme cp
Copie le contenu du fichier source (argv[1]) dans le fichier de destination(argv[2])
Si le fichier de destination n'existe pas il est crée
*/
int main(int argc, char** argv){
    
    if(argc<3){
        if(argc<2)
            mini_printf("cp: missing file operand\nTry \'cp --help\' for more information.\n");
        else{
             mini_printf("cp: missing destination file operand after " );
             mini_printf(argv[1]);
             mini_printf("\nTry \'cp --help\' for more information.\n ");
        }
        mini_exit();
    }
    char* src = argv[1];
    char * dst = argv[2];

    MYFILE* fdsrc, *fddst;
    extern const int IOBUFFER_SIZE;
    char *buffer=mini_calloc(sizeof(char),IOBUFFER_SIZE);
    int count_characters=0;
    
    fdsrc=mini_fopen(src, 'r');
    fddst=mini_fopen(dst, 'c');
    if(fddst!=(void*)-1 && fdsrc!=(void*)-1 && buffer!=(void*)-1){
        
        count_characters=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fdsrc);
        while(count_characters!=0 && count_characters!=-1){
            mini_fwrite(buffer,sizeof(char),IOBUFFER_SIZE,fddst);
            count_characters=mini_fread(buffer,sizeof(char),IOBUFFER_SIZE,fdsrc);
        }
        
        mini_fclose(fdsrc);
        mini_fclose(fddst);
        mini_free(buffer); 
    }
    mini_exit();
}
