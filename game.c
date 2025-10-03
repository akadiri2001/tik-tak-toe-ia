#include "jeu.h"
#include <stdio.h>
#include <string.h>

void initialiser_jeu(Jeu *jeu) {
    memset(jeu->plateau, VIDE, TAILLE_PLATEAU * sizeof(Case));
    jeu->joueur_actuel = JOUEUR_X;
}

void afficher_plateau(const Jeu *jeu) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        if (jeu->plateau[i] == VIDE) {
            printf(" %d ", i + 1);
        } else if (jeu->plateau[i] == JOUEUR_X) {
            printf(" X ");
        } else {
            printf(" O ");
        }
        
        if ((i + 1) % 3 == 0) {
            printf("\n");
            if (i < 8) printf("---+---+---\n");
        } else {
            printf("|");
        }
    }
    printf("\n");
}

int coup_valide(const Jeu *jeu, int position) {
    return position >= 0 && position < TAILLE_PLATEAU && jeu->plateau[position] == VIDE;
}

void jouer_coup(Jeu *jeu, int position) {
    jeu->plateau[position] = jeu->joueur_actuel;
    jeu->joueur_actuel = (jeu->joueur_actuel == JOUEUR_X) ? JOUEUR_O : JOUEUR_X;
}

int verifier_victoire(const Jeu *jeu) {
    int lignes[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    
    for (int i = 0; i < 8; i++) {
        Case a = jeu->plateau[lignes[i][0]];
        Case b = jeu->plateau[lignes[i][1]];
        Case c = jeu->plateau[lignes[i][2]];
        
        if (a != VIDE && a == b && b == c) {
            return a;
        }
    }
    return 0;
}

int plateau_plein(const Jeu *jeu) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        if (jeu->plateau[i] == VIDE) return 0;
    }
    return 1;
}

unsigned long long obtenir_hash(const Jeu *jeu) {
    unsigned long long hash = 0;
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        hash = hash * 3 + jeu->plateau[i];
    }
    return hash;
}
