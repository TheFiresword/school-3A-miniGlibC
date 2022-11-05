#include "mini_lib.h"
#include <stdio.h>


int main(int argc, char**argv){
    int* firstBloc= mini_calloc(sizeof(int),4);
    
    int* secondBloc= mini_calloc(sizeof(int),1);
    int *thirdBloc=mini_calloc(sizeof(int),3);

    printf("adresse du 1er bloc: %p\nadresse du 2nd bloc: %p \n",firstBloc, secondBloc);
    for(int i=0;i<4;i++){
        firstBloc[i]=i+1;
    }

    mini_free(firstBloc);
    int *fourBloc=mini_calloc(sizeof(int),3);
    printf("adresse du 1er bloc: %p\nadresse du 3em bloc: %p \n",firstBloc,fourBloc);
    return 0;
}