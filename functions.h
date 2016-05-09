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
    int nbSommets;
    int nbArcs;
};
typedef struct graphe Graphe;

struct noeud
{
    double lat;
    double lon;
    char nomLigne[511];
    char nom[511];
};
typedef struct noeud Noeud;

struct db
{
    Graphe g;
    Noeud* t;
};
typedef struct db DB;

void lectureDB(DB db);
DB creation(char*);
void bellman(Graphe g, int S);
void cheminPlusCourt(DB, int , int );
void affichageTemps(int);

#endif // FUNCTIONS_H_INCLUDED
