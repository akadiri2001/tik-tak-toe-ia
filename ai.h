#ifndef IA_H
#define IA_H

#include "game.h"

#define MAX_ETATS 20000
#define TAUX_APPRENTISSAGE 0.3
#define TAUX_EXPLORATION 0.2

typedef struct {
    unsigned long long etat;
    int action;
    float valeur;
} EtatAction;

typedef struct {
    int coup;
    unsigned long long etat;
} Historique;

typedef struct {
    EtatAction donnees[MAX_ETATS];
    int nombre;
    Historique historique[TAILLE_PLATEAU];
    int taille_historique;
} IA;


void initialiser_ia(IA *ia);
void charger_ia(IA *ia);
void sauvegarder_ia(const IA *ia);
int ia_choisir_coup(IA *ia, const Jeu *jeu, Case ia_joueur);
void ia_apprendre(IA *ia, int victoire);

extern Historique historique_humain[TAILLE_PLATEAU];
extern int taille_historique_humain;


#endif
