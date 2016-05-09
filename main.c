#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    int depart = -1, arrivee = -1, continuer = 1;
    DB database=creation("metro.csv");

    while(continuer){
        lectureDB(database);

        printf("\n\n\n\n\n");

        printf("CHOISSISSEZ VOTRE STATION DE DEPART (numero) : \n\n\n\n");
        scanf("%d", &depart);
        while(depart<0 || depart > database.g.nbSommets){
            scanf("%d", &depart);
        }

        printf("\n\n\n\n\n");

        printf("CHOISSISSEZ VOTRE STATION D'ARRIVEE (numero) : \n\n\n\n");
        scanf("%d", &arrivee);
        while(arrivee < 0 || arrivee > database.g.nbSommets){
            scanf("%d", &arrivee);
        }

        cheminPlusCourt(database, depart, arrivee);

        printf("RECHERCHER UN AUTRE ITINERAIRE ? (1 oui  0 non)");

        scanf("%d", &continuer);
        while(continuer != 0 || continuer != 1){
            printf("J'espere que tu es content de toi !\n");
            scanf("%d", &continuer);
        }

    }
    return 0;
}
