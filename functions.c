#include <math.h>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

Graphe creation(char* path){
    Graphe lol;
    int nbSommets, nbArcs;
    char test[1000];
    FILE* f = NULL;
    f = fopen(path,"r");
    if(f!=NULL){
        long pos = ftell(f);
        printf("%ld", pos);
        fseek(f, 0, SEEK_SET);
        fscanf(f, "%d %d", &nbSommets, &nbArcs);
        printf("%d %d ", nbSommets, nbArcs);
        //fseek(f, 10, SEEK_SET);
        pos = ftell(f);
        printf("%ld ", pos);
        fgets(test, 511, f);
        pos = ftell(f);
        printf("%ld ", pos);
        printf("                    %c", test[0]);
    }
    return lol;

}

void bellman(Graphe G){

}
