#ifndef JEU_H
#define JEU_H

#define TAILLE_PLATEAU 9

typedef enum {
    VIDE = 0,
    JOUEUR_X = 1,
    JOUEUR_O = 2
} Case;

typedef struct {
    Case plateau[TAILLE_PLATEAU];
    Case joueur_actuel;
} Jeu;

void initialiser_jeu(Jeu *jeu);
void afficher_plateau(const Jeu *jeu);
int coup_valide(const Jeu *jeu, int position);
void jouer_coup(Jeu *jeu, int position);
int verifier_victoire(const Jeu *jeu);
int plateau_plein(const Jeu *jeu);
unsigned long long obtenir_hash(const Jeu *jeu);

#endif
