#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "ai.h"

int main() {
    Jeu jeu;
    IA ia;
    char choix;
    Case ia_joueur, humain_joueur;
    
    printf("=== MORPION avec IA ===\n\n");
    
    initialiser_ia(&ia);
    charger_ia(&ia);
    
    printf("Voulez-vous jouer X ou O ? (x/o) : ");
    scanf(" %c", &choix);
    
    if (choix == 'x' || choix == 'X') {
        humain_joueur = JOUEUR_X;
        ia_joueur = JOUEUR_O;
        printf("Vous jouez X, l'IA joue O\n");
    } else {
        humain_joueur = JOUEUR_O;
        ia_joueur = JOUEUR_X;
        printf("Vous jouez O, l'IA joue X\n");
    }
    
    initialiser_jeu(&jeu);
    
    int partie_terminee = 0;
    int gagnant = 0;
    
    while (!partie_terminee) {
        afficher_plateau(&jeu);
        
        if (jeu.joueur_actuel == humain_joueur) {
            int position;
            printf("A ton tour ! Entrez un numero (1 a 9) : ");
            scanf("%d", &position);
            position--;
            
            if (coup_valide(&jeu, position)) {
                historique_humain[taille_historique_humain].etat = obtenir_hash(&jeu);
                historique_humain[taille_historique_humain].coup = position;
                taille_historique_humain++;
                jouer_coup(&jeu, position);
            } else {
                printf("Coup invalide ! Reessayez.\n");
                continue;
            }
        } else {
            printf("L'IA reflechit...\n");
            int coup_ia = ia_choisir_coup(&ia, &jeu, ia_joueur);
            jouer_coup(&jeu, coup_ia);
            printf("L'IA a joue en case %d\n", coup_ia + 1);
        }
        
        gagnant = verifier_victoire(&jeu);
        if (gagnant != 0) {
            partie_terminee = 1;
        } else if (plateau_plein(&jeu)) {
            partie_terminee = 1;
        }
    }
    
    afficher_plateau(&jeu);
    
    if (gagnant == humain_joueur) {
        printf("\n Vous avez gagne !\n");
        ia_apprendre(&ia, 2);
    } else if (gagnant == ia_joueur) {
        printf("\n L'IA a gagne !\n");
        ia_apprendre(&ia, 1);
    } else {
        printf("\n Match nul !\n");
        ia_apprendre(&ia, 0);
    }
    
    sauvegarder_ia(&ia);
    printf("Sauvegarde terminee avec %d etats\n", ia.nombre);
    
    return 0;
}
