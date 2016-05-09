#include <math.h>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include "limits.h"

void lectureDB(DB db){
    for(int i=0; i<10; i++){
        printf("Sommet %d : nom = %s", i, db.t[i].nom);
    }
}

DB creation(char* path){
    DB db;
    int nbSommets, nbArcs;
    char test[511];
    FILE* f = NULL;
    f = fopen(path,"r");
    if(f!=NULL){
        fscanf(f, "%d %d", &nbSommets, &nbArcs);
        fgets(test, 511, f);
        printf("%d %d ", nbSommets, nbArcs);
        fgets(test, 511, f);
        printf("%s", test);
        int* bin;
        if(0==0){
            printf("OK");
            db.g.sommets=malloc(nbSommets*sizeof(Sommet));
            db.g.arcs=malloc(nbArcs*sizeof(Arc));
            db.t=malloc(nbSommets*sizeof(Noeud));
            for(int i=0; i<nbSommets; i++){
                db.g.sommets[i].pere=-1;
                db.g.sommets[i].poids=100000;
                printf("%f", db.g.sommets[i].poids);
                fscanf(f,"%d %f %f %s", bin, &(db.t[i].lat), &(db.t[i].lon), db.t[i].nomLigne); // erreur ici
                printf("%s", db.t[i].nomLigne);
                fgets(db.t[i].nom,511,f);
                if ((db.t[i].nom)[strlen(db.t[i].nom)-1]<32) (db.t[i].nom)[strlen(db.t[i].nom)-1]=0;
            }
            fgets(test, 511, f);
            for(int i=0; i<nbArcs;i++){
                fscanf(f,"%d %d %lf", &(db.g.arcs[i].depart), &(db.g.arcs[i].arrivee), &(db.g.arcs[i].valeur));
            }
        }
    }
    return db;
}

void bellman(Graphe G){

}
