#include <math.h>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include "limits.h"

#define INFINI 1000000

void lectureDB(DB db){
    int i;
    for(i=0; i<db.g.nbSommets; i++){
        printf("STATION %d : nom = %s\n", i, db.t[i].nom);
    }
}

DB creation(char* path){
    DB db;
    int i;
    char test[511];
    FILE* f = NULL;
    f = fopen(path,"r");
    if(f!=NULL){
        fscanf(f, "%d %d", &db.g.nbSommets, &db.g.nbArcs);
        fgets(test, 511, f);
        printf("Sommets : %d \nArcs : %d \n\n", db.g.nbSommets, db.g.nbArcs);
        fgets(test, 511, f);
        printf("%s\n", test);
        int bin;
        if(0==0){
            db.g.sommets=malloc(db.g.nbSommets*sizeof(Sommet));
            db.g.arcs=malloc(db.g.nbArcs*sizeof(Arc));
            db.t=malloc(db.g.nbSommets*sizeof(Noeud));


            for(i=0; i<db.g.nbSommets; i++){
                db.g.sommets[i].pere=-1;
                db.g.sommets[i].poids=100000;

                fgets(test, 511, f);
                sscanf(test, "%d %lf %lf %s %s", &bin, &(db.t[i].lat), &(db.t[i].lon), db.t[i].nomLigne, db.t[i].nom);
                //printf("Noeud %d : %lf %lf %s %s\n", bin, (db.t[i].lat), (db.t[i].lon), db.t[i].nomLigne, db.t[i].nom);

                //fgets(db.t[i].nom,511,f);
                if ((db.t[i].nom)[strlen(db.t[i].nom)-1]<32) (db.t[i].nom)[strlen(db.t[i].nom)-1]=0;
            }

            fgets(test, 511, f);
            for(i=0; i<db.g.nbArcs; i++){
                fgets(test, 511, f);
                sscanf(test, "%d %d %lf", &(db.g.arcs[i].depart), &(db.g.arcs[i].arrivee), &(db.g.arcs[i].valeur));
                //printf("Arc entre %d et %d : %lf\n", db.g.arcs[i].depart, db.g.arcs[i].arrivee, db.g.arcs[i].valeur);
            }
        }
    }
    return db;
}


//maj des peres a faire
void bellman(Graphe g, int S){
    int leChangementCEstMaintenant = 0, i;
    int depart, arrivee;

    for(i=0; i<g.nbSommets; i++){
        g.sommets[i].poids = INFINI;
    }

    g.sommets[S].poids = 0;

    while (!leChangementCEstMaintenant){


        leChangementCEstMaintenant = 1;
        for(i=0; i<g.nbArcs; i++){
            depart = g.arcs[i].depart;
            arrivee = g.arcs[i].arrivee;
            if(g.sommets[depart].poids + g.arcs[i].valeur + 1 < g.sommets[arrivee].poids){
                g.sommets[arrivee].poids = g.sommets[depart].poids + g.arcs[i].valeur;
                g.sommets[arrivee].pere = depart;
                leChangementCEstMaintenant = 0;
                }
            }
    }
}


void cheminPlusCourt(DB db, int depart, int arrivee){
    int position = arrivee, duree = 0, i;
    int chemin[100];
    chemin[0] = arrivee;
    bellman(db.g, depart);
    if (db.g.sommets[arrivee].poids == INFINI){
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("AUCUN ITINERAIRE TROUVE\n\n\n");
    }
    else{
        double temps = db.g.sommets[arrivee].poids;

        while(position != depart){
            position = db.g.sommets[position].pere;
            duree++;
            chemin[duree] = position;
        }


        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("TRAJET ENTRE %s (STATION %d) ET %s (STATION %d)  \n\n\n\n", db.t[depart].nom, depart, db.t[arrivee].nom, arrivee);
        printf("DUREE ESTIMEE : %5.1f SECONDES\n", db.g.sommets[arrivee].poids);
        printf("NOMBRE DE STATIONS TRAVERSEES : %d\n", duree);
        printf("DETAIL DU TRAJET : \n\n");
        for(i=duree; i>0; i--){
            temps = db.g.sommets[chemin[i]].poids;
            printf("%5.1f  sec :  passage par %s (station %d)\n", temps, db.t[chemin[i]].nom, chemin[i]);
        }

        temps = db.g.sommets[arrivee].poids;
        printf("%5.1f  sec :  arrivee a %s (station %d)\n\n\n", temps, db.t[arrivee].nom, arrivee);
    }
}
