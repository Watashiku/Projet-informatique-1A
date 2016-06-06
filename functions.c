#include <math.h>
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "limits.h"
#include <float.h>

#define INFINI DBL_MAX


/* Fonction utilisée pour tester
 * certaines données récupérées
 */
void lectureDB(DB db){
    int i;
    for(i=0; i<db.g.nbSommets; i++){
        printf("STATION %d : nom = %s\n", i, db.t[i].nom);
    }
}


/* Lecture du fichier, création de la DB,
 * récuperation des données
 */
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
        if(0==0){//on sait jamais
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


/* Utilisation de l'algorithme de Bellman
 * sur un graphe à partir d'un sommet
 */
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


/* Fonction pricipale : 
 * elle utilise la fonction bellman(Graphe, int)
 * pour determiner le chemin le plus court entre
 * deux stations, puis l'affiche à l'écran.
 *
 * Comme indiqué sur le readme, l'affichage 
 * s'effectue en deux parties. L'une indique les 
 * changements et aide l'utilisateur en ne lui 
 * fournissant que les informations importantes
 * à son trajet, l'autre indique l'ensemble des 
 * stations traversées.
 */
void cheminPlusCourt(DB db, int depart, int arrivee){
    int position = arrivee, duree = 0, nbChangements = 0, a, i, compteur, details;
    int chemin[100];
    int changements[100];
    changements[0]=-10;
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
            if (strcmp(db.t[position].nomLigne, db.t[chemin[duree]].nomLigne)){
                printf("changement entre %s et %s\n", db.t[chemin[duree]].nomLigne, db.t[position].nomLigne);
                changements[nbChangements] = duree;
                nbChangements++;
            }
            duree++;
            chemin[duree] = position;
        }


        for(i=0 ; i<10; i++){
            printf("changements[%d] = %d\n", i, changements[i]);
        }


        compteur = nbChangements - 1;
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("TRAJET ENTRE %s (STATION %d) ET %s (STATION %d)  \n\n\n\n", db.t[depart].nom, depart, db.t[arrivee].nom, arrivee);
        printf("DUREE ESTIMEE : \n");
        affichageTemps(db.g.sommets[arrivee].poids);
        printf("\n");
        printf("NOMBRE DE STATIONS TRAVERSEES : %d\n", duree);
        printf("NOMBRE DE CHANGEMENT(S) : %d\n\n", nbChangements);

        printf("TRAJET : \n\n");
        temps = db.g.sommets[chemin[duree]].poids;

        if(changements[0] != duree-1){
            if(nbChangements){
                a = changements[nbChangements-1];
            }
            else{
                a = -1;
            }
            affichageTemps(0);
            printf(" :  ligne %s entre %s (station %d) et %s (station %d), %d arret(s)   : ", db.t[depart].nomLigne, db.t[depart].nom, depart, db.t[chemin[duree-1-a]].nom, chemin[duree-1-a], duree-1-a);
            affichageTemps(db.g.sommets[chemin[a+1]].poids - db.g.sommets[chemin[duree]].poids);
            printf("\n");
        }

        for(i=duree-1; i>0; i--){
            if(changements[compteur] == i){
                if(compteur){
                    a = changements[compteur] - changements[compteur-1];
                }
                else{
                    a = i;
                }
                affichageTemps(db.g.sommets[chemin[i+1]].poids);
                printf(" :  changement entre la ligne %s et la ligne %s : ", db.t[chemin[i+1]].nomLigne, db.t[chemin[i]].nomLigne);
                affichageTemps(db.g.sommets[chemin[i]].poids - db.g.sommets[chemin[i+1]].poids);
                printf("\n");
                compteur--;
                if(chemin[i+1]!=duree){
                    affichageTemps(db.g.sommets[chemin[i]].poids);
                    printf(" :  ligne %s entre %s (station %d) et %s (station %d), %d arret(s)   : ", db.t[chemin[i]].nomLigne, db.t[chemin[i]].nom, chemin[i], db.t[chemin[i-a]].nom, chemin[i-a], a-1);

                    affichageTemps(db.g.sommets[chemin[i-a]].poids - db.g.sommets[chemin[i]].poids);
                    printf("\n");
                }

            }
        }

        temps = db.g.sommets[arrivee].poids;
        affichageTemps(temps);
        printf(" :  arrivee a %s (station %d, ligne %s)\n", db.t[arrivee].nom, arrivee, db.t[arrivee].nomLigne);


        printf("TRAJET DETAILLE ? 1/0 \n");
        scanf("%d", &details);
        printf("\n\n");
        if(details){
            temps = db.g.sommets[depart].poids;
            affichageTemps(temps);
            printf(" :  depart de %s (station %d, ligne %s)\n", db.t[depart].nom, depart, db.t[depart].nomLigne);
            for(i=duree-1; i>0; i--){
                temps = db.g.sommets[chemin[i]].poids;
                affichageTemps(temps);
                printf(" :  passage par %s (station %d, ligne %s)\n", db.t[chemin[i]].nom, chemin[i], db.t[chemin[i]].nomLigne);
            }
            temps = db.g.sommets[arrivee].poids;
            affichageTemps(temps);
            printf(" :  arrivee a %s (station %d, ligne %s)\n", db.t[arrivee].nom, arrivee, db.t[arrivee].nomLigne);
        }
    }
}


/* Cette fonction convertit le poids 
 * du trajet en temps, pour faciliter 
 * la lecture des données.
 */
void affichageTemps(int secondes){
    int ratio = 1;
    int heures, minutes;

    secondes *=ratio;

    heures = secondes/3600;
    secondes %= 3600;

    minutes = secondes/60;
    secondes %= 60;

    if(heures){
        printf("%02dh %02dm %02ds", heures, minutes, secondes);
    }
    else{
        printf("%02dm %02ds", minutes, secondes);
    }
}
