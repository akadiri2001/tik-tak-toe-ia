#include "ia.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initialiser_ia(IA *ia) {
    ia->nombre = 0;
    ia->taille_historique = 0;
    srand(time(NULL));
}

void charger_ia(IA *ia) {
    FILE *fichier = fopen("ia_donnees.bin", "rb");
    if (fichier) {
        fread(&ia->nombre, sizeof(int), 1, fichier);
        if (ia->nombre > MAX_ETATS) ia->nombre = MAX_ETATS;
        fread(ia->donnees, sizeof(EtatAction), ia->nombre, fichier);
        fclose(fichier);
        printf("IA chargée avec %d états appris\n", ia->nombre);
    }
}

void sauvegarder_ia(const IA *ia) {
    FILE *fichier = fopen("ia_donnees.bin", "wb");
    if (fichier) {
        fwrite(&ia->nombre, sizeof(int), 1, fichier);
        fwrite(ia->donnees, sizeof(EtatAction), ia->nombre, fichier);
        fclose(fichier);
    }
}

float obtenir_valeur(IA *ia, unsigned long long etat, int action) {
    for (int i = 0; i < ia->nombre; i++) {
        if (ia->donnees[i].etat == etat && ia->donnees[i].action == action) {
            return ia->donnees[i].valeur;
        }
    }
    return 0.0f;
}

void mettre_a_jour_valeur(IA *ia, unsigned long long etat, int action, float nouvelle_valeur) {
    for (int i = 0; i < ia->nombre; i++) {
        if (ia->donnees[i].etat == etat && ia->donnees[i].action == action) {
            ia->donnees[i].valeur = nouvelle_valeur;
            return;
        }
    }
    
    if (ia->nombre < MAX_ETATS) {
        ia->donnees[ia->nombre].etat = etat;
        ia->donnees[ia->nombre].action = action;
        ia->donnees[ia->nombre].valeur = nouvelle_valeur;
        ia->nombre++;
    }
}

int ia_choisir_coup(IA *ia, const Jeu *jeu, Case ia_joueur) {
    unsigned long long etat = obtenir_hash(jeu);
    int coups_possibles[TAILLE_PLATEAU];
    int nb_coups = 0;
    
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        if (coup_valide(jeu, i)) {
            coups_possibles[nb_coups++] = i;
        }
    }
    
    if (nb_coups == 0) return -1;
    
    int meilleur_coup = coups_possibles[0];
    float meilleure_valeur = obtenir_valeur(ia, etat, coups_possibles[0]);
    
    // Exploration vs exploitation
    if ((float)rand() / RAND_MAX < TAUX_EXPLORATION) {
        meilleur_coup = coups_possibles[rand() % nb_coups];
    } else {
        for (int i = 1; i < nb_coups; i++) {
            float valeur = obtenir_valeur(ia, etat, coups_possibles[i]);
            if (valeur > meilleure_valeur) {
                meilleure_valeur = valeur;
                meilleur_coup = coups_possibles[i];
            }
        }
    }
    
    // Sauvegarder dans l'historique
    ia->historique[ia->taille_historique].coup = meilleur_coup;
    ia->historique[ia->taille_historique].etat = etat;
    ia->taille_historique++;
    
    return meilleur_coup;
}

void ia_apprendre(IA *ia, int victoire) {
    if (victoire) {
        // Récompenser tous les coups joués
        for (int i = 0; i < ia->taille_historique; i++) {
            unsigned long long etat = ia->historique[i].etat;
            int action = ia->historique[i].coup;
            float valeur_actuelle = obtenir_valeur(ia, etat, action);
            float nouvelle_valeur = valeur_actuelle + TAUX_APPRENTISSAGE;
            mettre_a_jour_valeur(ia, etat, action, nouvelle_valeur);
        }
    }
    
    // Réinitialiser l'historique pour la prochaine partie
    ia->taille_historique = 0;
}
