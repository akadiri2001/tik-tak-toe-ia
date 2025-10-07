#include "game.h"
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


void copier_plateau(const Case *src, Case *dest) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        dest[i] = src[i];
    }
}

void rotation_90(const Case *src, Case *dest) {
    dest[0] = src[6]; dest[1] = src[3]; dest[2] = src[0];
    dest[3] = src[7]; dest[4] = src[4]; dest[5] = src[1];
    dest[6] = src[8]; dest[7] = src[5]; dest[8] = src[2];
}

void miroir_horizontal(const Case *src, Case *dest) {
    dest[0] = src[2]; dest[1] = src[1]; dest[2] = src[0];
    dest[3] = src[5]; dest[4] = src[4]; dest[5] = src[3];
    dest[6] = src[8]; dest[7] = src[7]; dest[8] = src[6];
}

unsigned long long obtenir_hash(const Jeu *jeu) {
    Case variantes[8][TAILLE_PLATEAU];

    copier_plateau(jeu->plateau, variantes[0]);
    rotation_90(variantes[0], variantes[1]);
    rotation_90(variantes[1], variantes[2]);
    rotation_90(variantes[2], variantes[3]);
    miroir_horizontal(variantes[0], variantes[4]);
    rotation_90(variantes[4], variantes[5]);
    rotation_90(variantes[5], variantes[6]);
    rotation_90(variantes[6], variantes[7]);

    unsigned long long min_hash = -1ULL;
    for (int i = 0; i < 8; i++) {
        unsigned long long h = 0;
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            h = h * 3 + variantes[i][j];
        }
        if (h < min_hash) min_hash = h;
    }

    return min_hash;
}

