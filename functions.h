#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


struct sommet
{
    double poids;
    int pere;
};
typedef struct sommet Sommet;

struct arc
{
    int depart;
    int arrivee;
    double valeur;
};
typedef struct arc Arc;

struct graphe
{
    Sommet* sommets;
    Arc* arcs;
};

typedef struct graphe Graphe;

Graphe creation(char* path);
void bellman(Graphe G);

#endif // FUNCTIONS_H_INCLUDED
